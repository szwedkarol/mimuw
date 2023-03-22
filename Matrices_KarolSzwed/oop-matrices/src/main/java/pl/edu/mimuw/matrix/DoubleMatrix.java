package pl.edu.mimuw.matrix;

import java.lang.Double;
import java.util.Arrays;

public abstract class DoubleMatrix implements IDoubleMatrix {

    protected Shape shape = null;

    @Override
    public abstract double get(int row, int column);

    @Override
    public abstract double[][] data();

    @Override
    public abstract double normOne();

    @Override
    public abstract double normInfinity();

    @Override
    public abstract double frobeniusNorm();

    @Override
    public Shape shape() {
        return Shape.matrix(shape.rows, shape.columns);
    }

    @Override
    public IDoubleMatrix minus(double scalar) {
        return plus(-scalar);
    }

    @Override
    public IDoubleMatrix plus(double scalar) {
        // Adding or subtracting 0 (scalar) does not change the matrix
        if (Double.compare(0.0, scalar) == 0) {
            return DoubleMatrixFactory.full(this.data());
        }

        int rows = this.shape().rows;
        int columns = this.shape().columns;
        double[][] result = new double[rows][columns];
        for (int i = 0; i < rows; i++) {
            result[i] = Arrays.copyOf(this.data()[i], columns);
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result[i][j] += scalar;
            }
        }

        return DoubleMatrixFactory.full(result);
    }

    @Override
    public IDoubleMatrix times(double scalar) {
        // Multiplying by 0 (scalar) results in a null matrix
        if (Double.compare(scalar, 0.0) == 0) {
            return DoubleMatrixFactory.zero(this.shape());
        }

        // Multiplying by 1 (scalar) does not change the matrix
        if (Double.compare(scalar, 1.0) == 0) {
            return DoubleMatrixFactory.full(this.data());
        }

        int rows = this.shape().rows;
        int columns = this.shape().columns;
        double[][] result = new double[rows][columns];
        for (int i = 0; i < rows; i++) {
            result[i] = Arrays.copyOf(this.data()[i], columns);
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result[i][j] *= scalar;
            }
        }

        return DoubleMatrixFactory.full(result);
    }

    @Override
    public IDoubleMatrix times(IDoubleMatrix other) {
        assert other != null;
        Shape shape = this.shape();
        Shape otherShape = other.shape();
        shape.assertTimesMatrix(other);

        double[][] result = new double[shape.rows][otherShape.columns];

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < otherShape.columns; j++) {
                double sum = 0;
                for (int k = 0; k < shape.columns; k++) {
                    sum += get(i, k) * other.get(k, j);
                }

                result[i][j] = sum;
            }
        }

        return DoubleMatrixFactory.full(result);
    }

    @Override
    public IDoubleMatrix plus(IDoubleMatrix other) {
        assert other != null;
        Shape shape = Shape.matrix(shape().rows, shape().columns);
        // We can only add matrices of equal shapes
        assert this.shape().equals(other.shape());

        double[][] result = new double[shape.rows][shape.columns];

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                result[i][j] = get(i, j) + other.get(i, j);
            }
        }

        return DoubleMatrixFactory.full(result);
    }

    @Override
    public IDoubleMatrix minus(IDoubleMatrix other) {
        return plus(other.times(-1.0));
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        appendShape(sb, this);

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                sb.append(get(i, j));

                if (j != shape.columns - 1) {
                    sb.append(" ");
                }
            }
            sb.append("\n");
        }

        return sb.toString();
    }

    // Puts size of the matrix at the start of the result of toString()
    public static void appendShape(StringBuilder sb, IDoubleMatrix matrix) {
        assert matrix != null;
        Shape shape = matrix.shape();

        sb.append("Dimensions: ");
        sb.append(shape.rows).append(" x ").append(shape.columns).append("\n");
    }
}