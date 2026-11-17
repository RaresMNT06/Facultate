package validators;

import exceptions.ValidationException;
import model.User;

/**
 * Validator pentru utilizatori.
 * Un utilizator este valid daca:
 * - id-ul, daca exista, este pozitiv (un utilizator nou nu are inca id: il da stocarea)
 * - prenumele si numele sunt nevide si incep cu litera mare
 * - email-ul are forma nume@domeniu.extensie
 * - parola are cel putin 6 caractere
 * Regula "fara ';'" tine de formatul fisierului, deci se verifica in UserFileRepository.
 */
public class UserValidator implements Validator<User> {

    private static final String EMAIL_REGEX = "^[\\w.+-]+@[\\w-]+\\.[\\w.]+$";
    private static final int MIN_PASSWORD_LENGTH = 6;

    /**
     * toate erorile sunt raportate o singura data, intr-o singura ValidationException
     *
     * @param user - utilizatorul de validat
     * @throws ValidationException daca utilizatorul este null sau invalid;
     *                             mesajul contine toate erorile gasite
     */
    @Override
    public void validate(User user) {
        if (user == null) {
            throw new ValidationException("User cannot be null");
        }

        StringBuilder errors = new StringBuilder();

        if (user.getId() != null && user.getId() <= 0) {
            errors.append("invalid id; ");
        }
        if (!isValidName(user.getFirstName())) {
            errors.append("invalid first name; ");
        }
        if (!isValidName(user.getLastName())) {
            errors.append("invalid last name; ");
        }
        if (user.getEmail() == null || !user.getEmail().matches(EMAIL_REGEX)) {
            errors.append("invalid email; ");
        }
        if (user.getPassword() == null || user.getPassword().length() < MIN_PASSWORD_LENGTH) {
            errors.append("invalid password (at least " + MIN_PASSWORD_LENGTH + " characters); ");
        }

        if (!errors.isEmpty()) {
            throw new ValidationException(errors.toString().trim());
        }
    }

    /**
     * @param name - numele de verificat
     * @return true - daca numele este nevid si incepe cu litera mare, false altfel
     */
    private static boolean isValidName(String name) {
        return name != null && !name.isBlank()
                && Character.isUpperCase(name.charAt(0));
    }
}