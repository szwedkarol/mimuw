package pl.edu.mimuw.matrix;

import java.util.Arrays;

public class Verse extends DoubleMatrix {

    private final double[] rowValues;

    public Verse(int rows, double... rowValues) {
        assert rows > 0;
        assert rowValues != null && rowValues.length > 0;
        this.rowValues = Arrays.copyOf(rowValues, rowValues.length);
        this.shape = Shape.matrix(rows, rowValues.length);
    }

    @Override
    public double get(int row, int column) {
        shape.assertInShape(row, column);
        return rowValues[column];
    }

    @Override
    public double[][] data() {
        double[][] result = new double[shape.rows][shape.columns];

        for (int i = 0; i < shape.rows; i++) {
            result[i] = Arrays.copyOf(rowValues, rowValues.length);
        }

        return result;
    }

    /*
     * In a given column there are elements of equal value, so norm infinity is
     * based on the biggest value in 1st row of a matrix (multiplied by the
     * number of rows).
     */
    @Override
    public double normOne() {
        double maxInRow = Math.abs(rowValues[0]);

        for (double rowValue : rowValues) {
            if (Math.abs(rowValue) > maxInRow) {
                maxInRow = rowValue;
            }
        }

        return maxInRow * shape.rows;
    }

    /*
     * All rows have equal sum, so norm one value is based on a sum of elements
     * in "rowValues"
     */
    @Override
    public double normInfinity() {
        double sumInRow = 0.0;

        for (double rowValue : rowValues) {
            sumInRow += Math.abs(rowValue);
        }

        return sumInRow;
    }

    @Override
    public double frobeniusNorm() {
        double sumSquaresRow = 0.0;

        for (double rowValue : rowValues) {
            sumSquaresRow += rowValue * rowValue;
        }

        return Math.sqrt(sumSquaresRow * shape.rows);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        StringBuilder row = new StringBuilder();

        appendShape(sb, this);

        for (int i = 0; i < rowValues.length; i++) {
            row.append(rowValues[i]);

            if (i != rowValues.length - 1) {
                row.append(" ");
            }
        }
        row.append("\n");

        return sb.toString() + row.toString().repeat(shape.rows);
    }

}