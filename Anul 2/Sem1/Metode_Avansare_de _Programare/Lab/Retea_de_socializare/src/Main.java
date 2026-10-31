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

            Repository<Long, User> userRepository =
                    factory.createUserRepository(new UserValidator());
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