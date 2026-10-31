package repository.db;

import model.Friendship;
import model.Tuple;
import repository.Repository;
import validators.Validator;

/**
 * Repository de prietenii pastrate in baza de date.
 * Schelet: metodele vor fi implementate cu JDBC la laboratorul 4;
 * pana atunci arunca UnsupportedOperationException.
 */
public class FriendshipDbRepository implements Repository<Tuple<Long, Long>, Friendship> {

    private final Validator<Friendship> validator;
    private final String url;
    private final String username;
    private final String password;

    /**
     * @param validator - strategia de validare pentru prietenii
     * @param url       - adresa bazei de date (db.url)
     * @param username  - utilizatorul bazei de date (db.user)
     * @param password  - parola bazei de date (db.password)
     */
    public FriendshipDbRepository(Validator<Friendship> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public Friendship findOne(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("FriendshipDbRepository.findOne is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public Iterable<Friendship> findAll() {
        throw new UnsupportedOperationException("FriendshipDbRepository.findAll is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public Friendship save(Friendship entity) {
        throw new UnsupportedOperationException("FriendshipDbRepository.save is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public Friendship delete(Tuple<Long, Long> id) {
        throw new UnsupportedOperationException("FriendshipDbRepository.delete is not implemented yet (laboratory 4)");
    }

    /**
     * @throws UnsupportedOperationException metoda va fi implementata la laboratorul 4
     */
    @Override
    public Friendship update(Friendship entity) {
        throw new UnsupportedOperationException("FriendshipDbRepository.update is not implemented yet (laboratory 4)");
    }
}