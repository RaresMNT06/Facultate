package model;

import java.time.LocalDateTime;
import java.util.function.Predicate;

/**
 * Clasa utilitara cu criterii de cautare pentru prietenii.
 * Fiecare metoda intoarce un Predicate, folosit cu Repository.findAll(Predicate)
 * sau in stream-uri (filter).
 */
public final class FriendshipCriteria {

    private FriendshipCriteria() {
    }

    /**
     * @param userId - id-ul utilizatorului cautat
     * @return criteriul "prietenia il contine pe utilizatorul cu id-ul dat"
     */
    public static Predicate<Friendship> involvesUser(Long userId) {
        return f -> f.getUserId1().equals(userId) || f.getUserId2().equals(userId);
    }

    /**
     * @param date - data de referinta
     * @return criteriul "prietenia a fost creata dupa data data"
     */
    public static Predicate<Friendship> createdAfter(LocalDateTime date) {
        return f -> f.getFriendsFrom().isAfter(date);
    }
}