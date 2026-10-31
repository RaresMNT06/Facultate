package service;

import exceptions.DuplicateEntityException;
import exceptions.EntityNotFoundException;
import model.Friendship;
import model.User;
import model.Tuple;
import repository.Repository;

import java.util.ArrayList;
import java.util.List;


/**
 * Logica aplicatiei pentru utilizatori.
 */
public class UserService {
    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;

    /**
     * @param userRepository       repository-ul de utilizatori
     * @param friendshipRepository repository-ul de prietenii
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
     * Sterge un utilizator si toate prieteniile lui.
     *
     * @param id id-ul utilizatorului
     * @return utilizatorul sters
     * @throws EntityNotFoundException daca utilizatorul nu exista
     */
    public User removeUser(Long id){
        User removed = userRepository.delete(id);
        if(removed == null){
            throw new EntityNotFoundException("User with id " + id + " not found");
        }

        List<Tuple<Long,Long>> toDelete = new ArrayList<>();
        for(Friendship friendship : friendshipRepository.findAll()){
            if(friendship.getUserId1().equals(id) || friendship.getUserId2().equals(id)){
                toDelete.add(friendship.getId());
            }
        }
        for(Tuple<Long,Long> friendshipId : toDelete){
            friendshipRepository.delete(friendshipId);
        }
        return removed;
    }

    /**
     * @return toti utilizatorii
     */
    public Iterable<User> getAllUsers() {
        return userRepository.findAll();
    }

    private Long generateId(){
        long maxId = 0;
        for (User user : userRepository.findAll()){
            if (user.getId() > maxId){
                maxId = user.getId();
            }
        }
        return maxId + 1;
    }
}

