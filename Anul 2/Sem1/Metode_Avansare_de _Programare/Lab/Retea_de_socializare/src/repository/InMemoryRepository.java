package repository;

import model.Entity;
import validators.Validator;

import java.util.HashMap;
import java.util.Map;

/**
 * Repository care pastreaza entitatile in memorie.
 *
 * @param <ID> tipul identificatorului
 * @param <E>  tipul entitatilor
 */

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {

    private final Validator<E> validator;
    private final Map<ID, E> entities;

    /**
     * @param validator strategia de validare folosita la save/update
     */
    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        this.entities = new HashMap<>();
    }

    @Override
    public E findOne(ID id) {
        if (id == null){
            throw new IllegalArgumentException("Id must not be null");
        }
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) {
        if (entity == null || entity.getId() == null){
            throw new IllegalArgumentException("Entity and its id must not be null");
        }
        validator.validate(entity);
        if (entities.containsKey(entity.getId())) {
            return entity;
        }
        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null){
            throw new IllegalArgumentException("Id must not be null");
        }
        return entities.remove(id);
    }

    @Override
    public E update(E entity) {
        if (entity == null || entity.getId() == null){
            throw new IllegalArgumentException("Entity and its id must not be null");
        }
        validator.validate(entity);
        if (!entities.containsKey(entity.getId())) {
            return entity;
        }
        entities.put(entity.getId(), entity);
        return null;
    }
}
