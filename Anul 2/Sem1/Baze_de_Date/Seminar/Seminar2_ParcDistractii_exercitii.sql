USE ParcDistractii;
GO

--EX pag 7

INSERT INTO Categorii (nume_cat)
VALUES ('copii'), ('adult'), ('pensionari'), ('studenti'), ('elevi'), ('familie'), ('VIP');

INSERT INTO Vizitatori (nume_v, email, cod_cat)
VALUES ('Ana', 'ana@gmail.com', 1),
('Andrei', 'andrei@gmail.com', 2),
('Bogdan', 'bogdan@gmail.com', 3),
('Cristina', 'cristina@gmail.com', 4),
('Dana', 'dana@gmail.com', 2),
('Elena', 'elena@gmail.com', 5),
('Mihai', 'mihai@gmail.com', NULL);

INSERT INTO Sectiuni (nume_s, descriere)
VALUES ('Adrenalina', 'atractii extreme'),
('Carnaval', 'atractii colorate si muzica'),
('Canion', 'atractii pe apa printre stanci'),
('Familie', 'atractii pentru toata familia'),
('Acvatic', 'tobogane si piscine'),
('Dragon', 'atractii tematice cu dragoni'),
('Poveste', 'atractii pentru copii mici');

INSERT INTO Atractii (nume_a, descriere, varsta_min, cod_s)
VALUES ('Rollercoaster', 'cel mai rapid din parc', 12, 1),
('Turnul Caderii', 'cadere libera de la 60m', 16, 1),
('Carusel', 'carusel clasic', 3, 2),
('Raftul', 'coborare cu barca prin canion', 10, 3),
('Castelul Negru', 'casa groazei', 14, 4),
('Toboganul Mare', 'cel mai inalt tobogan', 8, 5),
('Zborul Dragonului', 'rollercoaster pentru copii', 6, NULL);

INSERT INTO Note (cod_v, cod_a, nota)
VALUES (1, 3, 9),
(1, 1, 10),
(2, 1, 9),
(2, 2, 10),
(3, 1, 8.5),
(4, 2, 7),
(5, 4, 10);

SELECT * FROM Categorii;
SELECT * FROM Vizitatori;
SELECT * FROM Sectiuni;
SELECT * FROM Atractii;
SELECT * FROM Note;


--EX pag 9

UPDATE Categorii SET nume_cat='studenti UBB'
WHERE cod_cat=4;
UPDATE Vizitatori SET email='ana_pop@gmail.com'
WHERE cod_v=1;
UPDATE Sectiuni SET descriere='cea mai veche sectiune'
WHERE nume_s='Adrenalina';
UPDATE Atractii SET varsta_min=15
WHERE cod_a=5;
UPDATE Note SET nota=7.5
WHERE cod_v=4 AND cod_a=2;

--EX pag 11

DELETE FROM Note WHERE cod_v=5 AND cod_a=4;

DELETE FROM Atractii WHERE cod_a=6;
