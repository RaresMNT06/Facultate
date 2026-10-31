package domain;

import java.util.function.Predicate;

/**
 * clasa utilitara cu criterii de cautare pentru utilizatori;
 * metodele intorc Predicate ("fabrici de criterii")
 */
public class CriteriaUser {

    private CriteriaUser() {
    }

    /**
     * @param prefix - inceputul prenumelui
     * @return criteriul "prenumele incepe cu prefix"
     */
    public static Predicate<User> firstNameStrartsWith(String prefix) {
        return u -> u.getFirstName().startsWith(prefix);
    }

    /**
     * @param name - numele cautat
     * @return criteriul "numele este name"
     */
    public static Predicate<User> hasLastName(String name) {
        return u -> u.getLastName().equals(name);
    }

    /**
     * @param n - numarul minim de prieteni
     * @return criteriul "are cel putin n prieteni"
     */
    public static Predicate<User> hasAtLeastFriends(int n) {
        return u -> u.getFriends().size() >= n;
    }

    /**
     * are forma lui Predicate.test, deci poate fi folosita ca CriteriaUser::withoutFriends
     *
     * @param u - utilizatorul verificat
     * @return true - daca u nu are prieteni, false altfel
     */
    public static boolean withoutFriends(User u) {
        return u.getFriends().isEmpty();
    }
}