package parser;

import domain.ComplexNumber;

// parses numbers written as a+b*i
public class AlgebraicFormParser implements NumberParser {
    // optional sign, digits, optional dot + decimals
    private static final String NUMBER_REGEX = "[+-]?\\d+(\\.\\d+)?";

    @Override
    public ComplexNumber parse(String text) throws InvalidExpressionException {
        if (text == null || text.isEmpty()) {
            throw new InvalidExpressionException("numar complex vid");
        }
        // no "i" at the end -> real number
        if (!text.endsWith("i")) {
            return new ComplexNumber(parseReal(text, text), 0);
        }
        String withoutI = text.substring(0, text.length() - 1);
        int signIndex = findLastSignIndex(withoutI);

        String realPart;
        String imaginaryPart;
        if (signIndex == -1) {
            realPart = "0";
            imaginaryPart = withoutI;
        } else {
            realPart = withoutI.substring(0, signIndex);
            imaginaryPart = withoutI.substring(signIndex);

        }

        return new ComplexNumber(parseReal(realPart, text), parseImaginary(imaginaryPart, text));

    }

    // last + or - that is NOT on position 0 separates the real part from the imaginary part
    private int findLastSignIndex(String text) {
        for (int i = text.length()-1;  i>0; i--) {
            char c = text.charAt(i);
            if (c == '+' || c == '-') {
                return i;
            }
        }
        return -1;
    }

    private double parseReal(String part, String original) throws InvalidExpressionException {
        if(!part.matches(NUMBER_REGEX)) {
            throw new InvalidExpressionException("numar complex invalid: " + original);
        }
        return Double.parseDouble(part);
    }

    // "" or "+" -> 1 ; "-" -> -1 ; "3*" -> 3 ; "-6*" -> -6
    private double parseImaginary(String part, String original) throws InvalidExpressionException {
        if(part.isEmpty() || part.equals("+")) {
            return 1;
        }
        if(part.equals("-")) {
            return -1;
        }
        if(!part.endsWith("*")) {
            throw new InvalidExpressionException("lipseste '*' inainte de i: " + original);
        }
        return parseReal(part.substring(0, part.length()-1), original);
    }

}
