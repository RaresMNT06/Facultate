package repository.factory;

/**
 * Tipurile de persistenta suportate de aplicatie.
 * Valoarea este citita din config.properties (cheia repository.type).
 */

public enum RepositoryType {

    /** entitatile sunt pastrate doar in memorie (se pierd la inchidere) */
    MEMORY,

    /** entitatile sunt pastrate in fisiere text */
    FILE,

    /** entitatile sunt pastrate in baza de date (implementat la laboratorul 4) */
    DATABASE
}
