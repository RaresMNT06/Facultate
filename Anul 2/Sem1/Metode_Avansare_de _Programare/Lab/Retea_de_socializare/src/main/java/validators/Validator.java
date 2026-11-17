package validators;

/**
 * Strategie de validare pentru entitati.
 * Este interfata functionala (o singura metoda abstracta), deci un validator
 * se poate scrie si ca expresie lambda sau referinta la metoda.
 *
 * @param <T> - tipul entitatilor validate
 */
@FunctionalInterface
public interface Validator<T> {

    /**
     * verifica daca entitatea este valida
     *
     * @param entity - entitatea de verificat
     * @throws exceptions.ValidationException daca entitatea nu este valida
     */
    void validate(T entity);

    /**
     * compune doua validatoare: aplica intai validatorul curent, apoi pe other
     *
     * @param other - validatorul aplicat dupa cel curent; nu poate fi null
     * @return un validator nou care aplica ambele reguli, in ordine
     * @throws IllegalArgumentException daca other este null
     */
    default Validator<T> andThen(Validator<T> other) {
        if(other == null) {
            throw new IllegalArgumentException("other must not be null");
        }
        return entity -> {
            this.validate(entity);
            other.validate(entity);
        };
    }
}
