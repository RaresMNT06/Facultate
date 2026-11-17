package validators;

import exceptions.ValidationException;
import model.User;

/**
 * Validator for users. A user is valid if:
 * - the id, if present, is positive (a new user has no id yet: the storage generates it)
 * - the first and last name are not blank and start with an uppercase letter
 * - the email has the form name@domain.extension
 * - the password has at least 6 characters
 * The rule "no ';'" belongs to the file format, so it is checked in UserFileRepository.
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