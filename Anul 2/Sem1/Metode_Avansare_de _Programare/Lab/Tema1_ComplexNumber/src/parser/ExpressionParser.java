package parser;

import domain.Expression;

public interface ExpressionParser {
    Expression parse(String[] args) throws InvalidExpressionException;
}
