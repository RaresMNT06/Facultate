package domain.validators;

/**
 * Validation strategy for entities
 *
 * @param <T> - type of the entities to be validated
 */
@FunctionalInterface
public interface Validator<T> {

    /**
     *
     * @param entity - the entity to be validated
     * @throws ValidationException if the entity is not valid
     */
    void validate(T entity);

    default Validator<T> andThen(Validator<T> other) {
        if (other == null) {
            throw new IllegalArgumentException("Validator cannot be null");
        }
        return (entity) -> {
            this.validate(entity);
            other.validate(entity);
        };
    }
}