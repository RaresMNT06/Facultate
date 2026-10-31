package repository.factory;


import domain.User;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.db.UserDbRepository;
import repository.file.UserFileRepository;
import domain.validators.Validator;


import java.util.Properties;

public class RepositoryFactory {

    private final Properties properties;

    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        RepositoryType type = readType();
        switch (type) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new UserFileRepository(validator, getRequired("file.name"));
            case DATABASE:
                return new UserDbRepository(validator,
                        getRequired("db.url"),
                        getRequired("db.username"),
                        getRequired("db.password"));
            default:
                throw new IllegalArgumentException("Unknown repository type: " + type);
        }

    }

    private RepositoryType readType() {
        String value = getRequired("repository.type");
        try{
            return RepositoryType.valueOf(value.trim().toUpperCase());
        }catch (IllegalArgumentException e){
            throw new IllegalArgumentException("Unknown repository type: '" + value+ "'", e);
        }

    }

    private String getRequired(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank())
            throw new IllegalArgumentException("Missing required property: " + key);
        return value;
    }

}
