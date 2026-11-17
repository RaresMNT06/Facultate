package repository.db;

import exceptions.RepositoryException;
import model.Friendship;
import model.Tuple;
import repository.Repository;
import validators.Validator;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

/**
 * Database repository for friendships, implemented with JDBC.
 * Every operation is a query on the table friendships(id1, id2, friends_from),
 * where (id1, id2) is the primary key and id1 &lt; id2; nothing is kept in memory.
 */
public class FriendshipDbRepository implements Repository<Tuple<Long, Long>, Friendship> {

    private final Validator<Friendship> validator;
    private final String url;
    private final String username;
    private final String password;

    /**
     * @param validator - the validation strategy for friendships
     * @param url       - the JDBC url of the database (db.url)
     * @param username  - the database user (db.user)
     * @param password  - the password of the database user (db.password)
     */
    public FriendshipDbRepository(Validator<Friendship> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * builds a friendship from the current row of a result set
     *
     * @param resultSet - the result set, positioned on a row of the table friendships
     * @return the friendship from the current row
     * @throws SQLException if a column cannot be read
     */
    private Friendship extractFriendship(ResultSet resultSet) throws SQLException {
        return new Friendship(resultSet.getLong("id1"),
                resultSet.getLong("id2"),
                resultSet.getTimestamp("friends_from").toLocalDateTime());   // TIMESTAMP -> LocalDateTime
    }

    /**
     * checks that an id and both its components are not null
     *
     * @param id - the id of a friendship
     * @throws IllegalArgumentException if id or one of its components is null
     */
    private void checkId(Tuple<Long, Long> id) {
        if (id == null || id.getLeft() == null || id.getRight() == null) {
            throw new IllegalArgumentException("id must not be null");
        }
    }

    /**
     * @param id - the id (id1, id2) of the friendship, with id1 &lt; id2; must not be null
     * @return the friendship with the given id or null if there is no such friendship
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException      if a database access error occurs
     */
    @Override
    public Friendship findOne(Tuple<Long, Long> id) {
        checkId(id);
        String sql = "SELECT * FROM friendships WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());
            try (ResultSet resultSet = statement.executeQuery()) {
                return resultSet.next() ? extractFriendship(resultSet) : null;
            }
        } catch (SQLException e) {
            throw DbErrors.wrap("searching friendship " + id, e);
        }
    }

    /**
     * @return all friendships, ordered by id1 and id2
     * @throws RepositoryException if a database access error occurs
     */
    @Override
    public Iterable<Friendship> findAll() {
        List<Friendship> friendships = new ArrayList<>();
        String sql = "SELECT * FROM friendships ORDER BY id1, id2";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql);
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                friendships.add(extractFriendship(resultSet));
            }
        } catch (SQLException e) {
            throw DbErrors.wrap("reading friendships", e);
        }
        return friendships;
    }

    /**
     * saves a new friendship
     *
     * @param entity - the friendship to save; must not be null
     * @return null - if the friendship was saved, otherwise the entity (the friendship already exists)
     * @throws IllegalArgumentException       if entity is null
     * @throws exceptions.ValidationException if the friendship is not valid
     * @throws RepositoryException            if a database access error occurs
     *                                        or a constraint is violated (e.g. a user does not exist)
     */
    @Override
    public Friendship save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity must not be null");
        }
        validator.validate(entity);                         // validare inainte de INSERT
        if (findOne(entity.getId()) != null) {              // prietenia exista deja
            return entity;
        }

        String sql = "INSERT INTO friendships (id1, id2, friends_from) VALUES (?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setLong(1, entity.getUserId1());      // id-ul mic (Friendship il normalizeaza)
            statement.setLong(2, entity.getUserId2());      // id-ul mare -> respecta CHECK (id1 < id2)
            statement.setTimestamp(3, Timestamp.valueOf(entity.getFriendsFrom()));   // LocalDateTime -> TIMESTAMP
            statement.executeUpdate();
        } catch (SQLException e) {
            throw DbErrors.wrap("saving friendship", e);
        }
        return null;
    }

    /**
     * deletes the friendship with the given id
     *
     * @param id - the id (id1, id2) of the friendship, with id1 &lt; id2; must not be null
     * @return the deleted friendship or null if there is no friendship with the given id
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException      if a database access error occurs
     */
    @Override
    public Friendship delete(Tuple<Long, Long> id) {
        Friendship found = findOne(id);                     // verifica si id == null
        if (found == null) {
            return null;
        }
        String sql = "DELETE FROM friendships WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw DbErrors.wrap("deleting friendship " + id, e);
        }
        return found;
    }

    /**
     * updates the date of an existing friendship
     *
     * @param entity - the friendship with the new data; must not be null
     * @return null - if the friendship was updated, otherwise the entity (there is no friendship with its id)
     * @throws IllegalArgumentException       if entity is null
     * @throws exceptions.ValidationException if the friendship is not valid
     * @throws RepositoryException            if a database access error occurs
     */
    @Override
    public Friendship update(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity must not be null");
        }
        validator.validate(entity);                         // validare inainte de UPDATE

        String sql = "UPDATE friendships SET friends_from = ? WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setTimestamp(1, Timestamp.valueOf(entity.getFriendsFrom()));
            statement.setLong(2, entity.getUserId1());
            statement.setLong(3, entity.getUserId2());
            int rows = statement.executeUpdate();
            return rows == 0 ? entity : null;                // 0 randuri = prietenia nu exista
        } catch (SQLException e) {
            throw DbErrors.wrap("updating friendship " + entity.getId(), e);
        }
    }
}