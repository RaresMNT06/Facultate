package operations;

public class OperationFactory {
    private static OperationFactory instance;

    // simple array, no generic collections (requirement)
    private final Operation[] operations;

    private OperationFactory() {
        operations = new Operation[] {
                new Addition(),
                new Subtraction(),
                new Multiplication(),
                new Division()
        };
    }

    public static OperationFactory getInstance() {
        if (instance == null) {
            instance = new OperationFactory();
        }
        return instance;
    }

    // Factory: "+" -> Addition ; unknown symbol -> null
    public Operation getOperation(String symbol) {
        for (Operation operation : operations) {
            if (operation.getSymbol().equals(symbol)) {
                return operation;
            }
        }
        return null;
    }
}