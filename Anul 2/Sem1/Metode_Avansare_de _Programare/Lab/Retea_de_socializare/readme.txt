=====================================================================
Laborator 4 - MAP: Refactorizare in stil Java 8
Interfete functionale, expresii lambda, referinte la metode, Optional, Stream API
=====================================================================

Aplicatia face exact ce facea la laboratorul 3 (aceleasi fisiere, acelasi format,
aceleasi mesaje pentru fisier lipsa si linii corupte). S-a schimbat doar codul:
buclele clasice au fost inlocuite cu stream-uri, iar comportamentul se transmite
ca parametru (lambda, referinte la metode).

Istoric Git: branch-ul main contine laboratorul 3 (inainte), iar branch-ul
lab4-refactoring contine refactorizarea (dupa), cate un commit pentru fiecare pas.

1. BUCLE INLOCUITE (INAINTE / DUPA)

Clasa / metoda                         | Inainte (Lab 3)                      | Dupa (Lab 4)
---------------------------------------|--------------------------------------|----------------------------------------------
UserService.generateId                 | for + if (id > max)                  | stream().mapToLong(User::getId).max().orElse(0)
UserService.removeUser                 | 2 bucle for (colectare + stergere)   | findAll(involvesUser(id)).stream().map(Friendship::getId)
                                       |                                      | .forEach(friendshipRepository::delete)
FriendshipService.getFriends           | for + if/else if + if (!= null) + add| findAll(involvesUser).stream().map(...).map(Optional::ofNullable)
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
- metoda statica            : UserCriteria::hasGmail
- metoda unui obiect anume  : System.out::println, friendshipRepository::delete,
                              userRepository::findOne, this::createEntityAsString
- metoda unui obiect oarecare: User::getLastName, User::getId, Friendship::getId, Tuple::getLeft
- constructor               : InMemoryRepository::new (in RepositoryFactory)

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
Repository (OCP, ISP).