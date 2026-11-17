package validators;

import exceptions.ValidationException;
import model.User;

/**
 * Validator pentru utilizatori.
 * Un utilizator este valid daca:
 * - id-ul este nenul si pozitiv
 * - prenumele si numele sunt nevide si incep cu litera mare
 * - email-ul are forma nume@domeniu.extensie
 * - parola are cel putin 6 caractere
 * - niciun camp nu contine ';' (separatorul din fisier)
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

        if(user == null) {
            throw new ValidationException("User cannot be null");
        }

        StringBuilder errors = new StringBuilder();

        if(user.getId() == null || user.getId() <= 0) {
            errors.append("invalid id; ");
        }
        if(!isValidName(user.getFirstName())) {
            errors.append("invalid first name; ");
        }
        if(!isValidName(user.getLastName())) {
            errors.append("invalid last name; ");
        }
        if(user.getEmail() == null || !user.getEmail().matches(EMAIL_REGEX)) {
            errors.append("invalid email; ");
        }
        if(user.getPassword() == null || user.getPassword().length() < MIN_PASSWORD_LENGTH
                || user.getPassword().contains(";")) {
            errors.append("invalid password (at least " + MIN_PASSWORD_LENGTH + " characters, no ';'); ");
        }

        if(!errors.isEmpty()) {
            throw new ValidationException(errors.toString().trim());
        }


    }


    /**
     * @param name - numele de verificat
     * @return true - daca numele este nevid, incepe cu litera mare si nu contine ';',
     * false altfel
     */
    private static boolean isValidName(String name) {
        return name != null && !name.isBlank()
                && Character.isUpperCase(name.charAt(0))
                && !name.contains(";");
    }


}
