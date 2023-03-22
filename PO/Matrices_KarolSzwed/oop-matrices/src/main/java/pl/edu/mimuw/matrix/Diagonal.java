package pl.edu.mimuw.matrix;

public class Diagonal extends SparseDiagonal {

    public Diagonal(double... diagonalValues) {
        super(diagonalValues);
    }

    @Override
    public double get(int rows, int columns) {
        shape.assertInShape(rows, columns);

        double result = 0.0;

        if (rows == columns) {
            result = diagonal[rows];
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
                    sb.append(diagonal[i]);
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

    @Override
    public double[][] data() {
        double[][] result = new double[shape.rows][shape.columns];

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                if (i == j) {
                    result[i][j] = diagonal[i];
                } else {
                    result[i][j] = 0;
                }
            }
        }

        return result;
    }

}
