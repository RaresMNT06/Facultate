package model;

import java.util.Objects;

/**
 * Pereche de doua valori.
 *
 * @param <E1> tipul primului element
 * @param <E2> tipul celui de-al doilea element
 */

public class Tuple<E1, E2> {

    private E1 left;
    private E2 right;

    /**
     * @param left  primul element
     * @param right al doilea element
     */
    public Tuple(E1 left,E2 right) {
        this.left = left;
        this.right = right;
    }

    /** @return primul element*/
    public E1 getLeft() {
        return left;
    }

    /** @return al doilea element*/
    public E2 getRight() {
        return right;
    }


    /**
     * doua perechi sunt egale daca au elementele egale, pe aceleasi pozitii
     *
     * @param o - obiectul cu care se compara
     * @return true - daca o este un Tuple cu aceleasi elemente, false altfel
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Tuple<?, ?> tuple = (Tuple<?, ?>) o;
        return Objects.equals(left, tuple.left) && Objects.equals(right, tuple.right);
    }

    /**
     * @return codul hash calculat din ambele elemente
     */
    @Override
    public int hashCode() {
        return Objects.hash(left, right);
    }

    @Override
    public String toString() {
        return "(" + left + ", " + right + ")";
    }

}
