package validators;

import exceptions.ValidationException;
import model.Friendship;

/**
 * Validator pentru prietenii.
 * O prietenie este valida daca:
 * - cele doua id-uri sunt nenule si diferite
 * - data prieteniei este nenula
 */

public class FriendshipValidator implements Validator<Friendship> {


    /**
     * toate erorile sunt raportate o singura data, intr-o singura ValidationException
     *
     * @param friendship - prietenia de validat
     * @throws ValidationException daca prietenia este null sau invalida;
     *                             mesajul contine toate erorile gasite
     */

    @Override
    public void validate(Friendship friendship){

        if (friendship == null) {
            throw new ValidationException("Friendship cannot be null; ");
        }

        StringBuilder errors = new StringBuilder();

        if (friendship.getUserId1() == null || friendship.getUserId2() == null) {
            errors.append("user ids cannot be null; ");
        } else if (friendship.getUserId1().equals(friendship.getUserId2())) {
            errors.append("a user cannot be friend with himself; ");
        }
        if(friendship.getFriendsFrom() == null){
            errors.append("friends date cannot be null; ");
        }

        if (!errors.isEmpty()) {
            throw new ValidationException(errors.toString().trim());
        }

    }
}
