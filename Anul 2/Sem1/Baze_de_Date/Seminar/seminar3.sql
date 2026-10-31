USE Blog224_sem1;
SELECT * FROM CuvinteCheie;
GO
--crearea unei proceduri stocate
CREATE PROCEDURE AdaugaCuvantCheie @nume NVARCHAR(100)
AS
BEGIN
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
	PRINT 'Acest cuvant cheie a fost deja adaugat in tabel';
ELSE
	INSERT INTO CuvinteCheie (nume) VALUES (@nume);
END;

--Apelul procedurii stocate
EXEC AdaugaCuvantCheie N'Pumpkin';
SELECT * FROM CuvinteCheie;

--Modificarea definitiei procedurii stocate
GO
ALTER PROCEDURE AdaugaCuvantCheie @nume NVARCHAR(100)
AS
SET NOCOUNT ON;
BEGIN
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
	PRINT 'Acest cuvant cheie a fost deja adaugat in tabel';
ELSE
	INSERT INTO CuvinteCheie (nume) VALUES (@nume);
END;

EXEC AdaugaCuvantCheie N'Cat';
SELECT * FROM CuvinteCheie;

--stergerea unei proceduri stocate
DROP PROCEDURE AdaugaCuvantCheie;
