package ui;

import exceptions.DuplicateEntityException;
import exceptions.EntityNotFoundException;
import exceptions.RepositoryException;
import exceptions.ValidationException;
import model.Friendship;
import model.User;
import service.CommunityService;
import service.FriendshipService;
import service.UserService;

import java.util.List;
import java.util.Scanner;

/**
 * Interfata cu utilizatorul in consola.
 */

public class ConsoleUI {

    private final UserService userService;
    private final CommunityService communityService;
    private final FriendshipService friendshipService;
    private final Scanner scanner;

    /**
     * @param userService       service-ul de utilizatori
     * @param friendshipService service-ul de prietenii
     * @param communityService  service-ul de comunitati
     */

    public ConsoleUI(UserService userService, FriendshipService friendshipService,
                     CommunityService communityService) {
        this.userService = userService;
        this.communityService = communityService;
        this.friendshipService = friendshipService;
        this.scanner = new Scanner(System.in);
    }

    /**
     * Porneste bucla principala a aplicatiei.
     */
    public void run() {
        while (true) {
            printMenu();
            String option = scanner.nextLine().trim();
            try {
                switch (option) {
                    case "1": addUser(); break;
                    case "2": removeUser(); break;
                    case "3": addFriendship(); break;
                    case "4": removeFriendship(); break;
                    case "5": showUsers(); break;
                    case "6": showFriendships(); break;
                    case "7": showFriends(); break;
                    case "8": showCommunityCount(); break;
                    case "9": showMostSociableCommunity(); break;
                    case "0":
                        System.out.println("Bye!");
                        return;
                    default:
                        System.out.println("Invalid option.");
                }
            } catch (ValidationException | EntityNotFoundException | DuplicateEntityException e) {
                System.out.println("Error: " + e.getMessage());
            } catch (NumberFormatException e) {
                System.out.println("Error: id must be a number.");
            } catch (RepositoryException e) {
                System.out.println("File error: " + e.getMessage());
            } catch (UnsupportedOperationException e) {
                System.out.println("Not available: " + e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println();
        System.out.println("===== SOCIAL NETWORK =====");
        System.out.println("1. Add user");
        System.out.println("2. Remove user");
        System.out.println("3. Add friendship");
        System.out.println("4. Remove friendship");
        System.out.println("5. Show users");
        System.out.println("6. Show friendships");
        System.out.println("7. Show friends of a user");
        System.out.println("8. Number of communities");
        System.out.println("9. Most sociable community");
        System.out.println("0. Exit");
        System.out.print("Option: ");
    }

    private void addUser() {
        System.out.print("First name: ");
        String firstName = scanner.nextLine();
        System.out.print("Last name: ");
        String lastName = scanner.nextLine();
        System.out.print("Email: ");
        String email = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();
        User user = userService.addUser(firstName, lastName, email, password);
        System.out.println("Added: " + user);
    }

    private void removeUser() {
        Long id = readId("User id: ");
        User user = userService.removeUser(id);
        System.out.println("Removed: " + user);
    }


    private void addFriendship() {
        Long id1 = readId("First user id: ");
        Long id2 = readId("Second user id: ");
        friendshipService.addFriendship(id1, id2);
        System.out.println("Friendship added.");
    }

    private void removeFriendship() {
        Long id1 = readId("First user id: ");
        Long id2 = readId("Second user id: ");
        friendshipService.removeFriendship(id1, id2);
        System.out.println("Friendship removed.");
    }


    private void showUsers() {
        for (User user : userService.getAllUsers()) {
            System.out.println(user);
        }
    }

    private void showFriendships() {
        for (Friendship friendship : friendshipService.getFriendships()) {
            System.out.println(friendship);
        }
    }

    private void showFriends() {
        Long id = readId("User id: ");
        List<User> friends = friendshipService.getFriends(id);
        if (friends.isEmpty()) {
            System.out.println("This user has no friends.");
        }
        for (User friend : friends) {
            System.out.println(friend);
        }
    }

    private void showCommunityCount() {
        System.out.println("Number of communities: " + communityService.countCommunities());
    }

    private void showMostSociableCommunity() {
        List<User> community = communityService.getMostSociableCommunity();
        System.out.println("Most sociable community:");
        for (User user : community) {
            System.out.println(user);
        }
    }

    private Long readId(String message) {
        System.out.print(message);
        return Long.parseLong(scanner.nextLine().trim());
    }
}
