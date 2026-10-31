--Crearea bazei de date cu numele ParcDistractii
CREATE DATABASE ParcDistractii;
GO

--Conectarea la baza de date
USE ParcDistractii;
GO

--Crearea tabelului Categorii
CREATE TABLE Categorii
(cod_cat INT PRIMARY KEY IDENTITY(1,1),
nume_cat NVARCHAR(100)
);

--Crearea tabelului Vizitatori
CREATE TABLE Vizitatori
(cod_v INT PRIMARY KEY IDENTITY(1,1),
nume_v NVARCHAR(100),
email NVARCHAR(100),
cod_cat INT,
CONSTRAINT fk_CategoriiVizitatori FOREIGN KEY (cod_cat) REFERENCES Categorii(cod_cat) ON UPDATE CASCADE ON DELETE CASCADE
);

--Crearea tabelului Sectiuni
CREATE TABLE Sectiuni
(cod_s INT PRIMARY KEY IDENTITY(1,1),
nume_s NVARCHAR(100),
descriere NVARCHAR(500)
);

--Crearea tabelului Atractii
CREATE TABLE Atractii
(cod_a INT PRIMARY KEY IDENTITY(1,1),
nume_a NVARCHAR(100),
descriere NVARCHAR(500),
varsta_min INT,
cod_s INT,
CONSTRAINT fk_SectiuniAtractii FOREIGN KEY (cod_s) REFERENCES Sectiuni(cod_s) ON UPDATE CASCADE ON DELETE CASCADE
);

--Crearea tabelului de legatura Note (many to many intre Vizitatori si Atractii)
CREATE TABLE Note
(cod_v INT,
cod_a INT,
nota REAL,
CONSTRAINT fk_VizitatoriNote FOREIGN KEY (cod_v) REFERENCES Vizitatori(cod_v),
CONSTRAINT fk_AtractiiNote FOREIGN KEY (cod_a) REFERENCES Atractii(cod_a),
CONSTRAINT pk_Note PRIMARY KEY (cod_v, cod_a)
);

/*Crearea unei constrangeri CHECK pe coloana nota din tabelul Note dupa ce a fost creat tabelul*/
ALTER TABLE Note
ADD CONSTRAINT ck_nota CHECK (nota>=1 AND nota<=10);