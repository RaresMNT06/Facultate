package parser;

import domain.ComplexNumber;
import domain.Expression;
import operations.Operation;
import operations.OperationFactory;

public class CommandLineParser implements ExpressionParser {

    private final NumberParser numberParser;
    private final OperationFactory factory;


    public CommandLineParser(NumberParser numberParser, OperationFactory factory) {
        this.numberParser = numberParser;
        this.factory = factory;
    }

    @Override
    public Expression parse(String[] args) throws InvalidExpressionException{
        // n1 op n2 op ... op nk -> odd number of arguments, at least 3
        if (args == null || args.length < 3 || args.length % 2 == 0){
            throw new InvalidExpressionException("Invalid number of arguments");
        }

        Operation operation = factory.getOperation(args[1]);
        if (operation == null) {
            throw new InvalidExpressionException("operator necunoscut: " + args[1]);
        }

        ComplexNumber[] numbers =  new ComplexNumber[(args.length+1) / 2];
        for (int i = 0; i<args.length; i++) {
            if (i%2 == 0){
                numbers[i/2] = numberParser.parse(args[i]);
            } else if (!args[i].equals(operation.getSymbol())) {
                throw new InvalidExpressionException("Operatorii trebuie sa fie la fel: " + args[i]);
            }
        }

        return new Expression(numbers, operation);
    }
}
