package ex.functional;

@FunctionalInterface
public interface Area<E> {

    double compute(E figure);
}
