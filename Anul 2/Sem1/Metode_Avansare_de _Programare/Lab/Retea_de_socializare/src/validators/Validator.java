package validators;

import exceptions.ValidationException;

/**
 * Strategie de validare pentru o entitate.
 *
 * @param <T> tipul entitatii validate
 */


public interface Validator<T> {

    /**
     * Verifica daca entitatea este valida.
     *
     * @param entity entitatea de verificat
     * @throws exceptions.ValidationException daca entitatea nu este valida
     */
    void validate(T entity);

}
