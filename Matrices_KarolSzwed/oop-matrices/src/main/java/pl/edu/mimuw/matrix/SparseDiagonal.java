package pl.edu.mimuw.matrix;

import java.util.Arrays;

public abstract class SparseDiagonal extends DoubleMatrix {

    protected final double[] diagonal;

    public SparseDiagonal(double... diagonalValues) {
        assert diagonalValues != null && diagonalValues.length > 0;
        this.diagonal = Arrays.copyOf(diagonalValues, diagonalValues.length);
        this.shape = Shape.matrix(diagonalValues.length, diagonalValues.length);
    }

    @Override
    public double normOne() {
        double result = diagonal[0];

        for (double diagonalValue : diagonal) {
            if (Math.abs(diagonalValue) > result) {
                result = Math.abs(diagonalValue);
            }
        }

        return result;
    }

    @Override
    public double normInfinity() {
        // Both norms (one and infinity) are equal for a diagonal matrix
        return this.normOne();
    }

    @Override
    public double frobeniusNorm() {
        double result;
        double sum = 0.0;

        for (double diagonalValue : diagonal) {
            sum += diagonalValue * diagonalValue;
        }

        result = Math.sqrt(sum);

        return result;
    }

}
