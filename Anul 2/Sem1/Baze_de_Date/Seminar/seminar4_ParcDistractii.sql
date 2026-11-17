USE ParcDistractii;
GO

CREATE FUNCTION CodCategorie (@nume_cat NVARCHAR(100))
RETURNS INT 
AS
BEGIN
DECLARE @cod INT;
SELECT @cod=cod_cat FROM Categorii WHERE nume_cat=@nume_cat
RETURN @cod;
END;
GO

PRINT dbo.CodCategorie('pensionari');
SELECT dbo.CodCategorie('copii') AS cod_categorie;
GO


CREATE FUNCTION SectiuniTerminateCu(@litera CHAR(1))
RETURNS TABLE AS
RETURN SELECT * FROM Sectiuni WHERE nume_s LIKE '_%'+@litera;
GO

SELECT * FROM dbo.SectiuniTerminateCu('n');
GO


CREATE VIEW vw_CategoriiPensionariCopii
AS
SELECT * FROM Categorii WHERE nume_cat IN ('pensionari' , 'copii')
GO

SELECT * FROM vw_CategoriiPensionariCopii;
GO

CREATE VIEW vw_SectiuniC
AS
SELECT * FROM Sectiuni WHERE nume_s LIKE 'C%';
GO


SELECT * FROM vw_SectiuniC;
GO


CREATE VIEW vw_VizitatoriNote
AS
SELECT V.nume_v AS vizitator, N.nota, A.nume_a AS atractie FROM Vizitatori V
INNER JOIN Note N ON V.cod_v=N.cod_v
INNER JOIN Atractii A ON N.cod_a=A.cod_a;
GO

SELECT * FROM vw_VizitatoriNote;
GO

