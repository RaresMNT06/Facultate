package exceptions;

/**
 * Exceptie unchecked aruncata cand se incearca adaugarea unei entitati care exista deja.
 */
public class DuplicateEntityException extends RuntimeException {

    /**
     * @param message - descrierea entitatii duplicate
     */
    public DuplicateEntityException(String message) {
        super(message);
    }
}