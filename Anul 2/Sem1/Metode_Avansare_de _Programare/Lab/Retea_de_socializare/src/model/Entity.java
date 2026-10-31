package model;

import java.util.Objects;

/**
 * Clasa de baza pentru toate entitatile care au un identificator.
 *
 * @param <ID> tipul identificatorului
 */

public class Entity<ID> {

    private ID id;

    public ID getId() {
        return id;
    }
    public void setId(ID id) {
        this.id = id;
    }


    /**
     * doua entitati sunt egale daca au acelasi tip si acelasi id
     *
     * @param o - obiectul cu care se compara
     * @return true - daca o este o entitate de acelasi tip cu acelasi id, false altfel
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity<?> entity = (Entity<?>) o;
        return Objects.equals(id, entity.id);
    }


    /**
     * @return codul hash calculat din id (entitati egale au acelasi cod hash)
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }


}
