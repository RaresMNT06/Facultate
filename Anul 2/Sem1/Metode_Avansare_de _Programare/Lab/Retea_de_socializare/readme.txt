=====================================================================
Laborator 3 - MAP: Retea de socializare
Persistenta in fisiere text, exceptii si Repository Factory
=====================================================================

1. STRUCTURA PROIECTULUI
- model         : Entity, Tuple, User, Friendship (entitatile domeniului);
                  UserCriteria, FriendshipCriteria (criterii de cautare, adaugate la laboratorul 4)
- validators    : Validator (interfata), UserValidator, FriendshipValidator
- exceptions    : ValidationException, RepositoryException, ConfigurationException,
                  EntityNotFoundException, DuplicateEntityException (toate unchecked)
- repository    : Repository (interfata CRUD), InMemoryRepository
    - file      : AbstractFileRepository, UserFileRepository, FriendshipFileRepository
    - db        : UserDbRepository, FriendshipDbRepository (schelete pentru laboratorul 5)
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
- createUserRepository(validator) si createFriendshipRepository(validator) aleg
  implementarea potrivita si intorc tipul abstract Repository<ID, E>:
    MEMORY   -> InMemoryRepository
    FILE     -> UserFileRepository / FriendshipFileRepository (cai: file.users, file.friendships)
    DATABASE -> UserDbRepository / FriendshipDbRepository (db.url, db.user, db.password)
  (la laboratorul 3 alegerea se facea cu un switch clasic; la laboratorul 4 a fost
  inlocuit cu un Map de functii, vezi sectiunea Laborator 4.)
- Ambele repository-uri sunt create pentru acelasi tip de persistenta.
- Fisier de configurare lipsa, cheie lipsa sau valoare necunoscuta -> ConfigurationException
  cu mesaj clar, prinsa in Main.

Ce trebuie schimbat pentru trecerea la baza de date (laboratorul 5):
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
      validare este o clasa noua care implementeaza Validator (sau, de la laboratorul 4,
      o lambda compusa cu andThen).
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
Decorator - la laboratorul 3, fluxurile de fisiere: BufferedReader decora FileReader
      (adauga buffer si readLine), BufferedWriter decora FileWriter. La laboratorul 4
      citirea si scrierea au trecut la java.nio.file (Files.lines, Files.write).

7. SIMPLE FACTORY vs ABSTRACT FACTORY
Simple Factory (varianta aleasa): o singura clasa care alege dupa RepositoryType.
  + simplu, tot codul de creare intr-un singur loc;
  - un tip nou de persistenta cere modificarea factory-ului (incalca OCP).
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
db.url, db.user, db.password    (folosite la laboratorul 5)

10. RESTRICTII RESPECTATE LA LABORATORUL 3
Fara lambda, method references si stream-uri; switch in forma clasica; fara serializare
binara si fara biblioteci externe pentru fisiere; cai relative; fisiere UTF-8.
(La laboratorul 4 lambda, referintele la metode si stream-urile au devenit obligatorii.)


=====================================================================
Laborator 4 - MAP: Refactorizare in stil Java 8
Interfete functionale, expresii lambda, referinte la metode, Optional, Stream API
=====================================================================

Aplicatia face exact ce facea la laboratorul 3 (aceleasi fisiere, acelasi format,
aceleasi mesaje pentru fisier lipsa si linii corupte). S-a schimbat doar codul:
buclele clasice au fost inlocuite cu stream-uri, iar comportamentul se transmite
ca parametru (lambda, referinte la metode).

Istoric Git: commit-ul "MAP: ... Lab 3 final" (000904c) este starea de dinainte;
refactorizarea a fost facuta pe branch-ul lab4-refactoring, cate un commit pentru
fiecare pas, apoi integrata in main (merge) si publicata pe GitHub.

1. BUCLE INLOCUITE (INAINTE / DUPA)

Clasa / metoda                         | Inainte (Lab 3)                      | Dupa (Lab 4)
---------------------------------------|--------------------------------------|----------------------------------------------
UserService.generateId                 | for + if (id > max)                  | stream().mapToLong(User::getId).max().orElse(0)
UserService.removeUser                 | 2 bucle for (colectare + stergere)   | findAll(involvesUser(id)).stream().map(Friendship::getId)
                                       |                                      | .forEach(friendshipRepository::delete)
FriendshipService.getFriends           | for + if/else if + if (!= null) + add| findAll(involvesUser).stream().map(celalalt id)
                                       |                                      | .map(id -> Optional.ofNullable(findOne(id)))
                                       |                                      | .flatMap(Optional::stream).sorted(...).toList()
CommunityService.buildGraph            | 2 bucle for + put/add                | flatMap (o prietenie -> 2 muchii) + groupingBy + toMap
CommunityService.getCommunities        | for pe noduri + if (!visited)        | keySet().stream().map(reachableFrom).distinct().toList()
CommunityService.dfs                   | for pe vecini + if                   | stream().filter(v -> !visited.contains(v)).forEach(dfs)
CommunityService.getMostSociable...    | for + if (length > best)             | max(Comparator.comparingInt(...)) -> Optional.map(...).orElse
CommunityService.longestPathFrom       | for + if (backtracking)              | stream().filter(...).mapToInt(...).max().orElse(0)
AbstractFileRepository.loadData        | while (readLine() != null) + contor  | Files.lines (try-with-resources) + IntStream.range(...).forEach
AbstractFileRepository.writeToFile     | for + writer.write                   | stream().map(this::createEntityAsString).toList() + Files.write
Repository.findAll(Predicate)          | (nou; la seminar cu for)             | stream().filter(filter).toList()
ConsoleUI.showUsers/Friendships/...    | for + System.out.println             | forEach(System.out::println)

2. INTERFETE FUNCTIONALE FOLOSITE

- Validator<T> (proprie)  : @FunctionalInterface, metoda default andThen; regula noua
                            "nume <= 20 caractere" scrisa ca lambda in Main si compusa cu
                            new UserValidator().andThen(...), fara clasa noua.
- Predicate<T>            : criteriile din UserCriteria si FriendshipCriteria;
                            Repository.findAll(Predicate); combinate cu and si Predicate.not
                            in ConsoleUI (Search users); filter in stream-uri.
- Function<T, R>          : map in stream-uri; creatorii din RepositoryFactory
                            (Function<Validator<E>, Repository<ID, E>>).
- Consumer<T>             : forEach (System.out::println, friendshipRepository::delete).
- Comparator<T>           : sortari cu comparing / thenComparing / comparingInt
                            (utilizatori dupa nume si prenume, prietenii dupa data,
                            comunitatea cu drumul maxim).
- Supplier<T>             : orElseThrow(() -> new ...Exception(...)).

Referinte la metode (toate cele 4 tipuri):
- metoda statica             : UserCriteria::hasGmail
- metoda unui obiect anume   : System.out::println, friendshipRepository::delete,
                               userRepository::findOne, this::createEntityAsString
- metoda unui obiect oarecare: User::getLastName, User::getId, Friendship::getId, Tuple::getLeft
- constructor                : InMemoryRepository::new (in RepositoryFactory)

3. RepositoryFactory FARA switch
Fiecarui RepositoryType ii corespunde, intr-un Map construit o singura data in
constructor, o Function<Validator<E>, Repository<ID, E>>. Se executa doar creatorul
tipului ales (lazy): la MEMORY nu se citesc fisierele. Un tip fara creator produce
ConfigurationException (Optional.ofNullable(...).orElseThrow(...)).
Un tip nou de persistenta = o constanta noua in enum + o intrare noua in map.

4. DECIZIA PENTRU Optional IN Repository
Interfata Repository intoarce in continuare null (contractul din seminarul 3).
Motiv: nu modificam contractul si toate implementarile (memorie, fisier, baza de date).
Optional se foloseste in service, acolo unde rezultatul poate lipsi:
UserService.findUser (Optional.ofNullable(repo.findOne(id))), removeUser,
FriendshipService.checkUserExist si removeFriendship (orElseThrow),
getFriends (flatMap(Optional::stream)), CommunityService (max -> Optional),
generateId (OptionalLong.orElse). Nu se apeleaza get() fara verificare.

5. TEMPLATE METHOD vs Function LA FISIERE
Am pastrat Template Method (AbstractFileRepository cu subclasele UserFileRepository si
FriendshipFileRepository). Conversia linie <-> entitate are un nume si un loc propriu,
documentat si testabil separat. Alternativa, un singur FileRepository<ID, E> care primeste
Function<String, E> si Function<E, String> (compozitie in loc de mostenire), ar elimina
subclasele si apelul metodei abstracte din constructor, dar conversia ar deveni o lambda
fara nume, scrisa la crearea repository-ului.
Citirea foloseste Files.lines intr-un try-with-resources; liniile sunt parcurse cu
IntStream.range ca sa se pastreze numarul liniei pentru liniile corupte. Scrierea foloseste
Files.write cu liniile obtinute printr-un stream peste entitati. IOException si
UncheckedIOException sunt impachetate in RepositoryException.

6. BUCLE PASTRATE
- ConsoleUI.run: while (true) pentru meniu; nu parcurge o colectie, ci repeta
  citirea optiunii pana la iesire.
- Nu a ramas nicio bucla pentru parcurgerea colectiilor. Backtracking-ul pentru cel mai
  lung drum este scris recursiv cu stream-uri (filter + mapToInt + max). In DFS si in
  backtracking stream-ul modifica multimea visited: este o multime locala, creata doar
  pentru parcurgere, iar varianta urmeaza sugestia din enunt
  (filter(v -> !vizitat.contains(v))).

7. CRITERII DE CAUTARE
- UserCriteria: firstNameStartsWith, hasLastName, hasEmailDomain (intorc Predicate<User>),
  hasGmail (boolean, folosita ca referinta la metoda statica).
- FriendshipCriteria: involvesUser (folosit in removeUser si getFriends), createdAfter.
Un criteriu nou se adauga ca metoda noua sau direct ca lambda, fara metode findByX in
Repository (OCP, ISP). In ConsoleUI, optiunea 10 (Search users) combina criteriile cu
and si Predicate.not.