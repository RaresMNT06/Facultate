package model;

import java.util.function.Predicate;

/**
 * Clasa utilitara cu criterii de cautare pentru utilizatori.
 * Fiecare metoda intoarce un Predicate, folosit cu Repository.findAll(Predicate)
 * si combinabil cu and, or, negate sau Predicate.not.
 */
public final class UserCriteria {

    private UserCriteria() {
    }

    /**
     * @param prefix - inceputul cautat al prenumelui
     * @return criteriul "prenumele incepe cu prefix"
     */
    public static Predicate<User> firstNameStartsWith(String prefix) {
        return u -> u.getFirstName().startsWith(prefix);
    }

    /**
     * @param lastName - numele cautat
     * @return criteriul "numele este lastName"
     */
    public static Predicate<User> hasLastName(String lastName) {
        return u -> u.getLastName().equals(lastName);
    }

    /**
     * @param domain - domeniul cautat (ex: gmail.com)
     * @return criteriul "email-ul este pe domeniul dat"
     */
    public static Predicate<User> hasEmailDomain(String domain) {
        return u -> u.getEmail().endsWith("@" + domain);
    }

    /**
     * criteriu folosit ca referinta la metoda statica (UserCriteria::hasGmail)
     *
     * @param u - utilizatorul verificat
     * @return true - daca utilizatorul are email de Gmail, false altfel
     */
    public static boolean hasGmail(User u) {
        return u.getEmail().endsWith("@gmail.com");
    }
}