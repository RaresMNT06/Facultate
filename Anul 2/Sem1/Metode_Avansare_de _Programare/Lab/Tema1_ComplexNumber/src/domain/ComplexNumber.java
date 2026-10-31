package domain;

public class ComplexNumber {

    private final double real;
    private final double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() {
        return real;
    }
    public double getImaginary() {
        return imaginary;
    }

    @Override
    public String toString() {
        if (imaginary == 0) {
            return format(real);
        }
        String sign = imaginary < 0 ? " - " : " + ";
        return format(real) + sign + format(Math.abs(imaginary)) + "*i";
    }

    private String format(double value) {
        if (value == Math.floor(value) && !Double.isInfinite(value)) {
            return String.valueOf((long)value);
        }
        return String.valueOf(value);
    }

}
