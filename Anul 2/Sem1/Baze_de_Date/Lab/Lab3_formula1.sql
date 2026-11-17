USE formula_1;
GO

CREATE OR ALTER PROCEDURE PilotiDinEchipa @nume_echipa VARCHAR(100)
AS 
BEGIN
	SELECT P.nume, P.prenume, P.numar, T.nume AS nationalitate
	FROM Piloti P
		INNER JOIN Echipe E ON P.id_echipa=E.id_echipa
		INNER JOIN Tari T ON E.id_tara=T.id_tara
	WHERE E.nume=@nume_echipa
END;
GO

EXEC PilotiDinEchipa 'Ferrari';
GO


CREATE OR ALTER PROCEDURE PuncteEchipa @nume_echipa VARCHAR(100), @total_puncte INT OUTPUT
AS
BEGIN
	IF NOT EXISTS (SELECT * FROM Echipe WHERE nume = @nume_echipa)
	BEGIN
        RAISERROR('Echipa nu exista!', 16, 1);
        RETURN;
    END;

	SELECT @total_puncte = ISNULL(SUM(R.puncte), 0)
    FROM Rezultate R
        INNER JOIN Piloti P ON R.id_pilot = P.id_pilot
        INNER JOIN Echipe E ON P.id_echipa = E.id_echipa
    WHERE E.nume = @nume_echipa;
END;
GO


DECLARE @puncte INT
EXECUTE PuncteEchipa 'Ferrari' , @total_puncte = @puncte OUTPUT;
PRINT @puncte;
GO
 
DECLARE @puncte INT;
EXEC PuncteEchipa 'Williams', @total_puncte = @puncte OUTPUT;
GO


CREATE PROCEDURE AdaugaSponsor @nume VARCHAR(100), @domeniu VARCHAR(50)
AS
BEGIN
    IF EXISTS (SELECT * FROM Sponsori WHERE nume = @nume)
    BEGIN
        PRINT 'Sponsorul exista deja!';
        RETURN;
    END;

    INSERT INTO Sponsori (nume, domeniu) VALUES (@nume, @domeniu);
    PRINT 'Sponsorul a fost adaugat.';
END;
GO


EXEC AdaugaSponsor 'Aramco', 'Energie';   
EXEC AdaugaSponsor 'Aramco', 'Energie';   
EXEC AdaugaSponsor 'Shell', 'Energie';    

SELECT * FROM Sponsori;       
GO



CREATE VIEW ListaCircuite
AS
    SELECT nume, oras, lungime_km
    FROM Circuite;
GO

SELECT * FROM ListaCircuite;
GO



CREATE VIEW SponsoriPeDomeniu
AS
    SELECT domeniu, COUNT(*) AS nr_sponsori
    FROM Sponsori
    GROUP BY domeniu;
GO

SELECT * FROM SponsoriPeDomeniu;
GO

CREATE VIEW PunctePiloti
AS
    SELECT P.nume AS pilot, E.nume AS echipa, SUM(R.puncte) AS total_puncte
    FROM Rezultate R
        INNER JOIN Piloti P ON R.id_pilot = P.id_pilot
        INNER JOIN Echipe E ON P.id_echipa = E.id_echipa
    GROUP BY P.nume, E.nume;
GO

SELECT * FROM PunctePiloti ORDER BY total_puncte DESC;