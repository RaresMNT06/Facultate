USE formula_1;
GO

-- ===================== PARINTI (fara FK) =====================

INSERT INTO Tari (nume, continent) VALUES
('Italia', 'Europa'),            -- 1
('Marea Britanie', 'Europa'),    -- 2
('Monaco', 'Europa'),            -- 3
('Olanda', 'Europa'),            -- 4
('Austria', 'Europa'),           -- 5
('Germania', 'Europa'),          -- 6
('Australia', 'Oceania'),        -- 7
('SUA', 'America de Nord'),      -- 8
('Japonia', 'Asia'),             -- 9
('Romania', 'Europa');           -- 10

INSERT INTO Sezoane (an, nr_curse) VALUES
(2024, 24),   -- 1
(2025, 24);   -- 2

INSERT INTO Motoare (producator, denumire_model, putere_cp) VALUES
('Mercedes', 'M16 E Performance', 1000),  -- 1
('Ferrari', '066/12', 1000),              -- 2
('Honda RBPT', 'RBPTH003', 1000);         -- 3

INSERT INTO Sponsori (nume, domeniu) VALUES
('Shell', 'Energie'),        -- 1
('Petronas', 'Energie'),     -- 2
('Oracle', 'Tehnologie'),    -- 3
('Santander', 'Financiar'),  -- 4
('Mobil 1', 'Energie'),      -- 5
('Google', 'Tehnologie');    -- 6

-- ===================== COPII (cu FK) =====================

INSERT INTO Echipe (nume, sef_echipa, an_infiintare, id_tara) VALUES
('Ferrari', 'Frederic Vasseur', 1929, 1),        -- 1
('McLaren', 'Andrea Stella', 1963, 2),           -- 2
('Red Bull Racing', 'Laurent Mekies', 2005, 5),  -- 3
('Mercedes', 'Toto Wolff', 2010, 6);             -- 4

INSERT INTO Piloti (nume, prenume, numar, data_nasterii, id_tara, id_echipa) VALUES
('Leclerc', 'Charles', 16, '1997-10-16', 3, 1),        -- 1
('Hamilton', 'Lewis', 44, '1985-01-07', 2, 1),         -- 2
('Norris', 'Lando', 4, '1999-11-13', 2, 2),            -- 3
('Piastri', 'Oscar', 81, '2001-04-06', 7, 2),          -- 4
('Verstappen', 'Max', 1, '1997-09-30', 4, 3),          -- 5
('Tsunoda', 'Yuki', 22, '2000-05-11', 9, 3),           -- 6
('Russell', 'George', 63, '1998-02-15', 2, 4),         -- 7
('Antonelli', 'Andrea Kimi', 12, '2006-08-25', 1, 4);  -- 8

INSERT INTO Masini (denumire_model, an, id_echipa, id_motor, id_pilot) VALUES
('SF-25', 2025, 1, 2, 1),
('SF-25', 2025, 1, 2, 2),
('MCL39', 2025, 2, 1, 3),
('MCL39', 2025, 2, 1, 4),
('RB21',  2025, 3, 3, 5),
('RB21',  2025, 3, 3, 6),
('W16',   2025, 4, 1, 7),
('W16',   2025, 4, 1, 8),
('SF-24', 2024, 1, 2, 1),
('MCL38', 2024, 2, 1, 3);

INSERT INTO Circuite (nume, oras, lungime_km, capacitate, id_tara) VALUES
('Autodromo Nazionale Monza', 'Monza', 5.793, 113000, 1),     -- 1
('Silverstone Circuit', 'Silverstone', 5.891, 164000, 2),     -- 2
('Circuit de Monaco', 'Monte Carlo', 3.337, 37000, 3),        -- 3
('Albert Park Circuit', 'Melbourne', 5.278, 125000, 7),       -- 4
('Circuit of the Americas', 'Austin', 5.513, 120000, 8),      -- 5
('Las Vegas Strip Circuit', 'Las Vegas', 6.201, 100000, 8),   -- 6
('Circuit Zandvoort', 'Zandvoort', 4.259, 105000, 4);         -- 7

INSERT INTO Spectatori (nume, prenume, email, id_tara) VALUES
('Popescu', 'Andrei', 'andrei.popescu@email.com', 10),  -- 1
('Ionescu', 'Maria', 'maria.ionescu@email.com', 10),    -- 2
('Rossi', 'Marco', 'marco.rossi@email.com', 1),         -- 3
('Smith', 'John', 'john.smith@email.com', 2),           -- 4
('Brown', 'Emily', 'emily.brown@email.com', 8),         -- 5
('de Vries', 'Lars', 'lars.devries@email.com', 4);      -- 6

INSERT INTO Curse (denumire, data_cursa, nr_tururi, id_circuit, id_sezon) VALUES
('Marele Premiu al Australiei', '2025-03-16', 58, 4, 2),      -- 1
('Marele Premiu al Monaco', '2025-05-25', 78, 3, 2),          -- 2
('Marele Premiu al Marii Britanii', '2025-07-06', 52, 2, 2),  -- 3
('Marele Premiu al Olandei', '2025-08-31', 72, 7, 2),         -- 4
('Marele Premiu al Italiei', '2025-09-07', 53, 1, 2),         -- 5
('Marele Premiu al SUA', '2025-10-19', 56, 5, 2),             -- 6
('Marele Premiu al Italiei', '2024-09-01', 53, 1, 1),         -- 7
('Marele Premiu de la Las Vegas', '2024-11-23', 50, 6, 1);    -- 8

-- ===================== TABELE DE LEGATURA (m-n) =====================

INSERT INTO Rezultate (id_pilot, id_curse, pozitie, puncte) VALUES
(3, 1, 1, 25), (5, 1, 2, 18), (7, 1, 3, 15), (8, 1, 4, 12), (4, 1, 5, 10),
(3, 2, 1, 25), (1, 2, 2, 18), (4, 2, 3, 15), (5, 2, 4, 12), (2, 2, 5, 10),
(3, 3, 1, 25), (4, 3, 2, 18), (2, 3, 3, 15), (5, 3, 4, 12), (7, 3, 5, 10),
(4, 4, 1, 25), (5, 4, 2, 18), (7, 4, 3, 15), (1, 4, 4, 12), (2, 4, 5, 10),
(5, 5, 1, 25), (3, 5, 2, 18), (4, 5, 3, 15), (1, 5, 4, 12), (7, 5, 5, 10),
(5, 6, 1, 25), (3, 6, 2, 18), (1, 6, 3, 15), (2, 6, 4, 12), (4, 6, 5, 10),
(1, 7, 1, 25), (4, 7, 2, 18), (3, 7, 3, 15), (7, 7, 4, 12), (2, 7, 5, 10),
(7, 8, 1, 25), (2, 8, 2, 18), (1, 8, 3, 15), (5, 8, 4, 12), (3, 8, 5, 10);

INSERT INTO Bilete (id_spectator, id_curse, tribuna, pret) VALUES
(1, 5, 'Tribuna Centrale', 450),
(2, 5, 'Tribuna Centrale', 450),
(3, 5, 'Parabolica', 320),
(4, 5, 'Ascari', 280),
(4, 3, 'Club Corner', 400),
(1, 3, 'Copse', 350),
(6, 3, 'Luffield', 300),
(1, 2, 'Port', 900),
(3, 2, 'Casino', 1100),
(5, 6, 'Main Grandstand', 380),
(4, 6, 'Turn 1', 420),
(6, 4, 'Hairpin', 250),
(5, 1, 'Brabham', 200);

INSERT INTO EchipeSponsori (id_echipa, id_sponsor, suma_anuala) VALUES
(1, 1, 40000000),
(1, 4, 20000000),
(2, 6, 30000000),
(2, 5, 10000000),
(3, 3, 100000000),
(3, 5, 15000000),
(4, 2, 75000000);


SELECT * FROM Piloti;

SELECT nume, id_echipa FROM Piloti;

-- INTEROGARI WHERE

SELECT nume, oras, lungime_km 
FROM Circuite 
WHERE lungime_km > 5 ORDER BY lungime_km DESC;

SELECT pret, tribuna 
FROM Bilete 
WHERE pret >= 300 AND pret <= 450;

SELECT pret, tribuna FROM Bilete WHERE pret BETWEEN 300 AND 450;

SELECT nume 
FROM Sponsori 
WHERE domeniu = 'Energie';


SELECT P.nume, E.nume 
FROM Piloti P 
	INNER JOIN Echipe E ON P.id_echipa = E.id_echipa 
WHERE E.nume = 'Ferrari';

-- INTEROGARI WHERE CU MAI MULTE TABELE

SELECT P.nume, T.nume, E.nume 
FROM Piloti P 
	INNER JOIN Tari T ON P.id_tara = T.id_tara 
	INNER JOIN Echipe E ON P.id_echipa = E.id_echipa
WHERE E.nume = 'Ferrari';

-- INTEROGARI CU GROUP BY

SELECT id_curse, COUNT(*) AS nr_bilete, SUM(pret) AS incasari
FROM Bilete
GROUP BY id_curse;
 
 -- INTEROGARI CU GROUP BY CU MAI MULTE TABELE

SELECT P.nume, E.nume, SUM(R.puncte) AS Puncte
FROM Rezultate R
	INNER JOIN Piloti P ON R.id_pilot = P.id_pilot
	INNER JOIN Echipe E ON P.id_echipa = E.id_echipa
GROUP BY P.nume, E.nume 

SELECT T.nume, COUNT(*) AS nr_circuite
FROM Curse C
	INNER JOIN Circuite Ci ON C.id_circuit = Ci.id_circuit
	INNER JOIN Tari T ON Ci.id_tara = T.id_tara
GROUP BY T.nume;

-- INTEROGARI CU HAVING

SELECT C.denumire, Ci.nume, COUNT(*) AS Bilete_vandute, SUM(B.pret) AS Incasari
FROM Bilete B
	INNER JOIN Curse C ON B.id_curse = C.id_curse
	INNER JOIN Circuite Ci ON C.id_circuit = Ci.id_circuit
GROUP BY C.denumire,Ci.nume
HAVING COUNT(*)>=3;

SELECT P.nume, E.nume AS echipa , SUM(R.puncte) AS Puncte
FROM Rezultate R
    INNER JOIN Piloti P ON R.id_pilot = P.id_pilot
    INNER JOIN Echipe E ON P.id_echipa = E.id_echipa
GROUP BY P.nume, E.nume
HAVING SUM(R.puncte) > 100;

-- INTEROGARI CU DISTINCT

--M-N

SELECT DISTINCT P.nume, P.prenume
FROM Piloti P
	INNER JOIN Rezultate R ON P.id_pilot = R.id_pilot
	INNER JOIN Curse C ON R.id_curse = C.id_curse
WHERE C.data_cursa >= '2025-01-01' AND R.pozitie = 1;

SELECT DISTINCT S.nume, S.prenume
FROM Spectatori S
	INNER JOIN Bilete B ON S.id_spectator = B.id_spectator
	INNER JOIN Curse C ON B.id_curse = C.id_curse
	INNER JOIN Circuite Ci ON C.id_circuit = Ci.id_circuit
	INNER JOIN Tari T ON Ci.id_tara = T.id_tara
WHERE  T.continent = 'Europa';