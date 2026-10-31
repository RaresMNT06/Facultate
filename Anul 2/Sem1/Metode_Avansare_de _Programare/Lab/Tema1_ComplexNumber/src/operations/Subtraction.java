package operations;

import domain.ComplexNumber;

public class Subtraction implements Operation {

    // (x + y*i) - (u + v*i) = (x - u) + (y - v)*i
    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        return new ComplexNumber(
                a.getReal() - b.getReal(),
                a.getImaginary() - b.getImaginary()
        );
    }

    @Override
    public String getSymbol() {
        return "-";
    }
}