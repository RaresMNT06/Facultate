package repository.file;

import exceptions.ValidationException;
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
     * checks the rule of the file format: no field may contain ';' (the separator)
     *
     * @param user - the user to check
     * @throws ValidationException if a field contains ';'
     */
    private void checkNoSeparator(User user) {
        if (user != null && String.join("", user.getFirstName(), user.getLastName(),
                user.getEmail(), user.getPassword()).contains(";")) {
            throw new ValidationException("fields must not contain ';' (the separator of the file)");
        }
    }

    @Override
    public User save(User user) {
        checkNoSeparator(user);
        return super.save(user);
    }

    @Override
    public User update(User user) {
        checkNoSeparator(user);
        return super.update(user);
    }
    /**
     * @return the next free id: the largest existing id + 1 (or 1 if there are no users)
     */
    @Override
    protected Long generateId() {
        return stream()
                .mapToLong(User::getId)
                .max()
                .orElse(0) + 1;
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
    protected String createEntityAsString(User user) {
        return user.getId() + ";" + user.getFirstName() + ";" + user.getLastName() + ";"
                + user.getEmail() + ";" + user.getPassword();
    }
}