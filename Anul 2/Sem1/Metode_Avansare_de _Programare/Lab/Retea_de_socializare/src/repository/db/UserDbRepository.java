package repository.db;

import model.User;
import repository.Repository;
import validators.Validator;

/**
 * Repository de utilizatori pastrati in baza de date.
 * Schelet: metodele vor fi implementate cu JDBC la laboratorul 4;
 * pana atunci arunca UnsupportedOperationException.
 */
public class UserDbRepository implements Repository<Long, User> {

    private final Validator<User> validator;
    private final String url;
    private final String username;
    private final String password;

    /**
     * @param validator - strategia de validare pentru utilizatori
     * @param url       - adresa bazei de date (db.url)
     * @param username  - utilizatorul bazei de date (db.user)
     * @param password  - parola bazei de date (db.password)
     */
    public UserDbRepository(Validator<User> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public User findOne(Long id) {
        throw new UnsupportedOperationException("UserDbRepository.findOne is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("UserDbRepository.findAll is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("UserDbRepository.save is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public User delete(Long id) {
        throw new UnsupportedOperationException("UserDbRepository.delete is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("UserDbRepository.update is not implemented yet (laboratory 4)");
    }
}