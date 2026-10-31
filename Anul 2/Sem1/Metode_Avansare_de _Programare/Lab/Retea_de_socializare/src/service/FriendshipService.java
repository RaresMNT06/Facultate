package service;

import exceptions.DuplicateEntityException;
import exceptions.EntityNotFoundException;
import model.Friendship;
import model.User;
import model.Tuple;
import repository.Repository;

import java.util.ArrayList;
import java.util.List;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;


/**
 * Logica aplicatiei pentru prietenii.
 */
public class FriendshipService {

    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;

    /**
     * @param userRepository       repository-ul de utilizatori
     * @param friendshipRepository repository-ul de prietenii
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
        if (friendshipRepository.delete(id) == null) {
            throw new EntityNotFoundException("Friendship " + userId1 + " and " + userId2 + " not found");
        }
    }
    /**
     * @param userId - id-ul utilizatorului
     * @return lista prietenilor utilizatorului (prieteniile cu utilizatori inexistenti sunt ignorate)
     * @throws EntityNotFoundException daca utilizatorul nu exista
     */
    public List<User> getFriends(Long userId) {
        checkUserExist(userId);
        List<User> friends = new ArrayList<>();
        for (Friendship friendship : friendshipRepository.findAll()) {
            Long friendId = null;
            if (friendship.getUserId1().equals(userId)) {
                friendId = friendship.getUserId2();
            } else if (friendship.getUserId2().equals(userId)) {
                friendId = friendship.getUserId1();
            }
            if (friendId != null) {
                User friend = userRepository.findOne(friendId);
                if (friend != null) {
                    friends.add(friend);
                }
            }
        }
        return friends;
    }

    /**
     * @return toate prieteniile
     */
    public Iterable<Friendship> getFriendships(){
        return friendshipRepository.findAll();
    }

    private void checkUserExist(Long userId){
        if (userRepository.findOne(userId) == null) {
            throw new EntityNotFoundException("User with id "+ userId +" not found");
        }
    }
}
