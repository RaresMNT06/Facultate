USE Blog224_sem1;
GO

--crearea unei functii scalare
CREATE FUNCTION VerificareCuvantCheie (@nume NVARCHAR(100))
RETURNS BIT
AS
BEGIN
	IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
		RETURN 1;
	RETURN 0;

END;
GO

-- apelul functiei

PRINT dbo.VerificareCuvantCheie(N'Cat');
PRINT dbo.VerificareCuvantCheie(N'Dog');
GO
--modificare definitiei functiei scalare

ALTER FUNCTION VerificareCuvantCheie (@nume NVARCHAR(100))
RETURNS VARCHAR(30)
AS
BEGIN
	IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
		RETURN 'Exista cuvantul cheie';
	RETURN 'Nu exista cuvantul cheie';

END;
GO

-- stergerea functiei

DROP FUNCTION dbo.VerificareCuvantCheie;
GO

--crearea unei functii inline table valued function

CREATE FUNCTION  ReturneazaPostari(@data_postarii DATETIME)
RETURNS TABLE AS
RETURN SELECT titlu, data_postarii FROM Postari
WHERE data_postarii>@data_postarii
GO

--apelul functiei inline table valued

SELECT * FROM dbo.ReturneazaPostari('2000-02-02 10:10:10');

--stergerea

DROP FUNCTION dbo.ReturneazaPostari

--crearea unui view
GO

CREATE VIEW vw_Postari
AS
SELECT titlu, data_postarii FROM Postari
WHERE titlu LIKE '%p';
GO

--modificarea def view

ALTER VIEW vw_Postari
AS
SELECT titlu FROM Postari
WHERE titlu LIKE 'p_%';
GO