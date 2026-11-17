-- Laboratorul 5: baza de date a retelei de socializare (socialnetwork)
-- 1. pgAdmin: Databases -> Create -> Database..., numele: socialnetwork
-- 2. Click dreapta pe socialnetwork -> Query Tool, deschideti acest fisier si rulati-l (F5).
-- Scriptul nu sterge nimic si poate fi rulat de mai multe ori.

-- id-ul il genereaza baza de date (GENERATED ALWAYS AS IDENTITY), nu il dam in INSERT
CREATE TABLE IF NOT EXISTS users (
    id         BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    first_name VARCHAR NOT NULL,
    last_name  VARCHAR NOT NULL,
    email      VARCHAR NOT NULL UNIQUE,   -- coloana in plus: User-ul are email
    password   VARCHAR NOT NULL           -- coloana in plus: User-ul are parola
);

-- o prietenie (id1, id2) se salveaza o singura data, cu id1 < id2;
-- ON DELETE CASCADE: prieteniile unui utilizator sters dispar automat
CREATE TABLE IF NOT EXISTS friendships (
                                           id1          BIGINT REFERENCES users (id) ON DELETE CASCADE,
    id2          BIGINT REFERENCES users (id) ON DELETE CASCADE,
    friends_from TIMESTAMP NOT NULL,
    PRIMARY KEY (id1, id2),
    CHECK (id1 < id2)
    );

-- utilizatorii de test (aceiasi ca in data/users.txt), adaugati doar daca emailul nu exista;
-- nr: doar ordinea inserarii (ca id-urile sa iasa 1..6), nu este id-ul
INSERT INTO users (first_name, last_name, email, password)
SELECT v.first_name, v.last_name, v.email, v.password
FROM (VALUES (1, 'Ion',   'Pop',      'ion@gmail.com',   'parola123'),
             (2, 'Ana',   'Ilie',     'ana@gmail.com',   'anaparola'),
             (3, 'Dan',   'Rus',      'dan@gmail.com',   'danparola'),
             (4, 'Maria', 'Pop',      'maria@gmail.com', 'maria2026'),
             (5, 'Vlad',  'Ene',      'vlad@gmail.com',  'vladparola'),
             (6, 'Ioana', 'Moldovan', 'ioana@gmail.com', 'ioana2026'))
         AS v(nr, first_name, last_name, email, password)
WHERE NOT EXISTS (SELECT 1 FROM users u WHERE u.email = v.email)
ORDER BY v.nr;
-- prieteniile (aceleasi ca in data/friendships.txt), date prin email;
-- LEAST / GREATEST pun id-ul mai mic primul (respecta CHECK id1 < id2)
INSERT INTO friendships (id1, id2, friends_from)
SELECT LEAST(a.id, b.id), GREATEST(a.id, b.id), p.friends_from
FROM (VALUES ('ion@gmail.com',  'ana@gmail.com',   TIMESTAMP '2026-10-19 10:30'),
             ('ana@gmail.com',  'dan@gmail.com',   TIMESTAMP '2026-10-19 11:00'),
             ('dan@gmail.com',  'maria@gmail.com', TIMESTAMP '2026-10-20 09:15'),
             ('vlad@gmail.com', 'ioana@gmail.com', TIMESTAMP '2026-10-20 18:45'))
         AS p(email1, email2, friends_from)
         JOIN users a ON a.email = p.email1
         JOIN users b ON b.email = p.email2
    ON CONFLICT DO NOTHING;

SELECT * FROM users ORDER BY id;
SELECT * FROM friendships ORDER BY id1, id2;