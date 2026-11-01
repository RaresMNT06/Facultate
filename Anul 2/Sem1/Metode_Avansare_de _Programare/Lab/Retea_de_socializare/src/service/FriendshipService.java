package service;

import exceptions.DuplicateEntityException;
import exceptions.EntityNotFoundException;
import model.Friendship;
import model.FriendshipCriteria;
import model.Tuple;
import model.User;
import repository.Repository;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;

/**
 * Logica aplicatiei pentru prietenii.
 */
public class FriendshipService {

    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;

    /**
     * @param userRepository       - repository-ul de utilizatori
     * @param friendshipRepository - repository-ul de prietenii
     */
    public FriendshipService(Repository<Long, User> userRepository,
                             Repository<Tuple<Long, Long>, Friendship> friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    /**
     * adauga o prietenie intre doi utilizatori, cu data si ora curenta
     *
     * @param userId1 - id-ul primului utilizator
     * @param userId2 - id-ul celui de-al doilea utilizator
     * @throws EntityNotFoundException        daca unul dintre utilizatori nu exista
     * @throws DuplicateEntityException       daca prietenia exista deja
     * @throws exceptions.ValidationException daca cei doi utilizatori sunt identici
     */
    public void addFriendship(Long userId1, Long userId2) {
        checkUserExist(userId1);
        checkUserExist(userId2);
        LocalDateTime now = LocalDateTime.now().truncatedTo(ChronoUnit.MINUTES);
        Friendship friendship = new Friendship(userId1, userId2, now);
        if (friendshipRepository.save(friendship) != null) {
            throw new DuplicateEntityException("Friendship " + userId1 + " and " + userId2 + " already exists");
        }
    }

    /**
     * sterge prietenia dintre doi utilizatori
     *
     * @param userId1 - id-ul primului utilizator
     * @param userId2 - id-ul celui de-al doilea utilizator
     * @throws EntityNotFoundException daca prietenia nu exista
     */
    public void removeFriendship(Long userId1, Long userId2) {
        Tuple<Long, Long> id = new Tuple<>(Math.min(userId1, userId2), Math.max(userId1, userId2));
        Optional.ofNullable(friendshipRepository.delete(id))
                .orElseThrow(() -> new EntityNotFoundException(
                        "Friendship " + userId1 + " and " + userId2 + " not found"));
    }

    /**
     * @param userId - id-ul utilizatorului
     * @return prietenii utilizatorului, sortati dupa nume si prenume
     * (prieteniile cu utilizatori inexistenti sunt ignorate)
     * @throws EntityNotFoundException daca utilizatorul nu exista
     */
    public List<User> getFriends(Long userId) {
        checkUserExist(userId);
        return friendshipRepository.findAll(FriendshipCriteria.involvesUser(userId)).stream()
                .map(f -> f.getUserId1().equals(userId) ? f.getUserId2() : f.getUserId1())
                .map(friendId -> Optional.ofNullable(userRepository.findOne(friendId)))
                .flatMap(Optional::stream)
                .sorted(Comparator.comparing(User::getLastName).thenComparing(User::getFirstName))
                .toList();
    }

    /**
     * @return toate prieteniile, sortate dupa data la care au fost create
     */
    public List<Friendship> getFriendships() {
        return friendshipRepository.stream()
                .sorted(Comparator.comparing(Friendship::getFriendsFrom))
                .toList();
    }

    /**
     * @param userId - id-ul utilizatorului verificat
     * @throws EntityNotFoundException daca utilizatorul nu exista
     */
    private void checkUserExist(Long userId) {
        Optional.ofNullable(userRepository.findOne(userId))
                .orElseThrow(() -> new EntityNotFoundException("User with id " + userId + " not found"));
    }
}