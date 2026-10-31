create database formula_1
GO
use formula_1
GO

/*
  RELATII 1-m:
    Tari     - Echipe
    Tari     - Piloti
    Tari     - Circuite
    Tari     - Spectatori
    Echipe   - Piloti
    Echipe   - Masini
    Motoare  - Masini
    Circuite - Curse
    Sezoane  - Curse

  RELATII m-n:
    Piloti     - Curse     (prin Rezultate)
    Spectatori - Curse     (prin Bilete)
    Echipe     - Sponsori  (prin EchipeSponsori)
*/


-- 1. Tari
CREATE TABLE Tari(
    id_tara INT PRIMARY KEY IDENTITY (1,1),
    nume VARCHAR(50) NOT NULL UNIQUE,
    continent VARCHAR(50)
);


--2. Sezoane
CREATE TABLE Sezoane(
    id_sezon INT PRIMARY KEY IDENTITY (1,1),
    an INT NOT NULL UNIQUE CHECK (an >=1950),
    nr_curse INT CHECK (nr_curse>0)
);

--3. Motoare
CREATE TABLE Motoare(
    id_motor INT PRIMARY KEY IDENTITY (1,1),
    producator VARCHAR(50) NOT NULL,
    denumire_model VARCHAR(50),
    putere_cp INT CHECK (putere_cp > 0)


);


-- 4. Sponsori
CREATE TABLE Sponsori (
    id_sponsor INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL UNIQUE,
    domeniu VARCHAR(50)

);


--5. Echipe 
CREATE TABLE Echipe(
    id_echipa INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL UNIQUE,
    sef_echipa VARCHAR(100),
    an_infiintare INT,
    id_tara INT FOREIGN KEY REFERENCES Tari(id_tara)
);


--6. Piloti
CREATE TABLE Piloti(
    id_pilot INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(50) NOT NULL,
    prenume VARCHAR(50) NOT NULL,
    numar INT UNIQUE CHECK (numar BETWEEN 1 AND 99),
    data_nasterii DATE,
    id_tara INT FOREIGN KEY REFERENCES Tari(id_tara),
    id_echipa INT FOREIGN KEY REFERENCES Echipe(id_echipa)
);

-- 7. Masini  
CREATE TABLE Masini (
    id_masina INT PRIMARY KEY IDENTITY(1,1),
    denumire_model VARCHAR(50) NOT NULL,
    an INT,
    id_echipa INT NOT NULL FOREIGN KEY REFERENCES Echipe(id_echipa),
    id_motor INT NOT NULL FOREIGN KEY REFERENCES Motoare(id_motor),
    id_pilot INT FOREIGN KEY REFERENCES Piloti(id_pilot)
);

-- 8. Circuite  
CREATE TABLE Circuite (
    id_circuit INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    oras VARCHAR(50),
    lungime_km DECIMAL(5,3) CHECK (lungime_km > 0),
    capacitate INT CHECK (capacitate > 0),
    id_tara INT NOT NULL FOREIGN KEY REFERENCES Tari(id_tara)
);

-- 9. Spectatori  
CREATE TABLE Spectatori (
    id_spectator INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(50) NOT NULL,
    prenume VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE,
    id_tara INT FOREIGN KEY REFERENCES Tari(id_tara)
);

-- 10. Curse 
CREATE TABLE Curse (
    id_curse INT PRIMARY KEY IDENTITY(1,1),
    denumire VARCHAR(100) NOT NULL,
    data_cursa DATE NOT NULL,
    nr_tururi INT CHECK (nr_tururi > 0),
    id_circuit INT NOT NULL FOREIGN KEY REFERENCES Circuite(id_circuit),
    id_sezon INT NOT NULL FOREIGN KEY REFERENCES Sezoane(id_sezon)
);


-- Relatii m-m

-- 11. Rezultate (Piloti m - n Curse)
CREATE TABLE Rezultate
(id_pilot INT FOREIGN KEY REFERENCES Piloti(id_pilot),
 id_curse INT FOREIGN KEY REFERENCES Curse(id_curse),
 pozitie INT CHECK (pozitie > 0),
 puncte INT CHECK (puncte >= 0),
 CONSTRAINT pk_Rezultate PRIMARY KEY (id_pilot, id_curse)
);

-- 12. Bilete (Spectatori m - n Curse)
CREATE TABLE Bilete
(id_spectator INT FOREIGN KEY REFERENCES Spectatori(id_spectator),
 id_curse INT FOREIGN KEY REFERENCES Curse(id_curse),
 tribuna VARCHAR(50),
 pret DECIMAL(8,2) CHECK (pret >= 0),
 CONSTRAINT pk_Bilete PRIMARY KEY (id_spectator, id_curse)
);

-- 13. EchipeSponsori (Echipe m - n Sponsori)
CREATE TABLE EchipeSponsori
(id_echipa INT FOREIGN KEY REFERENCES Echipe(id_echipa),
 id_sponsor INT FOREIGN KEY REFERENCES Sponsori(id_sponsor),
 suma_anuala DECIMAL(12,2) CHECK (suma_anuala > 0),
 CONSTRAINT pk_EchipeSponsori PRIMARY KEY (id_echipa, id_sponsor)
);

