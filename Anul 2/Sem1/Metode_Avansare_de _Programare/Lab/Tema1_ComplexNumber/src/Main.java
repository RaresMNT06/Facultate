import domain.Expression;
import operations.OperationFactory;
import parser.AlgebraicFormParser;
import parser.CommandLineParser;
import parser.ExpressionParser;
import parser.InvalidExpressionException;
import java.text.ParseException;

public class Main {

    public static void main(String[] args) {
        ExpressionParser parser = new CommandLineParser(
                new AlgebraicFormParser(),
                OperationFactory.getInstance()
        );

        try{
            Expression expression = parser.parse(args);
            System.out.println("Expresia este valida ");
            System.out.println("Rezultat: " + expression.evaluate() );
        } catch (InvalidExpressionException e) {
            System.out.println("Expresie invalide: "+e.getMessage());
        } catch (ArithmeticException e) {
            System.out.println("Eroare de calcul: "+e.getMessage());
        }
    }

}