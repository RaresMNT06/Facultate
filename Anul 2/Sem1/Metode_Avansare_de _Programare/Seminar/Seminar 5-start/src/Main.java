import domain.CriteriaUser;
import domain.Entity;
import domain.User;
import domain.validators.UserValidator;
import domain.validators.UserValidatorStrict;
import domain.validators.ValidationException;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.factory.RepositoryFactory;
import repository.file.UserFileRepository;
import util.MyCollections;

import javax.sound.midi.Soundbank;
import javax.xml.transform.Source;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;
import java.util.Properties;
import java.util.function.Consumer;
import java.util.function.Predicate;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
//        User u = new User("John", "Doe");
//        System.out.println(u instanceof Entity);
//        requirement1();
//        requirement2();
//        requirement3();
//        requirement4();
//        requirement7();
//        requirement8();
    }

    public static void requirement7(){
        Validator<User> anonValidator = new Validator<User>() {
            @Override
            public void validate(User user) {
                if (user.getFirstName() == null || user.getFirstName().isEmpty()) {
                    throw new ValidationException("First name should not be empty");
                }
            }
        };

        Validator<User> lambdaValidator = (user) -> {
            if (user.getFirstName() == null || user.getFirstName().isEmpty()) {
                throw new ValidationException("First name should not be empty");
            }
        };
        Validator<User> userValidator = Main::checkFirstName;
        validate(anonValidator, getUserFromText("7;;Pop"));
        validate(lambdaValidator, getUserFromText("7;;Pop"));
        validate(userValidator, getUserFromText("7;;Pop"));

        int maxLen = 10;
        Validator<User> maxLengthValidator = u ->{
            if (u.getFirstName().length() > maxLen || u.getLastName().length() > maxLen) {
                throw new ValidationException("First name should not be empty");
            }
        };

        Repository<Long, User> repo = new InMemoryRepository<>(lambdaValidator.andThen(maxLengthValidator));
        save(repo, getUserFromText("1;Ana;Pop"));
        save(repo, getUserFromText("2;Maximilian-Alexandru;Pop"));
        save(repo, getUserFromText("3;ana;Pop"));
    }

    // ---------------- Requirement 8. Searches with criteria ----------------

    /**
     * cautari pe reteaua demo cu criterii transmise ca Predicate;
     * afisare cu Consumer compusi si eliminare cu removeIf
     */
    public static void requirement8() {
        System.out.println("\n=== Requirement8 ===");
        Repository<Long, User> repo = demoNetwork();

        // a) numele Pop
        System.out.println("-- last name Pop");
        List<User> l1 = repo.findAll(CriteriaUser.hasLastName("Pop"));
        l1.forEach(System.out::println);

        // b) prenumele incepe cu I si numele Pop
        System.out.println("-- first name starts with I and last name Pop");
        List<User> l2 = repo.findAll(CriteriaUser.firstNameStrartsWith("I")
                .and(CriteriaUser.hasLastName("Pop")));
        l2.forEach(System.out::println);

        // c) cel putin 2 prieteni sau numele Matei
        System.out.println("-- at least 2 friends or last name Matei");
        List<User> l3 = repo.findAll(CriteriaUser.hasAtLeastFriends(2)
                .or(CriteriaUser.hasLastName("Matei")));
        l3.forEach(System.out::println);

        // d) nu au numele Pop
        System.out.println("-- last name is not Pop");
        List<User> l4 = repo.findAll(CriteriaUser.hasLastName("Pop").negate());
        l4.forEach(System.out::println);

        // e) au prieteni: fara metoda noua, negam withoutFriends
        System.out.println("-- have friends");
        List<User> l5 = repo.findAll(Predicate.not(CriteriaUser::withoutFriends));
        l5.forEach(System.out::println);

        // fiecare utilizator cu numarul de prieteni: doi Consumer compusi cu andThen
        System.out.println("-- users with number of friends");
        Consumer<User> printUser = u -> System.out.print(u);
        Consumer<User> printFriends = u -> System.out.println(" -> " + u.getFriends().size() + " friends");
        repo.findAll().forEach(printUser.andThen(printFriends));

        // copiem in lista si eliminam cu removeIf pe cei fara prieteni
        System.out.println("-- after removeIf (without friends)");
        List<User> users = MyCollections.toList(repo.findAll());
        users.removeIf(CriteriaUser::withoutFriends);
        users.forEach(System.out::println);
    }



    public static void validate(Validator<User> userValidator, User user){
        try {
            userValidator.validate(user);
            System.out.println("All good");
        }catch (ValidationException e){
            System.out.println(e.getMessage());
        }
    }

    public static void checkFirstName(User user){
        if (user.getFirstName() == null || user.getFirstName().isEmpty()) {
            throw new ValidationException("First name should not be empty");
        }
    }


    /**
     * Builds a small social network in memory: 6 users and 5 friendships
     * (Ana 3 friends, Mihai 2, Ioana 2, Ion 2, Irina 1, Dan 0)
     *
     * @return an in-memory repository with the demo users
     */
    static Repository<Long, User> demoNetwork() {
        Repository<Long, User> repo = new InMemoryRepository<>(new UserValidator());
        String[] lines = {"1;Ana;Pop", "2;Mihai;Ionescu", "3;Ioana;Marin", "4;Ion;Pop", "5;Irina;Pop", "6;Dan;Matei"};
        for (String line : lines)
            repo.save(getUserFromText(line));

        long[][] friendships = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {4, 5}};
        for (long[] p : friendships) {
            User a = repo.findOne(p[0]);
            User b = repo.findOne(p[1]);
            a.getFriends().add(b);
            b.getFriends().add(a);
        }
        return repo;
    }

    // ---------------- Requirement 1- Valid User ----------------

    /**
     * builds users from text lines (id;firstName;lastName), validates them
     * and prints the result; invalid data does not stop the program
     */
    static void requirement1() {
        System.out.println("=== Requirement 1 ===");
        Validator<User> validator = new UserValidator();

        // Data comes as text, like from a text file: id;firstName;lastName
        String[] lines = {
                "1;Ana;Pop",
                "-2;;ionescu",     // 3 validation errors
                "12b;Mihai;Pop",   // id not number -> NumberFormatException
                "3;Ion;"           // missing last name at the end -> see split(";", -1)
        };

        for (String line : lines) {
            try {
                User u = getUserFromText(line);
                validator.validate(u);
                System.out.println("VALID:   " + u);
            } catch (ValidationException e) {
                System.out.println("INVALID: [" + line + "] -> " + e.getMessage());
                if (e.getCause() != null)
                    System.out.println("         Cause: " + e.getCause());
            }
        }
        System.out.println("The app continues after validation.");
    }

    /**
     * creates a user from a text line; the NumberFormatException thrown by
     * Long.parseLong is translated into a ValidationException, keeping the
     * original exception as cause (exception chaining)
     *
     * @param line - text line with the format id;firstName;lastName
     * @return the user created from the given line (not validated yet)
     * @throws ValidationException if the id is not numeric
     */
    static User getUserFromText(String line) {
        // Use -1 as the limit to preserve trailing empty fields, ensuring that
        // empty values at the end of the line are not discarded during splitting.
        String[] fields = line.split(";", -1);
        try {
            User u = new User(fields[1], fields[2]);
            u.setId(Long.parseLong(fields[0]));
            return u;
        } catch (NumberFormatException e) {
            throw new ValidationException("The id '" + fields[0] + "' is not a number", e);
        }
    }

    // ---------------- Requirement 2. In memory repository ----------------

    /**
     * saves the same users in two repositories that use different validation
     * strategies; the exceptions thrown by the validator propagate through
     * the repository and are handled here, in the caller
     */
    static void requirement2() {
        System.out.println("\n=== Requirement 2 ===");
        // Strategy: same context (InMemoryRepository), different validation strategies
        Repository<Long, User> repo = new InMemoryRepository<>(new UserValidator());
        Repository<Long, User> repoStrict = new InMemoryRepository<>(new UserValidatorStrict());

        User ana = getUserFromText("1;Ana;Pop");
        User io = getUserFromText("2;Io;Pop");          // valid normal, valid strict
        User x = getUserFromText("3;X;Pop");            // valid normal, invalid strict
        User anaDublura = getUserFromText("1;Ana;Pop"); // same id

        System.out.println("-- repo (UserValidator)");
        save(repo, ana);
        save(repo, io);
        save(repo, x);
        save(repo, anaDublura);
        save(repo, null);

        System.out.println("-- repoStrict (UserValidatorStrict)");
        save(repoStrict, ana);
        save(repoStrict, x);

        System.out.println("-- findOne / findAll");
        try {
            System.out.println("findOne(1): " + repo.findOne(1L));
            System.out.println("findOne(99): " + repo.findOne(99L));
            System.out.println("findOne(null): " + repo.findOne(null));
            System.out.println("could not arrive here");
        } catch (IllegalArgumentException e) {
            System.out.println("Error findOne: " + e.getMessage());
        }
        System.out.println("findAll: " + repo.findAll());
    }

    /**
     * saves an entity and reports the result; ValidationException (thrown by
     * the validator) and IllegalArgumentException (thrown by the repository)
     * propagate from the repository and are caught here
     *
     * @param repo   - the repository where the user is saved
     * @param entity - the user to be saved (may be null)
     */
    static void save(Repository<Long, User> repo, User entity) {
        try {
            User result = repo.save(entity);
            if (result == null)
                System.out.println("Saved:  " + entity);
            else
                System.out.println("There is:  " + result + " (duplicated id)");
        } catch (ValidationException | IllegalArgumentException e) {
            System.out.println("Error:  " + e.getClass().getSimpleName() + " -> " + e.getMessage());
        } finally {
            System.out.println("  (finally: save operation is done)");
        }
    }

    // ---------------- Requirement 3. File Repository----------------

    /**
     * loads the users from a text file, saves new users (the valid ones reach
     * the file) and reopens the file with a new repository to show that the
     * data persisted
     */
    static void requirement3() {
        System.out.println("\n=== Requirement3 ===");
        String file = "data/users.txt";
        Repository<Long, User> repo = new UserFileRepository(new UserValidator(), file);
        System.out.println("Loaded from file: " + repo.findAll());

        save(repo, getUserFromText("4;Ion;Pop"));
        save(repo, getUserFromText("5;;popescu"));   // invalid

        //restart the app: new repo, over same file
        Repository<Long, User> repoDupaRepornire = new UserFileRepository(new UserValidator(), file);
        System.out.println("After restart:      " + repoDupaRepornire.findAll());

        // file not found -> empty repository, program continues
        Repository<Long, User> repoGol = new UserFileRepository(new UserValidator(), "data/inexistent.txt");
        System.out.println("File not found:   " + repoGol.findAll());
    }

    static void requirement4(){
        System.out.println("\n=== Requirement4 ===");
        Properties props = loadProperties("config.properties");
        RepositoryFactory factory = new RepositoryFactory(props);

        Repository<Long, User> repo = factory.createUserRepository(new UserValidator());
        System.out.println("Created repo:"+repo.getClass().getSimpleName());
        System.out.println("Find all:"+repo.findAll());
    }

    static Properties loadProperties(String resource){
        Properties prop = new Properties();
        try(InputStream in = Main.class.getResourceAsStream(resource)){//need to mark the folder as resource root
            //try(InputStream in = new FileInputStream(resource)){
            if(in == null)
                throw new RuntimeException("There is no resource: " + resource);
            prop.load(in);
        } catch (IOException e) {
            throw new RuntimeException("Error while reading the resource "+e);
        }
        return prop;
    }
}