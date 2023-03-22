package pl.edu.mimuw.matrix;

public class AntiDiagonal extends SparseDiagonal {

    public AntiDiagonal(double... antiDiagonalValues) {
        super(antiDiagonalValues);
    }

    @Override
    public double get(int rows, int columns) {
        shape.assertInShape(rows, columns);

        double result = 0.0;

        if (rows + columns == diagonal.length - 1) {
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
                if (i + j == diagonal.length - 1) {
                    sb.append(diagonal[i]);
                    // After the anti-diagonal we have only 0 and there are >= 3
                    if (diagonal.length - j - 1 >= 3) {
                        sb.append(" 0 ... 0");
                        j = shape.columns;
                    }

                    while ( j < shape.columns - 1 ) {
                        sb.append(" 0");
                        j++;
                    }
                } else if (diagonal.length - 1 - (i + j) >= 3) {
                    // Up to the anti-diagonal we have only 0 and there are >= 3
                    sb.append("0 ... 0");
                    j = diagonal.length - 1 - i - 1;
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
                if (i + j == diagonal.length - 1) {
                    result[i][j] = diagonal[i];
                } else {
                    result[i][j] = 0;
                }
            }
        }

        return result;
    }

}
