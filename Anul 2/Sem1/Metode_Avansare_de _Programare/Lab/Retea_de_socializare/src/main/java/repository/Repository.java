package repository;

import exceptions.ValidationException;
import model.Entity;
import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

/**
 * Interfata pentru operatiile CRUD ale unui repository
 *
 * @param <ID> - tipul identificatorului; E trebuie sa aiba un atribut de tip ID
 * @param <E>  - tipul entitatilor salvate in repository
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * cauta o entitate dupa id
     *
     * @param id - id-ul entitatii cautate; nu poate fi null
     * @return entitatea cu id-ul dat sau null daca nu exista
     * @throws IllegalArgumentException daca id-ul este null
     */
    E findOne(ID id);

    /**
     * @return toate entitatile
     */
    Iterable<E> findAll();

    /**
     * salveaza o entitate noua
     *
     * @param entity - entitatea de salvat; nu poate fi null
     * @return null - daca entitatea a fost salvata,
     * altfel entitatea (id-ul exista deja)
     * @throws ValidationException      daca entitatea nu este valida
     * @throws IllegalArgumentException daca entitatea este null
     */
    E save(E entity);

    /**
     * sterge entitatea cu id-ul dat
     *
     * @param id - id-ul entitatii de sters; nu poate fi null
     * @return entitatea stearsa sau null daca nu exista o entitate cu id-ul dat
     * @throws IllegalArgumentException daca id-ul este null
     */
    E delete(ID id);

    /**
     * actualizeaza o entitate existenta
     *
     * @param entity - entitatea cu datele noi; nu poate fi null
     * @return null - daca entitatea a fost actualizata,
     * altfel entitatea (id-ul nu exista)
     * @throws ValidationException      daca entitatea nu este valida
     * @throws IllegalArgumentException daca entitatea este null
     */
    E update(E entity);

    /**
     * transforma toate entitatile din repository intr-un stream
     * (metoda ajutatoare, scrisa o singura data, folosita de service-uri)
     *
     * @return un stream secvential cu toate entitatile
     */
    default Stream<E> stream() {
        return StreamSupport.stream(findAll().spliterator(), false);
    }

    /**
     * cauta entitatile care respecta un criteriu
     *
     * @param filter - criteriul de cautare (Predicate); nu poate fi null
     * @return lista entitatilor pentru care filter.test(entitate) este true
     * @throws IllegalArgumentException daca filter este null
     */
    default List<E> findAll(Predicate<E> filter) {
        if (filter == null) {
            throw new IllegalArgumentException("filter must not be null");
        }
        return stream()
                .filter(filter)
                .toList();
    }
}