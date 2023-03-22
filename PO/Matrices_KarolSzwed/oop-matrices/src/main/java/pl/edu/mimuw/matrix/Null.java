package pl.edu.mimuw.matrix;

public class Null extends Constant {

    public Null(Shape shape) {
        super(shape, 0.0);
    }

    @Override
    public IDoubleMatrix times(double scalar) {
        // Multiplying null matrix by anything results in a null matrix
        return DoubleMatrixFactory.zero(shape);
    }

    @Override
    public IDoubleMatrix times(IDoubleMatrix other ) {
        assert other != null;
        // Multiplying null matrix by another matrix results in a null matrix
        shape.assertTimesMatrix(other);
        return DoubleMatrixFactory.zero(Shape.matrix(shape().rows, other.shape().columns));
    }
}
