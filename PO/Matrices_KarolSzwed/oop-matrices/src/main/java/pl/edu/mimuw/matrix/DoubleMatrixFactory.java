package pl.edu.mimuw.matrix;

public class DoubleMatrixFactory {

    private DoubleMatrixFactory() {
    }

    public static IDoubleMatrix sparse(Shape shape, MatrixCellValue... values) {
        return new Sparse(shape, values);
    }

    public static IDoubleMatrix full(double[][] values) {
        return new Full(values);
    }

    public static IDoubleMatrix identity(int size) {
        return new Identity(size);
    }

    public static IDoubleMatrix diagonal(double... diagonalValues) {
        return new Diagonal(diagonalValues);
    }

    public static IDoubleMatrix antiDiagonal(double... antiDiagonalValues) {
        return new AntiDiagonal(antiDiagonalValues);
    }

    public static IDoubleMatrix vector(double... values){
        return new Vector(values);
    }

    public static IDoubleMatrix zero(Shape shape) {
        return new Null(shape);
    }

    public static IDoubleMatrix constant(Shape shape, double value) {
        return new Constant(shape, value);
    }

    public static IDoubleMatrix verse(int rows, double... rowValues) {
        return new Verse(rows, rowValues);
    }

    public static IDoubleMatrix columnar(int columns, double... columnValues) {
        return new Columnar(columns, columnValues);
    }

}