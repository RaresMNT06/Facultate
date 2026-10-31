Laborator 3 - MAP: Retea de socializare
Persistenta in fisiere text, exceptii si Repository Factory

1. STRUCTURA PROIECTULUI
- model         : Entity, Tuple, User, Friendship (entitatile domeniului)
- validators    : Validator (interfata), UserValidator, FriendshipValidator
- exceptions    : ValidationException, RepositoryException, ConfigurationException,
                  EntityNotFoundException, DuplicateEntityException (toate unchecked)
- repository    : Repository (interfata CRUD), InMemoryRepository
    - file      : AbstractFileRepository, UserFileRepository, FriendshipFileRepository
    - db        : UserDbRepository, FriendshipDbRepository (schelete pentru laboratorul 4)
    - factory   : RepositoryType (MEMORY, FILE, DATABASE), RepositoryFactory
- service       : UserService, FriendshipService, CommunityService
- ui            : ConsoleUI
- Main          : asambleaza aplicatia
- src/main/resources/config.properties : configurarea persistentei
- data/         : fisierele cu date si fisierele de test cu linii corupte

2. FORMATUL FISIERELOR
Fisierele sunt text, UTF-8, cate o entitate pe linie, campurile separate prin ';'.
- data/users.txt       : id;prenume;nume;email;parola
- data/friendships.txt : idUtilizator1;idUtilizator2;dataPrieteniei (ISO, ex: 2026-10-19T10:30)
Observatii:
- formatul utilizatorilor este extins fata de enunt (id;prenume;nume) cu email si parola,
  necesare pentru functionalitatile urmatoare (autentificare);
- numele fisierelor sunt in engleza, ca toate numele din proiect
  (users.txt = utilizatori.txt, friendships.txt = prietenii.txt);
- id-ul unei prietenii este normalizat (id-ul mai mic primul), deci 1;2 si 2;1
  reprezinta aceeasi prietenie.

3. CUM FUNCTIONEAZA FACTORY-UL
RepositoryFactory este un Simple Factory si este singurul loc din aplicatie care
cunoaste clasele concrete de repository.
- La creare citeste src/main/resources/config.properties cu java.util.Properties,
  intr-un try-with-resources.
- Cheia repository.type este transformata in enum-ul RepositoryType.
- createUserRepository(validator) si createFriendshipRepository(validator) aleg cu un
  switch clasic implementarea potrivita si intorc tipul abstract Repository<ID, E>:
    MEMORY   -> InMemoryRepository
    FILE     -> UserFileRepository / FriendshipFileRepository (cai: file.users, file.friendships)
    DATABASE -> UserDbRepository / FriendshipDbRepository (db.url, db.user, db.password)
- Ambele repository-uri sunt create pentru acelasi tip de persistenta.
- Fisier de configurare lipsa, cheie lipsa sau valoare necunoscuta -> ConfigurationException
  cu mesaj clar, prinsa in Main.

Ce trebuie schimbat pentru trecerea la baza de date (laboratorul 4):
- se scrie codul JDBC in metodele din UserDbRepository si FriendshipDbRepository
  (acum arunca UnsupportedOperationException);
- se adauga driverul JDBC in proiect;
- in config.properties se seteaza repository.type=DATABASE si datele reale de conectare.
Service-urile, ConsoleUI si Main raman neschimbate, pentru ca depind doar de interfata Repository.

4. FISIER LIPSA SI LINII CORUPTE
Fisier lipsa: aplicatia porneste cu repository-ul gol si afiseaza un mesaj; fisierul
(si folderul data/, daca lipseste) se creeaza la prima salvare.

Linie corupta sau invalida: linia este RAPORTATA (fisierul, numarul liniei si motivul)
si IGNORATA; incarcarea continua cu urmatoarea linie.
- erorile de format (NumberFormatException, DateTimeParseException, campuri lipsa) sunt
  impachetate intr-o RepositoryException (exception chaining, constructorul (message, cause));
- datele din fisier trec prin validator; o entitate invalida produce ValidationException;
- un id duplicat este raportat si ignorat.
Justificare: aplicatia ramane utilizabila cu datele corecte, iar utilizatorul vede exact ce
linie este gresita si de ce. Dezavantaj: la prima salvare fisierul este rescris doar cu
entitatile valide, deci liniile corupte se pierd.
Pentru consistenta, o prietenie cu un utilizator inexistent (fisier editat manual) este
ignorata la construirea grafului si la afisarea prietenilor.
Fisiere de test: data/users_corrupt.txt si data/friendships_corrupt.txt.

Celelalte exceptii (validare la adaugare, entitate inexistenta, duplicat, operatie
neimplementata pentru DATABASE) sunt prinse in ConsoleUI, unde se afiseaza un mesaj,
iar aplicatia continua. Nu se folosesc catch (Exception e) si nici blocuri catch goale.

5. PRINCIPII SOLID
SRP - fiecare clasa are un singur rol: entitatile retin date, validatoarele verifica,
      repository-urile pastreaza datele, service-urile contin regulile aplicatiei,
      ConsoleUI comunica cu utilizatorul, RepositoryFactory creeaza repository-urile.
OCP - o entitate noua se salveaza in fisier printr-o subclasa noua a lui
      AbstractFileRepository, fara a modifica codul de citire/scriere; o regula noua de
      validare este o clasa noua care implementeaza Validator.
LSP - InMemoryRepository, UserFileRepository si UserDbRepository pot fi folosite oriunde
      se cere un Repository<Long, User> si respecta contractul din Javadoc-ul interfetei
      (ex: findOne(null) si delete(null) arunca IllegalArgumentException).
DIP - service-urile, ConsoleUI si Main depind de interfata Repository, nu de clasele
      concrete; InMemoryRepository depinde de interfata Validator. Dependentele sunt primite
      prin constructor.

6. SABLOANE DE PROIECTARE
Factory (Simple Factory) - RepositoryFactory: creeaza repository-ul potrivit dupa configurare.
Template Method - AbstractFileRepository: loadData si writeToFile sunt scrise o singura data,
      iar pasii extractEntity si createEntityAsString sunt implementati in subclase.
Strategy - Validator: InMemoryRepository primeste o strategie de validare prin constructor
      si o aplica fara sa stie care este (UserValidator, FriendshipValidator).
Decorator - fluxurile de fisiere: BufferedReader decoreaza FileReader (adauga buffer si
      readLine), BufferedWriter decoreaza FileWriter.

7. SIMPLE FACTORY vs ABSTRACT FACTORY
Simple Factory (varianta aleasa): o singura clasa cu switch dupa RepositoryType.
  + simplu, tot codul de creare intr-un singur loc;
  - un tip nou de persistenta cere modificarea switch-ului (incalca OCP).
Abstract Factory: interfata RepositoryFactory cu cate o implementare pentru fiecare tip
(FileRepositoryFactory, DbRepositoryFactory).
  + un tip nou inseamna o clasa noua, fara a modifica codul existent (respecta OCP);
  - mai multe clase, iar alegerea implementarii tot trebuie facuta intr-un singur loc.
Am ales Simple Factory deoarece tipurile de persistenta sunt putine si fixe.

8. UNDE ESTE VALIDAREA
Validarea datelor unei entitati este in repository (InMemoryRepository apeleaza validatorul
la save si update), conform contractului din Repository (save arunca ValidationException).
Astfel nicio entitate invalida nu ajunge in repository, nici macar la incarcarea din fisier.
Regulile care au nevoie de alte date (utilizatorii exista, prietenia nu e duplicat,
stergerea unui utilizator ii sterge si prieteniile) sunt in service.

9. CONFIGURARE (src/main/resources/config.properties)
repository.type=FILE            (MEMORY, FILE sau DATABASE)
file.users=data/users.txt
file.friendships=data/friendships.txt
db.url, db.user, db.password    (folosite la laboratorul 4)

10. RESTRICTII RESPECTATE
Fara lambda, method references si stream-uri; switch in forma clasica; fara serializare
binara si fara biblioteci externe pentru fisiere; cai relative; fisiere UTF-8.