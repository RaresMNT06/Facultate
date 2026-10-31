package repository.db;

import domain.User;
import domain.validators.Validator;
import repository.Repository;

/**
 * Database repository for users;
 * every operation will be a query on the table users(id, first_name, last_name)
 * keeps nothing in memory.
 */
public class UserDBRepository implements Repository<Long, User> {

    private final Validator<User> validator;
    private final String url;
    private final String user;
    private final String password;

    public UserDBRepository(Validator<User> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public User findOne(Long aLong) {
        throw new UnsupportedOperationException("Find one not implemented yet");
    }

    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("Find all not implemented yet");
    }

    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("Save not implemented yet");
    }

    @Override
    public User delete(Long aLong) {
        throw new UnsupportedOperationException("Delete not implemented yet");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("Update not implemented yet");
    }
}
