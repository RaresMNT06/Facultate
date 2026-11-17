package repository.db;

import exceptions.RepositoryException;

import java.sql.SQLException;

/**
 * Translates a SQLException into a RepositoryException with a clear message for the user.
 * The message depends on the SQLState of the exception (a standard 5-character code):
 * the class (first 2 characters) tells what kind of error happened.
 */
public final class DbErrors {

    private DbErrors() {
    }

    /**
     * wraps a SQLException into a RepositoryException with a specific message;
     * the original exception is kept as cause (exception chaining)
     *
     * @param action - what the repository was doing, e.g. "saving user"
     * @param e      - the exception thrown by JDBC
     * @return the RepositoryException to be thrown
     */
    public static RepositoryException wrap(String action, SQLException e) {
        String state = e.getSQLState() == null ? "" : e.getSQLState();
        String message;
        if (state.startsWith("08")) {                     // 08 = connection exception
            message = "cannot connect to the database (is the PostgreSQL server running?)";
        } else if (state.startsWith("28")) {              // 28 = invalid authorization
            message = "database login failed (check db.user and db.password in config.properties)";
        } else if (state.equals("3D000")) {               // baza de date nu exista
            message = "the database does not exist (check db.url in config.properties)";
        } else if (state.equals("23505")) {               // unique_violation
            message = "the value already exists (e.g. the email is already used)";
        } else if (state.equals("23503")) {               // foreign_key_violation
            message = "the referenced user does not exist";
        } else if (state.equals("23514")) {               // check_violation
            message = "a check constraint was violated (e.g. id1 must be smaller than id2)";
        } else if (state.startsWith("23")) {              // 23 = alte constrangeri
            message = "a database constraint was violated";
        } else {
            message = e.getMessage();
        }
        return new RepositoryException("Database error while " + action + ": " + message, e);
    }
}