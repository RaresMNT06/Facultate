USE formula_1;
GO


SELECT * FROM Circuite WHERE id_circuit = 1; 

UPDATE Circuite
SET capacitate = 120000
WHERE id_circuit = 1;



SELECT * FROM Circuite;


INSERT INTO Circuite(nume, oras, lungime_km, capacitate, id_tara)
VALUES ('Autodromo Enzo e Dino Ferrari', 'Imola', 4.909, 78000, 1);



