package model;

import java.time.LocalDateTime;

/**
 * Prietenie intre doi utilizatori.
 * Id-ul este perechea ordonata (id mic, id mare), deci (1, 2) si (2, 1) sunt aceeasi prietenie.
 */

public class Friendship extends Entity<Tuple<Long, Long>> {

    private final LocalDateTime friendsFrom;

    /**
     * creeaza o prietenie; id-ul este normalizat (id-ul mai mic primul)
     *
     * @param userId1     - id-ul primului utilizator
     * @param userId2     - id-ul celui de-al doilea utilizator
     * @param friendsFrom - data si ora la care s-a creat prietenia
     */
    public Friendship(Long userId1, Long userId2, LocalDateTime friendsFrom) {
        if (userId1 < userId2) {
            setId(new Tuple<>(userId1, userId2));
        } else {
            setId(new Tuple<>(userId2, userId1));
        }
        this.friendsFrom = friendsFrom;
    }

    public Long getUserId1() {
        return getId().getLeft();
    }

    public Long getUserId2() {
        return getId().getRight();
    }

    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }

    /**
     * @return reprezentarea ca text a prieteniei
     */
    @Override
    public String toString() {
        return "Friendship: " + getUserId1() + " - " + getUserId2() + " (since " + friendsFrom + ")";
    }
}
