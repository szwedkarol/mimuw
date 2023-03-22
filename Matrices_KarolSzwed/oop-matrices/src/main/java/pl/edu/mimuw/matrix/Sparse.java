package pl.edu.mimuw.matrix;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Sparse extends DoubleMatrix {

    /*
     * "values" is a list of lists of MatrixCellValue objects. Main list is a list
     * of rows (sorted based on row index), then we have a list of non-zero cells in
     * that row (sorted based on column index).
     */
    private final List<List<MatrixCellValue>> values;
    private final int cellCount;

    public Sparse(Shape shape, MatrixCellValue... values) {
        assert shape != null;
        assert shape.rows > 0 && shape.columns > 0;
        this.shape = Shape.matrix(shape.rows, shape.columns);
        this.cellCount = values.length;
        this.values = new ArrayList<List<MatrixCellValue>>();

        for (int i = 0; i < values.length; i++) {
            int j; // index of a list based on a row of current MatrixCellValue
            int rowInList = 0;
            for (j = 0; j < this.values.size(); j++) {
                rowInList = this.values.get(j).get(0).row;
                if (values[i].row <= rowInList) {
                    break;
                }
            }

            int row = values[i].row;
            int column = values[i].column;
            double value = values[i].value;
            shape.assertInShape(row, column);

            if (this.values.size() <= j || values[i].row != rowInList) {
                ArrayList<MatrixCellValue> temp = new ArrayList<MatrixCellValue>();
                temp.add(MatrixCellValue.cell(row, column, value));
                this.values.add(j, temp);
            } else if (values[i].row == rowInList) {
                int k;
                for (k = 0; k < this.values.get(j).size(); k++) {
                    // Checks whether a cell with current row and column already
                    // exits in "values"
                    assert column != this.values.get(j).get(k).column;

                    if (column < this.values.get(j).get(k).column) {
                        break;
                    }
                }

                this.values.get(j).add(k, MatrixCellValue.cell(row, column, value));
            }
        }
    }

    @Override
    public double get(int row, int column) {
        shape.assertInShape(row, column);

        // Bin search used firstly on rows (on first element of all
        // linked lists), then on columns (so within a single list)

        int left = 0;
        int right = values.size() - 1;

        int indexRow = -1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (values.get(mid).get(0).row < row) {
                left = mid + 1;
            } else if (values.get(mid).get(0).row > row) {
                right = mid - 1;
            } else if (values.get(mid).get(0).row == row) {
                indexRow = mid;
                break;
            }
        }

        if (indexRow == -1) {
            // Cell with given index of a row does not exist in
            // "values", so it's a zero-element
            return 0.0;
        }

        int indexColumn = -1;

        left = 0;
        right = values.get(indexRow).size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (values.get(indexRow).get(mid).column < column) {
                left = mid + 1;
            } else if (values.get(indexRow).get(mid).column > column) {
                right = mid - 1;
            } else if (values.get(indexRow).get(mid).column == column) {
                indexColumn = mid;
                break;
            }
        }

        if (indexColumn == -1) {
            // Cell with given column index does not exist in
            // "values", so it's a zero-element
            return 0.0;
        } else {
            return values.get(indexRow).get(indexColumn).value;
        }
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

    /*
     * Returns an array of non-zero cells in the Sparse matrix
     */
    private MatrixCellValue[] getNonZeroArray() {
        MatrixCellValue[] result = new MatrixCellValue[cellCount];
        int index = 0;

        for (int i = 0; i < values.size(); i++) {
            for (int j = 0; j < values.get(i).size(); j++) {
                int row = values.get(i).get(j).row;
                int column = values.get(i).get(j).column;
                double value = values.get(i).get(j).value;

                MatrixCellValue cell = MatrixCellValue.cell(row, column, value);
                result[index] = cell;
                index++;
            }
        }

        return result;
    }

    @Override
    public IDoubleMatrix times(double scalar) {
        MatrixCellValue[] result = new MatrixCellValue[cellCount];
        int index = 0;

        for (int i = 0; i < values.size(); i++) {
            for (int j = 0; j < values.get(i).size(); j++) {
                int row = values.get(i).get(j).row;
                int column = values.get(i).get(j).column;
                double value = scalar * values.get(i).get(j).value;
                MatrixCellValue cell = MatrixCellValue.cell(row, column, value);
                result[index] = cell;
                index++;
            }
        }

        return new Sparse(shape, result);
    }

    @Override
    public IDoubleMatrix plus(double scalar) {
        double[][] result = new double[shape.rows][shape.columns];

        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.columns; j++) {
                result[i][j] = get(i, j) + scalar;
            }
        }

        return DoubleMatrixFactory.full(result);
    }

    @Override
    public IDoubleMatrix minus(double scalar) {
        return plus(-scalar);
    }

    /*
     * Returns: * 0, if cells have the same row and column; integer > 0, if cellB is
     * earlier in the matrix; integer < 0, if cellA is earlier in the matrix;
     * Earlier int the matrix means lower row index, or if rows are the same, then
     * lower column index.
     */
    private static int compareCells(MatrixCellValue cellA, MatrixCellValue cellB) {
        assert cellA != null && cellB != null;
        if (cellA.row > cellB.row) {
            return 1;
        } else if (cellA.row < cellB.row) {
            return -1;
        } else if (cellA.column > cellB.column) {
            // cellA.row == cellB.row
            return 1;
        } else if (cellA.column < cellB.column) {
            return -1;
        } else {
            // cellA.row == cellB.row && cellA.column == cellB.column
            return 0;
        }
    }

    private IDoubleMatrix optimisedTimes(Sparse other) {
        int size = 0;
        MatrixCellValue[] result = new MatrixCellValue[0];

        // To optimize multiplication, "other" matrix is sorted by columns
        // (Left matrix is already sorted by rows in "values" list)
        List<List<MatrixCellValue>> sortedColumns = new ArrayList<List<MatrixCellValue>>();

        // Sorting by columns right matrix ("Sparse other")
        MatrixCellValue[] B = other.getNonZeroArray();
        for (int i = 0; i < B.length; i++) {
            int j;
            for (j = 0; j < sortedColumns.size(); j++) {
                if (B[i].column <= sortedColumns.get(j).get(0).column) {
                    break;
                }
            }

            int row = B[i].row;
            int column = B[i].column;
            double value = B[i].value;

            if (sortedColumns.size() <= j || column != sortedColumns.get(j).get(0).column) {
                ArrayList<MatrixCellValue> temp = new ArrayList<MatrixCellValue>();
                temp.add(MatrixCellValue.cell(row, column, value));
                sortedColumns.add(j, temp);
            } else if (column == sortedColumns.get(j).get(0).column) {
                int k;
                for (k = 0; k < sortedColumns.get(j).size(); k++) {
                    assert row != sortedColumns.get(j).get(k).row;
                    if (row < sortedColumns.get(j).get(k).row) {
                        break;
                    }
                }

                sortedColumns.get(j).add(k, MatrixCellValue.cell(row, column, value));
            }
        }

        // Actual multiplication of matrices
        for (int i = 0; i < values.size(); i++) {
            for (int j = 0; j < sortedColumns.size(); j++) {
                int row = 0;
                int col = 0;
                double sum = 0.0;
                while (row < values.get(i).size() && col < sortedColumns.get(j).size()) {
                    if (values.get(i).get(row).column == sortedColumns.get(j).get(col).row) {
                        sum += values.get(i).get(row).value * sortedColumns.get(j).get(col).value;

                        row++;
                        col++;
                    } else if (values.get(i).get(row).column < sortedColumns.get(j).get(col).row) {
                        row++;
                    } else {
                        col++;
                    }
                }

                if (size >= result.length) {
                    result = Arrays.copyOf(result, size * 2 + 1);
                }

                result[size] = MatrixCellValue.cell(values.get(i).get(0).row,
                        sortedColumns.get(j).get(0).column, sum);
                size++;
            }
        }

        result = Arrays.copyOf(result, size);
        return new Sparse(Shape.matrix(shape().rows, other.shape().columns), result);
    }

    @Override
    public IDoubleMatrix times(IDoubleMatrix other) {
        assert other != null;
        shape().assertTimesMatrix(other);
        if (getClass() == other.getClass()) {
            return this.optimisedTimes(((Sparse) other));
        } else {
            return super.times(other);
        }
    }

    private IDoubleMatrix optimisedPlus(Sparse other) {
        MatrixCellValue[] valuesA = getNonZeroArray();
        MatrixCellValue[] valuesB = other.getNonZeroArray();
        MatrixCellValue[] result = new MatrixCellValue[0];
        int size = 0; // size of "result" array
        int iA = 0; // index of array "valuesA"
        int iB = 0; // index of array "valuesB"

        int row;
        int column;
        double value;

        while (iA < valuesA.length && iB < valuesB.length) {
            if (size >= result.length) {
                result = Arrays.copyOf(result, size * 2 + 1);
            }

            int comparison = compareCells(valuesA[iA], valuesB[iB]);

            if (comparison > 0) {
                row = valuesB[iB].row;
                column = valuesB[iB].column;
                value = valuesB[iB].value;
                result[size] = MatrixCellValue.cell(row, column, value);
                iB++;
            } else if (comparison < 0) {
                row = valuesA[iA].row;
                column = valuesA[iA].column;
                value = valuesA[iA].value;
                result[size] = MatrixCellValue.cell(row, column, value);
                iA++;
            } else { // compareCells(valuesA[iA], valuesB[iB]) == 0
                row = valuesA[iA].row;
                column = valuesA[iA].column;
                value = valuesA[iA].value + valuesB[iB].value;
                result[size] = MatrixCellValue.cell(row, column, value);
                iA++;
                iB++;
            }

            size++;
        }

        while (iA < valuesA.length) {
            if (size >= result.length) {
                result = Arrays.copyOf(result, size * 2 + 1);
            }

            row = valuesA[iA].row;
            column = valuesA[iA].column;
            value = valuesA[iA].value;

            result[size] = MatrixCellValue.cell(row, column, value);
            iA++;
            size++;
        }

        while (iB < valuesB.length) {
            if (size >= result.length) {
                result = Arrays.copyOf(result, size * 2 + 1);
            }

            row = valuesB[iB].row;
            column = valuesB[iB].column;
            value = valuesB[iB].value;

            result[size] = MatrixCellValue.cell(row, column, value);
            iB++;
            size++;
        }

        result = Arrays.copyOf(result, size);
        return new Sparse(shape, result);
    }

    @Override
    public IDoubleMatrix plus(IDoubleMatrix other) {
        assert other != null;
        assert shape().equals(other.shape());
        if (getClass() == other.getClass()) {
            return ((Sparse) other).optimisedPlus(this);
        } else {
            return other.plus(this);
        }
    }

    @Override
    public double normInfinity() {
        double sumInRow = 0.0;
        double result = 0.0;

        for (int i = 0; i < values.size(); i++) {
            sumInRow = 0;
            for (int j = 0; j < values.get(i).size(); j++) {
                sumInRow += Math.abs(values.get(i).get(j).value);
            }

            if (sumInRow > result) {
                result = sumInRow;
            }
        }

        return result;
    }

    @Override
    public double normOne() {
        double[] sumInColumn = new double[shape.columns];
        double result = 0.0;

        for (int i = 0; i < values.size(); i++) {
            for (int j = 0; j < values.get(i).size(); j++) {
                double value = Math.abs(values.get(i).get(j).value);
                sumInColumn[values.get(i).get(j).column] += value;
            }
        }

        for (int i = 0; i < sumInColumn.length; i++) {
            if (sumInColumn[i] > result) {
                result = sumInColumn[i];
            }
        }

        return result;
    }

    @Override
    public double frobeniusNorm() {
        double sumOfSquares = 0.0;

        for (int i = 0; i < values.size(); i++) {
            for (int j = 0; j < values.get(i).size(); j++) {
                double value = values.get(i).get(j).value;
                sumOfSquares += value * value;
            }
        }

        return Math.sqrt(sumOfSquares);
    }

}
