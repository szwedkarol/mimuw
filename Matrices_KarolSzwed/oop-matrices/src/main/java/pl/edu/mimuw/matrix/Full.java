package pl.edu.mimuw.matrix;

import java.util.Arrays;

public class Full extends DoubleMatrix {

    private final double[][] values;

    public Full(double[][] values) {
        assert values != null && values.length > 0 && values[0].length > 0;
        assertFullRowLength(values);
        this.values = new double[values.length][values[0].length];
        for (int i = 0; i < values.length; i++) {
            this.values[i] = Arrays.copyOf(values[i], values[i].length);
        }
        this.shape = Shape.matrix(values.length, values[0].length);
    }

    private void assertFullRowLength(double[][] values) {
        int length = values[0].length;
        for (int i = 0; i < values.length; i++) {
            assert length == values[i].length;
        }
    }

    @Override
    public double get(int row, int column) {
        shape.assertInShape(row, column);

        return values[row][column];
    }

    @Override
    public double[][] data() {
        double[][] result = new double[values.length][values[0].length];
        for (int i = 0; i < values.length; i++) {
            result[i] = Arrays.copyOf(values[i], values[i].length);
        }
        return result;
    }

    @Override
    public double normInfinity() {
        double result = -Double.MAX_VALUE;
        double rowSum = 0.0;

        for (int i = 0; i < values.length; i++) {
            rowSum = 0.0;
            for (int j = 0; j < values[0].length; j++) {
                rowSum += Math.abs(values[i][j]);
            }

            if (rowSum > result) {
                result = rowSum;
            }
        }

        return result;
    }

    @Override
    public double normOne() {
        double result = -Double.MAX_VALUE;
        double columnSum = 0.0;

        for (int j = 0; j < values[0].length; j++) {
            columnSum = 0.0;
            for (int i = 0; i < values.length; i++) {
                columnSum += Math.abs(values[i][j]);
            }

            if (columnSum > result) {
                result = columnSum;
            }
        }

        return result;
    }

    @Override
    public double frobeniusNorm() {
        double sumOfSquares = 0.0;
        double result;

        for (int i = 0; i < values.length; i++) {
            for (int j = 0; j < values[0].length; j++) {
                sumOfSquares += values[i][j] * values[i][j];
            }
        }

        result = Math.sqrt(sumOfSquares);

        return result;
    }

}
