package seminar7.repository.db;

import seminar7.domain.Movie;
import seminar7.domain.validators.Validator;
import seminar7.repository.Repository;
import seminar7.repository.RepositoryException;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MovieDBRepository implements Repository<Long, Movie> {
    private final Validator<Movie> validator;
    private final String url;
    private final String username;
    private final String password;

    public MovieDBRepository(Validator<Movie> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Movie> findOne(Long id) {
        if (id == null)
            throw new IllegalArgumentException("id must not be null");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement("select * from filme where id=?")) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Movie movie = new Movie(resultSet.getString("titlu"),
                            resultSet.getString("regizor"),
                            resultSet.getInt("an"),
                            resultSet.getInt("durata"));
                    movie.setId(id);
                    return Optional.of(movie);
                }
            }

        } catch (SQLException e) {
            throw new RepositoryException("Error while reading data:" + e.getMessage(), e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Movie> findAll() {
        List<Movie> movies = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement("select * from filme order by id");
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                Movie m = new Movie(resultSet.getString("titlu"),
                        resultSet.getString("regizor"),
                        resultSet.getInt("an"),
                        resultSet.getInt("durata"));
                m.setId(resultSet.getLong("id"));
                movies.add(m);
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error while reading the movies:" + e.getMessage(), e);
        }
        return movies;
    }

    @Override
    public Optional<Movie> save(Movie entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must not be null");
        validator.validate(entity);
        String sql = "INSERT into filme (titlu, regizor,an, durata) values (?,?,?,?)";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            preparedStatement.setString(1, entity.getTitle());
            preparedStatement.setString(2, entity.getDirector());
            preparedStatement.setInt(3, entity.getYear());
            preparedStatement.setInt(4, entity.getDuration());
            preparedStatement.executeUpdate();
            try (ResultSet resultSet = preparedStatement.getGeneratedKeys()) {
                resultSet.next();
                entity.setId(resultSet.getLong("id"));
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error while saving data:" + e.getMessage(), e);
        }
        return Optional.empty();
    }

    @Override
    public Optional<Movie> delete(Long id) {
        Optional<Movie> found = findOne(id);
        if (found.isEmpty())
            return found;

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement("DELETE FROM filme WHERE id = ?")) {
            ps.setLong(1, id);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Error while deleting: " + e.getMessage(), e);
        }
        return found;
    }

    @Override
    public Optional<Movie> update(Movie entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must not be null");
        validator.validate(entity);
        String sql = "UPDATE filme set titlu=?,regizor=?,an=?,durata=? where id=?";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, entity.getTitle());
            preparedStatement.setString(2, entity.getDirector());
            preparedStatement.setInt(3, entity.getYear());
            preparedStatement.setInt(4, entity.getDuration());
            preparedStatement.setLong(5, entity.getId());
            int nrRows = preparedStatement.executeUpdate();
            return nrRows == 0 ? Optional.of(entity) : Optional.empty();

        } catch (SQLException e) {
            throw new RepositoryException("Error while updating data:" + e.getMessage(), e);
        }
    }

    public List<Movie> findByDirector(String director) {
        List<Movie> movies = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT * FROM filme WHERE regizor = ? ORDER BY an")) {

            statement.setString(1, director);
            try (ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    Movie movie = new Movie(resultSet.getString("titlu"), resultSet.getString("regizor"),
                            resultSet.getInt("an"), resultSet.getInt("durata"));
                    movie.setId(resultSet.getLong("id"));
                    movies.add(movie);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error: " + e.getMessage(), e);
        }
        return movies;
    }
}
