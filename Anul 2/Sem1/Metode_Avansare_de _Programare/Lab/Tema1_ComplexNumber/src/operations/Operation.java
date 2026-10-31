package operations;

import domain.ComplexNumber;

public interface Operation {
    ComplexNumber apply(ComplexNumber a, ComplexNumber b);

    String getSymbol();

}
