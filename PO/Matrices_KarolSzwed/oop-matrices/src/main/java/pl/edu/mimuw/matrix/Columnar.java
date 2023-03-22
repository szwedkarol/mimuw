package pl.edu.mimuw.matrix;

import java.util.Arrays;

public class Columnar extends DoubleMatrix {

    private final double[] columnValues;

    public Columnar(int columns, double... columnValues) {
        assert columns > 0;
        assert columnValues != null && columnValues.length > 0;
        this.columnValues = Arrays.copyOf(columnValues, columnValues.length);
        this.shape = Shape.matrix(columnValues.length, columns);
    }

    @Override
    public double get(int row, int column) {
        shape.assertInShape(row, column);
        return columnValues[row];
    }

    @Override
    public double[][] data() {
        double[][] result = new double[shape.rows][shape.columns];

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                result[i][j] = get(i, j);
            }
        }

        return result;
    }

    @Override
    /*
     * All columns have equal sum, so norm one value is based on a sum of elements
     * in "columnValues"
     */
    public double normOne() {
        double sumInColumn = 0.0;

        for (double columnValue : columnValues) {
            sumInColumn += Math.abs(columnValue);
        }

        return sumInColumn;
    }

    @Override
    /*
     * In a given row there are elements of equal value, so norm infinity is based
     * on the biggest value in 1st column of a matrix (multiplied by the number of
     * columns).
     */
    public double normInfinity() {
        double maxInColumn = Math.abs(columnValues[0]);

        for (double columnValue : columnValues) {
            if (Math.abs(columnValue) > maxInColumn) {
                maxInColumn = Math.abs(columnValue);
            }
        }

        return maxInColumn * shape.columns;
    }

    @Override
    public double frobeniusNorm() {
        double sumSquaresColumn = 0.0;

        for (double columnValue : columnValues) {
            sumSquaresColumn += columnValue * columnValue;
        }

        return Math.sqrt(sumSquaresColumn * shape.columns);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        appendShape(sb, this);

        if (shape.columns <= 2) {
            for (int i = 0; i < shape.rows; i++) {
                for (int j = 0; j < shape.columns; j++) {
                    sb.append(columnValues[j]);

                    if (j != shape.columns - 1) {
                        sb.append(" ");
                    }
                }
                sb.append("\n");
            }
        } else {
            for (int i = 0; i < shape.rows; i++) {
                sb.append(columnValues[i]).append(" ... ");
                sb.append(columnValues[i]).append("\n");
            }
        }

        return sb.toString();
    }

}