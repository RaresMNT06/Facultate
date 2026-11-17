package exceptions;

/**
 * Exceptie unchecked aruncata cand o entitate cautata nu exista.
 */
public class EntityNotFoundException extends RuntimeException {

    /**
     * @param message - descrierea entitatii negasite
     */
    public EntityNotFoundException(String message) {
        super(message);
    }
}