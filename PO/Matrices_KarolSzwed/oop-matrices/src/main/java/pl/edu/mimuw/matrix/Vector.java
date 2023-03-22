package pl.edu.mimuw.matrix;

import java.util.Arrays;

public class Vector extends DoubleMatrix {

    private final double[] values;

    public Vector(double... values) {
        assert values != null && values.length > 0;
        this.values = Arrays.copyOf(values, values.length);
        this.shape = Shape.vector(values.length);
    }

    @Override
    public double get(int row, int column) {
        shape.assertInShape(row, column);

        return values[row];
    }

    @Override
    public double[][] data() {
        double[][] result = new double[values.length][1];

        for (int i = 0; i < values.length; i++) {
            result[i][0] = values[i];
        }

        return result;
    }

    @Override
    public double normInfinity() {
        double result = values[0];

        for (double value : values) {
            if (Math.abs(value) > result) {
                result = Math.abs(value);
            }
        }

        return result;
    }

    @Override
    public double normOne() {
        double result = 0.0;

        for (double value : values) {
            result += Math.abs(value);
        }

        return result;
    }

    @Override
    public double frobeniusNorm() {
        double result = 0.0;

        for (double value : values) {
            result += value * value;
        }

        result = Math.sqrt(result);
        return result;
    }

}
