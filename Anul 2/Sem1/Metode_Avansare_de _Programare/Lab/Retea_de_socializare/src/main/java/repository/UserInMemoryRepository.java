package repository;

import model.User;
import validators.Validator;

/**
 * In-memory repository for users; it generates the id of a new user
 * (the largest existing id + 1), so the service no longer generates ids.
 */
public class UserInMemoryRepository extends InMemoryRepository<Long, User> {

    /**
     * @param validator - the validation strategy for users
     */
    public UserInMemoryRepository(Validator<User> validator) {
        super(validator);
    }

    /**
     * @return the next free id: the largest existing id + 1 (or 1 if there are no users)
     */
    @Override
    protected Long generateId() {
        return stream()
                .mapToLong(User::getId)
                .max()
                .orElse(0) + 1;
    }
}