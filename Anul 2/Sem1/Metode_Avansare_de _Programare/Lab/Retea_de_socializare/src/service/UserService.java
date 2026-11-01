package service;

import exceptions.DuplicateEntityException;
import exceptions.EntityNotFoundException;
import model.Friendship;
import model.FriendshipCriteria;
import model.Tuple;
import model.User;
import repository.Repository;

import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;

/**
 * Logica aplicatiei pentru utilizatori.
 */
public class UserService {

    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;

    /**
     * @param userRepository       - repository-ul de utilizatori
     * @param friendshipRepository - repository-ul de prietenii
     */
    public UserService(Repository<Long, User> userRepository,
                       Repository<Tuple<Long, Long>, Friendship> friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    /**
     * adauga un utilizator nou, cu id generat automat
     *
     * @param firstName - prenumele utilizatorului
     * @param lastName  - numele utilizatorului
     * @param email     - adresa de email a utilizatorului
     * @param password  - parola utilizatorului
     * @return utilizatorul adaugat
     * @throws exceptions.ValidationException daca datele nu sunt valide
     * @throws DuplicateEntityException       daca id-ul exista deja
     */
    public User addUser(String firstName, String lastName, String email, String password) {
        User user = new User(firstName, lastName, email, password);
        user.setId(generateId());
        if (userRepository.save(user) != null) {
            throw new DuplicateEntityException("User with id " + user.getId() + " already exists");
        }
        return user;
    }

    /**
     * sterge un utilizator si toate prieteniile lui
     *
     * @param id - id-ul utilizatorului
     * @return utilizatorul sters
     * @throws EntityNotFoundException daca utilizatorul nu exista
     */
    public User removeUser(Long id) {
        User removed = Optional.ofNullable(userRepository.delete(id))
                .orElseThrow(() -> new EntityNotFoundException("User with id " + id + " not found"));

        friendshipRepository.findAll(FriendshipCriteria.involvesUser(id))
                .stream()
                .map(Friendship::getId)
                .forEach(friendshipRepository::delete);

        return removed;
    }

    /**
     * cauta un utilizator dupa id
     *
     * @param id - id-ul utilizatorului
     * @return Optional cu utilizatorul gasit sau Optional gol daca nu exista
     */
    public Optional<User> findUser(Long id) {
        return Optional.ofNullable(userRepository.findOne(id));
    }

    /**
     * @return toti utilizatorii, sortati dupa nume, apoi dupa prenume
     */
    public List<User> getAllUsers() {
        return userRepository.stream()
                .sorted(Comparator.comparing(User::getLastName).thenComparing(User::getFirstName))
                .toList();
    }

    /**
     * cauta utilizatorii care respecta un criteriu
     *
     * @param criteria - criteriul de cautare (Predicate), de exemplu din UserCriteria
     * @return utilizatorii care respecta criteriul, sortati dupa nume, apoi dupa prenume
     */
    public List<User> searchUsers(Predicate<User> criteria) {
        return userRepository.findAll(criteria).stream()
                .sorted(Comparator.comparing(User::getLastName).thenComparing(User::getFirstName))
                .toList();
    }

    /**
     * @return urmatorul id liber: cel mai mare id existent + 1 (sau 1 daca nu exista utilizatori)
     */
    private Long generateId() {
        return userRepository.stream()
                .mapToLong(User::getId)
                .max()
                .orElse(0) + 1;
    }
}