package exceptions;

/**
 * Exceptie unchecked aruncata cand configurarea aplicatiei (config.properties)
 * lipseste, nu poate fi citita sau contine o valoare lipsa ori necunoscuta.
 */
public class ConfigurationException extends RuntimeException {

    /**
     * @param message - descrierea problemei de configurare
     */
    public ConfigurationException(String message) {
        super(message);
    }

    /**
     * @param message - descrierea problemei de configurare
     * @param cause   - exceptia originala (exception chaining)
     */
    public ConfigurationException(String message, Throwable cause) {
        super(message, cause);
    }
}
