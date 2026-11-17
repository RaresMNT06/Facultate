import exceptions.ConfigurationException;
import exceptions.RepositoryException;
import model.Friendship;
import model.Tuple;
import model.User;
import repository.Repository;
import repository.factory.RepositoryFactory;
import service.CommunityService;
import service.FriendshipService;
import service.UserService;
import ui.ConsoleUI;
import validators.FriendshipValidator;
import validators.UserValidator;
import exceptions.ValidationException;
import validators.Validator;

/**
 * Punctul de intrare al aplicatiei: creeaza repository-urile prin factory,
 * asambleaza service-urile si interfata cu utilizatorul si porneste aplicatia.
 */
public class Main {

    /**
     * @param args - argumentele din linia de comanda (nefolosite)
     */
    public static void main(String[] args) {
        try {
            RepositoryFactory factory = new RepositoryFactory();
            System.out.println("Persistence: " + factory.getType());

            int maxNameLength = 20;
            Validator<User> nameLengthRule = u -> {
                if (u.getFirstName().length() > maxNameLength || u.getLastName().length() > maxNameLength) {
                    throw new ValidationException("first name and last name must have at most "
                            + maxNameLength + " characters");
                }
            };
            Validator<User> userValidator = new UserValidator().andThen(nameLengthRule);

            Repository<Long, User> userRepository = factory.createUserRepository(userValidator);
            Repository<Tuple<Long, Long>, Friendship> friendshipRepository =
                    factory.createFriendshipRepository(new FriendshipValidator());

            UserService userService = new UserService(userRepository, friendshipRepository);
            FriendshipService friendshipService = new FriendshipService(userRepository, friendshipRepository);
            CommunityService communityService = new CommunityService(userRepository, friendshipRepository);

            ConsoleUI ui = new ConsoleUI(userService, friendshipService, communityService);
            ui.run();
        } catch (ConfigurationException e) {
            System.out.println("Configuration error: " + e.getMessage());
        } catch (RepositoryException e) {
            System.out.println("Cannot start the application: " + e.getMessage());
        }
    }
}