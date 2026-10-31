package domain;

import operations.Operation;


public class Expression {
        private final ComplexNumber[] numbers;
        private final Operation operation;

        public Expression(ComplexNumber[] numbers, Operation operation){
            this.numbers = numbers;
            this.operation = operation;
        }

        public ComplexNumber evaluate(){
            ComplexNumber result = numbers[0];
            for (int i = 1; i < numbers.length; i++){
                result = operation.apply(result, numbers[i]);
            }
            return result;
        }


}
