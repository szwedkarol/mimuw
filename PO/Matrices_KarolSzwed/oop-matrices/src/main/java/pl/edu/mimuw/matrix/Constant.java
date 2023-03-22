package pl.edu.mimuw.matrix;

public class Constant extends DoubleMatrix {

    private final double value;

    public Constant(Shape shape, double value) {
        assert shape != null;
        assert shape.rows > 0 && shape.columns > 0;
        this.value = value;
        this.shape = Shape.matrix(shape.rows, shape.columns);
    }

    @Override
    public double normOne() {
        return Math.abs(value) * shape.rows;
    }

    @Override
    public double normInfinity() {
        return Math.abs(value) * shape.columns;
    }

    @Override
    public double frobeniusNorm() {
        double sumOfSquares = value * value * shape.rows * shape.columns;

        return Math.sqrt(sumOfSquares);
    }

    @Override
    public IDoubleMatrix times(double scalar) {
        if (Double.compare(scalar, 0.0) == 0) {
            // Multiplying by 0 (scalar) results in a null matrix
            return DoubleMatrixFactory.zero(this.shape());
        } else {
            return new Constant(shape, value * scalar);
        }
    }

    @Override
    public IDoubleMatrix plus(double scalar) {
        return new Constant(shape, value + scalar);
    }

    @Override
    public IDoubleMatrix minus(double scalar) {
        return plus(-scalar);
    }

    @Override
    public double get(int row, int column) {
        shape.assertInShape(row, column);
        return value;
    }

    @Override
    public double[][] data() {
        double[][] result = new double[shape.rows][shape.columns];

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                result[i][j] = value;
            }
        }

        return result;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        appendShape(sb, this);

        if (shape.columns <= 2) {
            for (int i = 0; i < shape.rows; i++) {
                for (int j = 0; j < shape.columns; j++) {
                    sb.append(value);

                    if (j != shape.columns - 1) {
                        sb.append(" ");
                    }
                }
                sb.append("\n");
            }
        } else {
            for (int i = 0; i < shape.rows; i++) {
                sb.append(value).append(" ... ").append(value).append("\n");
            }
        }

        return sb.toString();
    }

}
