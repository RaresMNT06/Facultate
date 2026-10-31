package repository.db;

import domain.User;
import domain.validators.Validator;
import repository.Repository;

/**
 * Database repository for users (skeleton - methods are not implemented yet)
 */
public class UserDbRepository implements Repository<Long, User> {

    private final Validator<User> validator;
    private final String url;
    private final String username;
    private final String password;

    /**
     * @param validator - the validation strategy for the users
     * @param url       - the url of the database
     * @param username  - the database user
     * @param password  - the database password
     */
    public UserDbRepository(Validator<User> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public User findOne(Long id) {
        throw new UnsupportedOperationException("findOne nu este implementat inca");
    }

    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("findAll nu este implementat inca");
    }

    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("save nu este implementat inca");
    }

    @Override
    public User delete(Long id) {
        throw new UnsupportedOperationException("delete nu este implementat inca");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("update nu este implementat inca");
    }
}