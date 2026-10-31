package operations;

import domain.ComplexNumber;

public class Division implements Operation {

    // (x + y*i)/(u + v*i) = [(xu + yv) + (yu - xv)*i] / (u^2 + v^2)
    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double x = a.getReal();
        double y = a.getImaginary();
        double u = b.getReal();
        double v = b.getImaginary();

        double denominator = u * u + v * v;
        if (denominator == 0) {
            throw new ArithmeticException("Impartire la 0");
        }
        return new ComplexNumber((x * u + y * v) / denominator, (y * u - x * v) / denominator);
    }

    @Override
    public String getSymbol() {
        return "/";
    }
}