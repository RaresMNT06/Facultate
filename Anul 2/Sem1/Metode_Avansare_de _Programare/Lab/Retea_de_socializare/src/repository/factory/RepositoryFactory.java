package repository.factory;

import exceptions.ConfigurationException;
import model.Friendship;
import model.User;
import model.Tuple;
import repository.InMemoryRepository;
import repository.Repository;
import repository.db.FriendshipDbRepository;
import repository.db.UserDbRepository;
import repository.file.FriendshipFileRepository;
import repository.file.UserFileRepository;
import validators.Validator;

import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.nio.charset.StandardCharsets;
import java.util.Properties;

/**
 * Simple Factory pentru repository-uri.
 * Este singurul loc din aplicatie care cunoaste clasele concrete de repository;
 * tipul de persistenta si parametrii lui sunt cititi din config.properties.
 * Ambele repository-uri sunt create pentru acelasi tip de persistenta.
 */

public class RepositoryFactory {

    private static final String DEFAULT_CONFIG_FILE = "src/main/resources/config.properties";

    private final Properties properties;
    private final RepositoryType type;

    /**
     * creeaza factory-ul folosind fisierul de configurare implicit
     *
     * @throws ConfigurationException daca fisierul lipseste sau repository.type este lipsa ori necunoscut
     */
    public RepositoryFactory() {
        this(DEFAULT_CONFIG_FILE);
    }

    /**
     * creeaza factory-ul folosind fisierul de configurare dat
     *
     * @param configFile - calea catre fisierul de configurare
     * @throws ConfigurationException daca fisierul lipseste sau repository.type este lipsa ori necunoscut
     */
    public RepositoryFactory(String configFile) {
        this.properties = loadProperties(configFile);
        this.type = readType();
    }


    /**
     * @return tipul de persistenta citit din configurare
     */
    public RepositoryType getType() {
        return type;
    }

    /**
     * creeaza repository-ul de utilizatori pentru tipul de persistenta din configurare
     *
     * @param validator - strategia de validare pentru utilizatori
     * @return repository-ul de utilizatori (tipul abstract Repository)
     * @throws ConfigurationException daca lipseste un parametru necesar tipului ales
     */
    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        switch (type) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new UserFileRepository(validator, getRequired("file.users"));
            case DATABASE:
                return new UserDbRepository(validator,
                        getRequired("db.url"), getRequired("db.user"), getRequired("db.password"));
            default:
                throw new IllegalArgumentException("Unknown repository type: " + type);
        }
    }

    /**
     * creeaza repository-ul de prietenii pentru tipul de persistenta din configurare
     *
     * @param validator - strategia de validare pentru prietenii
     * @return repository-ul de prietenii (tipul abstract Repository)
     * @throws ConfigurationException daca lipseste un parametru necesar tipului ales
     */
    public Repository<Tuple<Long, Long>, Friendship> createFriendshipRepository(Validator<Friendship> validator) {
        switch (type) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new FriendshipFileRepository(validator, getRequired("file.friendships"));
            case DATABASE:
                return new FriendshipDbRepository(validator,
                        getRequired("db.url"), getRequired("db.user"), getRequired("db.password"));
            default:
                throw new IllegalArgumentException("Unknown repository type: " + type);
        }
    }

    /**
     * incarca fisierul de configurare intr-un obiect Properties
     *
     * @param configFile - calea catre fisierul de configurare
     * @return proprietatile citite
     * @throws ConfigurationException daca fisierul nu poate fi citit
     */
    private static Properties loadProperties(String configFile) {
        Properties properties = new Properties();
        try (Reader reader = new FileReader(configFile, StandardCharsets.UTF_8)) {
            properties.load(reader);
        } catch (IOException e) {
            throw new ConfigurationException("Cannot load properties file: " + configFile, e);
        }
        return properties;
    }

    /**
     * @param key - cheia cautata in configurare
     * @return valoarea cheii, fara spatii la capete
     * @throws ConfigurationException daca cheia lipseste sau are valoare goala
     */
    private String getRequired(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank()) {
            throw new ConfigurationException("Missing configuration key: " + key);
        }
        return value.trim();
    }

    /**
     * @return tipul de persistenta din cheia repository.type
     * @throws ConfigurationException daca valoarea lipseste sau nu este MEMORY, FILE ori DATABASE
     */
    private RepositoryType readType() {
        String value = getRequired("repository.type");
        try{
            return RepositoryType.valueOf(value.toUpperCase());
        } catch (IllegalArgumentException e){
            throw new ConfigurationException("Unknown repository type: " + value+" (expected MEMORY, FILE or DATABASE)", e);
        }
    }
}
