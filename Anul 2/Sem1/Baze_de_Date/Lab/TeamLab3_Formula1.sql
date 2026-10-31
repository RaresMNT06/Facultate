USE formula_1;
GO


-- =================== TABELUL CU VERSIUNEA ===================


CREATE TABLE VersiuneBD
(versiune INT);

INSERT INTO VersiuneBD (versiune) VALUES (0);
GO

SELECT * FROM VersiuneBD
GO


-- =================== 1. TIPUL UNEI COLOANE ===================

CREATE PROCEDURE ModificaTipColoana
AS
BEGIN
	ALTER TABLE Circuite
	ALTER COLUMN oras VARCHAR(100);
	PRINT 'Coloana oras din Circuite are acum tipul VARCHAR(100)';
END;
GO

CREATE PROCEDURE RevinoTipColoana
AS
BEGIN
	ALTER TABLE Circuite
	ALTER COLUMN oras VARCHAR(50);
	PRINT 'Coloana oras din Circuite a revenit la tipul VARCHAR(50)';
END;
GO

-- =================== 2. VALOARE IMPLICITA (DEFAULT) ===================


CREATE PROCEDURE AdaugaDefault
AS
BEGIN
	ALTER TABLE Bilete
	ADD CONSTRAINT df_tribuna DEFAULT 'Generala' FOR tribuna;
	PRINT 'S-a adaugat valoare impilicita Genereala pentru Bilete.tribuna';
END;
GO

CREATE PROCEDURE StergeDefault
AS
BEGIN
	ALTER TABLE Bilete
	DROP CONSTRAINT df_tribuna;
	PRINT 'S-a sters valoarea implicita pentru Bilete.tribuna';
END;
GO

-- =================== 3. CREARE / STERGERE TABEL ===================

CREATE PROCEDURE CreeazaTabel
AS
BEGIN
    CREATE TABLE Mecanici
    (id_mecanic INT PRIMARY KEY IDENTITY,
     nume VARCHAR(50) NOT NULL,
     prenume VARCHAR(50),
     id_echipa INT
    );
    PRINT 'S-a creat tabelul Mecanici';
END;
GO

CREATE PROCEDURE StergeTabel
AS
BEGIN
    DROP TABLE Mecanici;
    PRINT 'S-a sters tabelul Mecanici';
END;
GO


-- =================== 4. COLOANA NOUA ===================

CREATE PROCEDURE AdaugaColoana
AS
BEGIN
    ALTER TABLE Piloti
    ADD nr_victorii INT;
    PRINT 'S-a adaugat coloana nr_victorii in Piloti';
END;
GO

CREATE PROCEDURE StergeColoana
AS
BEGIN
    ALTER TABLE Piloti
    DROP COLUMN nr_victorii;
    PRINT 'S-a sters coloana nr_victorii din Piloti';
END;
GO

-- =================== 5. CHEIE STRAINA ===================

CREATE PROCEDURE AdaugaCheieStraina
AS
BEGIN
    ALTER TABLE Mecanici
    ADD CONSTRAINT fk_Mecanici_Echipe
    FOREIGN KEY (id_echipa) REFERENCES Echipe(id_echipa);
    PRINT 'S-a adaugat cheia straina Mecanici.id_echipa -> Echipe';
END;
GO

CREATE PROCEDURE StergeCheieStraina
AS
BEGIN
    ALTER TABLE Mecanici
    DROP CONSTRAINT fk_Mecanici_Echipe;
    PRINT 'S-a sters cheia straina fk_Mecanici_Echipe';
END;
GO


-- =================== TABELUL CU PROCEDURILE PE VERSIUNI ===================
-- procedura_do:   duce baza din versiunea (v-1) in versiunea v
-- procedura_undo: duce baza din versiunea v inapoi in versiunea (v-1)


CREATE TABLE ProceduriVersiune
(versiune INT PRIMARY KEY,
 procedura_do VARCHAR(100),
 procedura_undo VARCHAR(100),
);


INSERT INTO ProceduriVersiune (versiune, procedura_do, procedura_undo) VALUES
(1, 'ModificaTipColoana', 'RevinoTipColoana'),
(2, 'AdaugaDefault',      'StergeDefault'),
(3, 'CreeazaTabel',       'StergeTabel'),
(4, 'AdaugaColoana',      'StergeColoana'),
(5, 'AdaugaCheieStraina', 'StergeCheieStraina');
GO

-- =================== PROCEDURA PRINCIPALA ===================

CREATE PROCEDURE SchimbaVersiune @versiune INT
AS
BEGIN
    SET NOCOUNT ON;

    IF(@versiune <0 or @versiune > (SELECT MAX(versiune) FROM ProceduriVersiune))
    BEGIN 
        RAISERROR('Versiunea ceruta nu exist!',16, 1);
        RETURN;
    END;
    
    DECLARE @curenta INT;
    DECLARE @procedura VARCHAR(100);

    SELECT @curenta = versiune FROM VersiuneBD;

    IF (@curenta = @versiune)
    BEGIN
        PRINT 'Baza de date este deja la versiunea ceruta.';
        RETURN;
    END;

    WHILE(@curenta < @versiune)
    BEGIN
        SET @curenta = @curenta +1;
        SELECT @procedura = procedura_do FROM ProceduriVersiune WHERE versiune = @curenta;
        EXEC(@procedura);
        UPDATE VersiuneBD SET versiune=@curenta;
    END;


    WHILE (@curenta > @versiune)
    BEGIN
        SELECT @procedura = procedura_undo FROM ProceduriVersiune WHERE versiune = @curenta;
        EXEC(@procedura);
        SET @curenta = @curenta - 1;
        UPDATE VersiuneBD SET versiune = @curenta;
    END;

PRINT 'Baza de date este acum la versiunea ' + CAST(@curenta AS VARCHAR(10));
END;
GO


EXEC SchimbaVersiune 5;
SELECT * FROM VersiuneBD;

EXEC SchimbaVersiune 2;
SELECT * FROM VersiuneBD;

EXEC SchimbaVersiune 9;

EXEC SchimbaVersiune 0;
SELECT * FROM VersiuneBD;

SELECT * FROM ProceduriVersiune
