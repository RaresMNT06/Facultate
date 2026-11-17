package repository.file;

import model.Friendship;
import model.Tuple;
import validators.Validator;

import java.time.LocalDateTime;

/**
 * Repository in fisier text pentru prietenii; cate o prietenie pe linie,
 * cu formatul idUtilizator1;idUtilizator2;dataPrieteniei (data in format ISO, ex: 2026-10-19T10:30)
 */
public class FriendshipFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Friendship> {

    /**
     * @param validator validatorul pentru prietenii
     * @param fileName  calea catre fisier
     */
    public FriendshipFileRepository(Validator<Friendship> validator, String fileName) {
        super(validator, fileName);
    }


    /**
     * @param line - o linie cu formatul idUtilizator1;idUtilizator2;dataPrieteniei
     * @return prietenia descrisa de linie
     */
    @Override
    protected Friendship extractEntity(String line) {
        String[] fields = line.split(";", -1);
        Long id1 = Long.parseLong(fields[0].trim());
        Long id2 = Long.parseLong(fields[1].trim());
        LocalDateTime friendsFrom = LocalDateTime.parse(fields[2].trim());
        return new Friendship(id1, id2,  friendsFrom);
    }

    /**
     * @param friendship - prietenia de transformat
     * @return linia idUtilizator1;idUtilizator2;dataPrieteniei
     */
    @Override
    protected String createEntityAsString(Friendship friendship) {
        return friendship.getUserId1() + ";" + friendship.getUserId2()+ ";" + friendship.getFriendsFrom();
    }
}
