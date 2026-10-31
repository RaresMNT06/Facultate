USE ParcDistractii
GO


--pag 10 ex 1
CREATE PROCEDURE AdaugaSectiune @nume_s NVARCHAR(100), @descriere NVARCHAR(500)
AS 
BEGIN
INSERT INTO Sectiuni (nume_s,descriere) VALUES (@nume_s,@descriere);
END
GO
EXEC AdaugaSectiune 'Spatiu', 'atractii tematice spatiale';
SELECT * FROM Sectiuni;
GO


--pag 10 ex 2
CREATE PROCEDURE ActualizeazaEmail @cod_v INT, @email NVARCHAR(100)
AS 
BEGIN
UPDATE Vizitatori SET email=@email
WHERE cod_v=@cod_v;
END
GO

EXEC ActualizeazaEmail 1,'anna_pop@gmail.com'
SELECT * FROM Vizitatori;
GO

--pag 10 ex 3


CREATE PROCEDURE ReturneazaVizitatoriNote
AS
BEGIN
SELECT V.nume_v, V.email, COUNT(N.nota) nr_note
FROM Vizitatori V
	INNER JOIN Note N ON V.cod_v = N.cod_v
GROUP BY V.cod_cat, V.nume_v,V.email;
END;
GO


EXEC ReturneazaVizitatoriNote
GO

-- pag 25 ex 1
CREATE PROCEDURE AdaugaCategorie @nume_cat NVARCHAR(100)
AS
BEGIN
IF(EXISTS(SELECT * FROM Categorii WHERE nume_cat=@nume_cat))
	PRINT 'CATEGORIA DEJA EXISTA';
ELSE
	INSERT INTO Categorii (nume_cat) VALUES (@nume_cat);
END
GO

EXEC AdaugaCategorie 'copii';
EXEC AdaugaCategorie 'zombi';
SELECT * FROM Categorii
GO


-- pag 25 ex 2

CREATE PROCEDURE AdaugaAtractie @nume_a NVARCHAR(100), @descriere NVARCHAR(500), 
@varsta_min INT, @nume_s NVARCHAR(100)
AS
BEGIN
DECLARE @cod_s INT;

IF(NOT EXISTS(SELECT * FROM Sectiuni WHERE nume_s=@nume_s))
	INSERT INTO Sectiuni (nume_s) VALUES (@nume_s)

SELECT @cod_s=cod_s FROM Sectiuni WHERE nume_s=@nume_s;
INSERT INTO Atractii (nume_a, descriere, varsta_min, cod_s)
VALUES (@nume_a, @descriere, @varsta_min, @cod_s);


END;
GO


EXEC AdaugaAtractie 'Racheta', 'lansare verticala', 14, 'Spatiu';      --sectiune existenta
EXEC AdaugaAtractie 'Barca Pirat', 'leagan gigant', 10, 'Pirati';      --sectiune noua
SELECT * FROM Sectiuni;
SELECT * FROM Atractii;
GO


--pag 25 ex 3

CREATE PROCEDURE VerificaVizitator @email NVARCHAR(100), @cod_v INT OUTPUT
AS
BEGIN
IF(EXISTS(SELECT * FROM Vizitatori WHERE email=@email))
	SELECT @cod_v=cod_v FROM Vizitatori WHERE email=@email;
ELSE
	RAISERROR('Nu exista niciun vizitator cu aceasta adresa de email!',16,1);
END;
GO

DECLARE @codv AS INT;
SET @codv=0;
EXEC VerificaVizitator 'andrei@gmail.com', @cod_v=@codv OUTPUT;
PRINT @codv;

EXEC VerificaVizitator 'nimeni@gmail.com', @cod_v=@codv OUTPUT;   --eroare
GO


-- pag 34 ex 1

CREATE PROCEDURE StergeAtractie @nume_a NVARCHAR(100)
AS
BEGIN
IF(EXISTS(SELECT * FROM Note N INNER JOIN Atractii A ON N.cod_a=A.cod_a
          WHERE A.nume_a=@nume_a))
	PRINT 'Atractia are note si nu poate fi stearsa';
ELSE
	DELETE FROM Atractii WHERE nume_a=@nume_a;
END;
GO

EXEC StergeAtractie 'Rollercoaster';   --are note, afiseaza mesajul
EXEC StergeAtractie 'Barca Pirat';     --nu are note, se sterge
SELECT * FROM Atractii;
GO


--pag 34 ex 2

CREATE PROCEDURE AdaugaNota @cod_a INT, @cod_v INT, @nota REAL
AS
BEGIN
IF(NOT EXISTS(SELECT * FROM Atractii WHERE cod_a=@cod_a)
   OR NOT EXISTS(SELECT * FROM Vizitatori WHERE cod_v=@cod_v))
BEGIN
	RAISERROR('Atractia sau vizitatorul nu exista!',16,1);
	RETURN;
END;

IF(@nota<1 OR @nota>10)
BEGIN
	RAISERROR('Nota trebuie sa fie cuprinsa intre 1 si 10!',16,1);
	RETURN;
END;

INSERT INTO Note (cod_v, cod_a, nota) VALUES (@cod_v, @cod_a, @nota);
END;
GO

EXEC AdaugaNota 3, 6, 9.5;      --merge (daca vizitatorul 6 nu a notat deja atractia 3)
EXEC AdaugaNota 999, 1, 8;      --eroare: atractia nu exista
EXEC AdaugaNota 1, 6, 15;       --eroare: nota invalida
SELECT * FROM Note;
GO



--pag 34 ex 3


CREATE PROCEDURE Adauga50Atractii
AS
BEGIN
SET NOCOUNT ON;
DECLARE @i INT;
DECLARE @varsta INT;
DECLARE @cod_s INT;
SET @i=1;

WHILE @i<=50
BEGIN
	--varsta minima aleatoare intre 3 si 18
	SET @varsta=3+CAST(RAND()*16 AS INT);
	--o sectiune existenta aleasa aleator
	SELECT TOP 1 @cod_s=cod_s FROM Sectiuni ORDER BY NEWID();

	INSERT INTO Atractii (nume_a, descriere, varsta_min, cod_s)
	VALUES ('Atractia ' + CAST(@i AS VARCHAR(10)),
	        'generata la ' + CONVERT(VARCHAR(30), GETDATE(), 120),
	        @varsta, @cod_s);

	SET @i=@i+1;
END;
PRINT 'Au fost adaugate 50 de atractii';
END;
GO

EXEC Adauga50Atractii;
SELECT * FROM Atractii;
GO