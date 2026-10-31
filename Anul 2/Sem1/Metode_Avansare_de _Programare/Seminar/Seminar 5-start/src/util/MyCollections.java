package util;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BinaryOperator;
import java.util.function.Function;

public class MyCollections {

    private MyCollections() {
    }

    /**
     * copies the elements of an Iterable into a new list
     * (e.g. the result of Repository.findAll())
     *
     * @param elements - the elements to be copied; must not be null
     * @param <E>      - type of the elements
     * @return a new, modifiable list with the same elements, in the same order
     */
    public static <E> List<E> toList(Iterable<E> elements) {
        List<E> result = new ArrayList<>();
        elements.forEach(result::add);      // referinta la metoda unui obiect anume
        return result;
    }

    /**
     * applies a function to every element (the "map" operation)
     *
     * @param elements - the elements to be transformed; must not be null
     * @param f        - the transformation applied to each element; must not be null
     * @param <T>      - type of the elements
     * @param <R>      - type of the results
     * @return the list of results, in the order of the elements
     */
    public static <T, R> List<R> transform(Iterable<T> elements, Function<T, R> f) {
        List<R> result = new ArrayList<>();
        for (T e : elements)
            result.add(f.apply(e));
        return result;
    }

    /**
     * combines all the elements, two by two, with an operator (the "reduce" operation)
     *
     * @param elements - the elements to be combined; must not be null
     * @param op       - the operator that combines two elements into one; must not be null
     * @param <E>      - type of the elements
     * @return the result of the combination
     * or null - if there are no elements
     */
    public static <E> E reduce(Iterable<E> elements, BinaryOperator<E> op) {
        E result = null;
        for (E e : elements)
            result = (result == null) ? e : op.apply(result, e);
        return result;
    }
}
