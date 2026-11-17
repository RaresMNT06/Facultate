package exceptions;

/**
 * Exceptie unchecked (extinde RuntimeException) aruncata cand o entitate nu este valida.
 * Compilatorul nu obliga declararea ei in clauza throws; ea urca pe stiva de apeluri
 * (validator -> repository -> service -> UI) si este prinsa in UI, unde se afiseaza mesajul.
 */
public class ValidationException extends RuntimeException {

    /**
     * @param message - descrierea erorilor de validare
     */
    public ValidationException(String message) {
        super(message);
    }

    /**
     * @param message - descrierea erorilor de validare
     * @param cause   - exceptia originala care a produs eroarea (exception chaining)
     */
    public ValidationException(String message, Throwable cause) {
        super(message, cause);
    }
}