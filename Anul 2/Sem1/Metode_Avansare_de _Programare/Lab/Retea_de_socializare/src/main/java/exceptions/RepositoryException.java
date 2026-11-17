package exceptions;

/**
 * Exceptie unchecked pentru erorile de persistenta (citire/scriere fisier, linii corupte).
 * Impacheteaza exceptia originala (IOException, NumberFormatException, DateTimeParseException)
 * prin constructorul (message, cause).
 */
public class RepositoryException extends RuntimeException {

    /**
     * @param message - descrierea erorii
     */
    public RepositoryException(String message) {
        super(message);
    }

    /**
     * @param message - descrierea erorii
     * @param cause   - exceptia originala (exception chaining)
     */
    public RepositoryException(String message, Throwable cause) {
        super(message, cause);
    }
}