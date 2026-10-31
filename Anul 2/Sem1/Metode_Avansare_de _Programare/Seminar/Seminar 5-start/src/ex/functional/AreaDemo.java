package ex.functional;

import java.util.ArrayList;
import java.util.List;

public class AreaDemo {

    public static <E> void printArea(List<E> figures, Area<E> area) {
        for (E figure : figures) {
            System.out.println(area.compute(figure));
        }
    }

    public static void main(String[] args) {
        List<Circle> circles = List.of(new Circle(2),
                new Circle(3), new Circle(4));

        Area<Circle> annonymousArea = new Area<Circle>() {
            @Override
            public double compute(Circle figure) {
                return Math.PI * figure.getRadius() * figure.getRadius();
            }
        };

        System.out.println("Anonymous Area ");
        printArea(circles, annonymousArea);


        Area<Circle> lambdaArea= c->Math.PI*c.getRadius()*c.getRadius();
        System.out.println("lambda Area ");
        printArea(circles, lambdaArea);

        Area<Circle> referenceArea= Circle::area;
        System.out.println("reference Area ");
        printArea(circles, referenceArea);


        System.out.println("Square Area ");
        List<Square> squares = List.of(new Square(4), new Square(3));
        printArea(squares, s-> s.getSide()*s.getSide());
    }
}