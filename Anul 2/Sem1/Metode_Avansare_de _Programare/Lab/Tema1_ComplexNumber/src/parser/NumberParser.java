package parser;

import domain.ComplexNumber;

public interface NumberParser {
    ComplexNumber parse(String expression) throws InvalidExpressionException;
}

