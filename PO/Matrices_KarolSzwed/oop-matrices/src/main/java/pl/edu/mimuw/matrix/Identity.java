package pl.edu.mimuw.matrix;

public class Identity extends DoubleMatrix {

    public Identity(int size) {
        assert size > 0;
        this.shape = Shape.matrix(size, size);
    }

    @Override
    public double normOne() {
        return 1.0;
    }

    @Override
    public double normInfinity() {
        return 1.0;
    }

    @Override
    public double frobeniusNorm() {
        int size = shape.rows;

        return Math.sqrt(size);
    }

    @Override
    public IDoubleMatrix times(IDoubleMatrix other) {
        shape.assertTimesMatrix(other);
        // Multiplying by identity matrix does not change the original matrix
        return other;
    }

    @Override
    public double[][] data() {
        double[][] result = new double[shape.rows][shape.columns];

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                if (i == j) {
                    result[i][j] = 1;
                } else {
                    result[i][j] = 0;
                }
            }
        }

        return result;
    }

    @Override
    public double get(int rows, int columns) {
        shape.assertInShape(rows, columns);
        double result = 1.0;

        if (rows != columns) {
            result = 0.0;
        }

        return result;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        appendShape(sb, this);

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                if (i == j) {
                    sb.append("1");
                } else if (i >= 3 && j == 0) {
                    // Up to the diagonal we have only 0 and there are >= 3
                    sb.append("0 ... 0");
                    j = i - 1;
                } else if (shape.columns - i - 1 >= 3 && j > i) {
                    // Up to the end of row we have only 0 and there are >= 3
                    sb.append("0 ... 0");
                    j = shape.columns;
                } else {
                    sb.append("0");
                }

                if (j != shape.columns - 1) {
                    sb.append(" ");
                }
            }

            sb.append("\n");
        }

        return sb.toString();
    }

}