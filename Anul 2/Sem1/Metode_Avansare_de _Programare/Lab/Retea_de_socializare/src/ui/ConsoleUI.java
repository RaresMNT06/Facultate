package ui;

import exceptions.DuplicateEntityException;
import exceptions.EntityNotFoundException;
import exceptions.RepositoryException;
import exceptions.ValidationException;
import model.User;
import service.CommunityService;
import service.FriendshipService;
import service.UserService;

import java.util.List;
import java.util.Scanner;
import model.UserCriteria;
import java.util.function.Predicate;

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
                    case "10": searchUsers(); break;
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
        System.out.println("10. Search users");
        System.out.println("0. Exit");
        System.out.print("Option: ");
    }

    /**
     * afiseaza elementele unei liste, cate unul pe linie, sau un mesaj daca lista e goala
     *
     * @param items        - elementele de afisat
     * @param emptyMessage - mesajul afisat cand lista e goala
     */
    private void printAll(List<?> items, String emptyMessage) {
        if (items.isEmpty()) {
            System.out.println(emptyMessage);
        } else {
            items.forEach(System.out::println);
        }
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
        printAll(userService.getAllUsers(), "No users.");
    }

    private void showFriendships() {
        printAll(friendshipService.getFriendships(), "No friendships.");
    }

    private void showFriends() {
        Long id = readId("User id: ");
        printAll(friendshipService.getFriends(id), "This user has no friends.");
    }

    private void showCommunityCount() {
        System.out.println("Number of communities: " + communityService.countCommunities());
    }

    private void showMostSociableCommunity() {
        System.out.println("Most sociable community:");
        printAll(communityService.getMostSociableCommunity(), "No users.");
    }

    private Long readId(String message) {
        System.out.print(message);
        return Long.parseLong(scanner.nextLine().trim());
    }


    /**
     * cauta utilizatori dupa criterii combinate (UserCriteria + and / Predicate.not);
     * un criteriu lasat gol nu se aplica
     */
    private void searchUsers() {
        System.out.print("Last name (Enter = any): ");
        String lastName = scanner.nextLine().trim();
        System.out.print("First name starts with (Enter = any): ");
        String prefix = scanner.nextLine().trim();
        System.out.print("Email: 1 = only Gmail, 2 = without Gmail, Enter = any: ");
        String gmail = scanner.nextLine().trim();

        Predicate<User> criteria = u -> true;
        if (!lastName.isEmpty()) {
            criteria = criteria.and(UserCriteria.hasLastName(lastName));
        }
        if (!prefix.isEmpty()) {
            criteria = criteria.and(UserCriteria.firstNameStartsWith(prefix));
        }
        switch (gmail) {
            case "1": criteria = criteria.and(UserCriteria::hasGmail); break;
            case "2": criteria = criteria.and(Predicate.not(UserCriteria::hasGmail)); break;
            default: break;
        }

        printAll(userService.searchUsers(criteria), "No users found.");
    }
}
