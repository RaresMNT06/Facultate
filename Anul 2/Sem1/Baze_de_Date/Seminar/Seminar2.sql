INSERT INTO Utilizatori (nume_utilizator, email, parola)
VALUES ('bob', 'bob@gmail.com', 'dvaa949a48tg9'),
('tom', 'tom@gmail.com', 'efghw9545' );

--citirea datelor din tabel
SELECT * FROM Utilizatori;
SELECT cod_u, nume_utilizator, email, parola FROM Utilizatori;
SELECT nume_utilizator, email FROM Utilizatori
SELECT nume_utilizator AS utiliazator, email FROM Utilizatori;
SELECT email, nume_utilizator FROM Utilizatori;

--actualizarea datelor
UPDATE Utilizatori SET nume_utilizator='bobt';
UPDATE Utilizatori SET nume_utilizator='tom'
WHERE cod_u=2;
UPDATE Utilizatori SET nume_utilizator='tomt', email='tom_t@gmail.com' 
WHERE cod_u=2;

--stergerea datelor

DELETE FROM Utilizatori WHERE cod_u=2;
DELETE FROM Utilizatori;


INSERT INTO Utilizatori (nume_utilizator, email, parola)
VALUES ('bob', 'bob@gmail.com', 'dvaa949a48tg9'),
('tom', 'tom@gmail.com', 'efghw9545' );

SELECT * FROM Utilizatori WHERE nume_utilizator='tom';


