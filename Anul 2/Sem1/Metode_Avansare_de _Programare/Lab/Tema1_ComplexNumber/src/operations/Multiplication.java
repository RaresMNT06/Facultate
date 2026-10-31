package operations;

import domain.ComplexNumber;

public class Multiplication implements Operation {

    // (x + y*i)(u + v*i) = (xu - yv) + (xv + yu)*i
    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double x = a.getReal();
        double y = a.getImaginary();
        double u = b.getReal();
        double v = b.getImaginary();
        return new ComplexNumber(x * u - y * v, x * v + y * u);
    }

    @Override
    public String getSymbol() {
        return "*";
    }
}