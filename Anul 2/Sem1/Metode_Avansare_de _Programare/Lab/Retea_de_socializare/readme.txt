==================================================================
LABORATORUL 5 - Persistenta in PostgreSQL (JDBC)
==================================================================

1. PORNIRE
------------------------------------------------------------------
- Proiectul este acum Gradle (build.gradle.kts); driverul JDBC
  org.postgresql:postgresql:42.7.7 este o dependenta Gradle.
- Gradle Wrapper 9.2.0 (prima versiune stabila care merge pe Java 25).
- Baza de date: in pgAdmin se creeaza baza "socialnetwork", apoi
  se ruleaza sql/socialnetwork.sql (Query Tool, F5). Scriptul poate
  fi rulat de mai multe ori (IF NOT EXISTS / ON CONFLICT DO NOTHING).
- Configurare: se copiaza src/main/resources/config.example.properties
  ca config.properties si se completeaza db.password.
  config.properties (cu parola reala) este in .gitignore.
- Tipul stocarii se schimba DOAR din config.properties:
  repository.type = MEMORY | FILE | DATABASE

2. BAZA DE DATE
------------------------------------------------------------------
users(id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
      first_name, last_name, email UNIQUE, password)  - toate NOT NULL
friendships(id1, id2 -> users(id) ON DELETE CASCADE,
            friends_from TIMESTAMP NOT NULL,
            PRIMARY KEY (id1, id2), CHECK (id1 < id2))

Decizii:
- Coloanele email si password sunt in plus fata de enunt, pentru ca
  User are email si parola inca din laboratorul 3.
- email este UNIQUE: doi utilizatori nu pot avea acelasi email.
- Stergerea prieteniilor unui utilizator sters: AMBELE variante.
  * ON DELETE CASCADE in baza de date: baza ramane consistenta si
    daca un utilizator e sters direct din pgAdmin.
  * Stergerea explicita in UserService.removeUser: este necesara
    pentru FILE si MEMORY, unde nu exista CASCADE. Ordinea este
    intai prieteniile, apoi utilizatorul, deci functioneaza si
    fara CASCADE (cheia straina nu este incalcata).

3. REPOSITORY-URILE JDBC
------------------------------------------------------------------
- UserDbRepository, FriendshipDbRepository implementeaza
  Repository<ID, E>; nu pastreaza nimic in memorie.
- Conexiunea: DriverManager.getConnection(url, user, password),
  cu parametrii primiti de la RepositoryFactory (din config).
- Connection, PreparedStatement, ResultSet: try-with-resources.
- Toate valorile se trimit prin PreparedStatement cu ? (setString,
  setLong, setTimestamp), niciodata prin concatenare -> fara SQL
  injection (testat cu numele  X'); DROP TABLE users; --).
- Contractul Repository: findOne -> null daca nu exista; save/update
  valideaza inainte; update pentru id inexistent intoarce entitatea
  (executeUpdate() == 0); delete intoarce entitatea stearsa;
  argument null -> IllegalArgumentException.

4. ID-UL GENERAT DE STOCARE
------------------------------------------------------------------
- UserService nu mai genereaza id-ul (generateId a fost scos).
- DATABASE: INSERT fara id + RETURN_GENERATED_KEYS ->
  getGeneratedKeys() -> entity.setId(...).
- FILE / MEMORY: InMemoryRepository.generateId() (Template Method,
  implicit null), suprascrisa in UserFileRepository si in
  UserInMemoryRepository (max + 1).
- UserValidator accepta id null (utilizator nou), dar respinge id <= 0.
- UI-ul afiseaza id-ul primit: "Added user with id N: ...".
- PostgreSQL nu refoloseste id-urile sterse (IDENTITY doar creste).

5. EXCEPTII
------------------------------------------------------------------
- SQLException se impacheteaza in RepositoryException (unchecked)
  prin DbErrors.wrap, care alege mesajul dupa SQLState:
    08xxx -> serverul nu raspunde (oprit)
    28xxx -> user / parola gresite
    3D000 -> baza de date nu exista
    23505 -> valoare duplicata (email)
    23503 -> cheie straina (utilizator inexistent)
    23514 -> CHECK incalcat
  Cauza originala se pastreaza (exception chaining).
- ConsoleUI afiseaza "Storage error: <mesaj>", fara stack trace,
  fara catch gol si fara catch (Exception e).

6. ALTE MODIFICARI
------------------------------------------------------------------
- Regula "fara ';'" s-a mutat din UserValidator in UserFileRepository:
  ';' este separatorul fisierului, deci este o regula a formatului
  de fisier, nu a domeniului. In baza de date ';' este text obisnuit.
- Lungimea maxima a numelui (regula lambda din Main) a crescut de la
  20 la 50, ca sa permita testul de SQL injection.
- Codul a fost mutat in src/main/java (structura Gradle);
  pachetele au ramas aceleasi.

7. DEMONSTRATIE
------------------------------------------------------------------
- CRUD verificat in pgAdmin (SELECT * FROM users / friendships).
- Id generat: Add user -> "Added user with id N".
- Datele raman dupa repornirea aplicatiei.
- repository.type schimbat intre DATABASE / FILE / MEMORY.
- Server oprit (services.msc -> Stop) -> mesaj "cannot connect...".
- Email duplicat -> mesaj "the value already exists...".
- Nume  X'); DROP TABLE users; --  salvat ca text obisnuit.