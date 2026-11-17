package repository.file;

import model.User;
import validators.Validator;


/**
 * Repository in fisier text pentru utilizatori; cate un utilizator pe linie,
 * cu formatul id;prenume;nume;email;parola
 */
public class UserFileRepository extends AbstractFileRepository<Long, User> {
    /**
     * @param validator validatorul pentru utilizatori
     * @param fileName  calea catre fisier
     */

    public UserFileRepository(Validator<User> validator, String fileName) {
        super(validator, fileName);
    }


    /**
     * @param line - o linie cu formatul id;prenume;nume;email;parola
     * @return utilizatorul descris de linie
     */
    @Override
    protected User extractEntity(String line) {
        String[] fields = line.split(";", -1);
        User user = new User(fields[1], fields[2], fields[3], fields[4]);
        user.setId(Long.parseLong(fields[0]));
        return user;
    }

    /**
     * @param user - utilizatorul de transformat
     * @return linia id;prenume;nume;email;parola
     */
    @Override
    protected String createEntityAsString(User user){
        return user.getId() + ";"+ user.getFirstName() + ";"+ user.getLastName() + ";"+ user.getEmail()+";"+ user.getPassword();
    }
}
