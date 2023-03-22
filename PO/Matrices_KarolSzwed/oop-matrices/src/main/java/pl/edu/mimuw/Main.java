/*
 * Author: Karol Szwed
 * Date: 18.05.2022 r.
 * 1st big project for PO - Matrices
 */
package pl.edu.mimuw;

import pl.edu.mimuw.matrix.*;

import static pl.edu.mimuw.matrix.DoubleMatrixFactory.sparse;
import static pl.edu.mimuw.matrix.MatrixCellValue.cell;
import static pl.edu.mimuw.matrix.Shape.matrix;

public class Main {

    public static void main(String[] args) {
        System.out.println("All kinds of implemented matrices:\n");

        IDoubleMatrix AntiDiagonal = DoubleMatrixFactory.antiDiagonal(
                new double[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

        IDoubleMatrix Diagonal = DoubleMatrixFactory.diagonal(
                new double[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

        IDoubleMatrix Sparse = DoubleMatrixFactory.sparse(
                matrix(10, 10),
                cell(0, 2, 1),
                cell(0, 1, 12),
                cell(2, 7, 3),
                cell(4, 3, 15),
                cell(6, 6, 5),
                cell(8, 2, 16),
                cell(9, 4, 6));

        IDoubleMatrix Full = DoubleMatrixFactory.full(new double[][]{
                new double[]{1, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                new double[]{2, 2, 0, 0, 0, 0, 10, 10, 0, 0},
                new double[]{3, 2, 0, 0, 10, 0, 0, 0, 0, 0},
                new double[]{4, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                new double[]{5, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                new double[]{6, 2, 0, 0, 0, 0, 10, 0, 0, 0},
                new double[]{7, 2, 0, 0, 10, 0, 10, 0, 0, 0},
                new double[]{8, 2, 0, 0, 0, 0, 10, 0, 0, 0},
                new double[]{9, 2, 0, 0, 10, 0, 0, 0, 10, 0},
                new double[]{10, 2, 0, 0, 10, 0, 0, 0, 0, 0}});

        IDoubleMatrix Identity = DoubleMatrixFactory.identity(10);

        IDoubleMatrix Vector = DoubleMatrixFactory.vector(
                new double[]{1,2,3,4,5,6,7,8,9,10});


        IDoubleMatrix Null = DoubleMatrixFactory.zero(
                Shape.matrix(10, 10));

        IDoubleMatrix Constant = DoubleMatrixFactory.constant(
                Shape.matrix(10, 10), 4);

        IDoubleMatrix Verse = DoubleMatrixFactory.verse(10,
                new double[]{1,2,4,6,8,10,12,14,16,18});

        IDoubleMatrix Columnar = DoubleMatrixFactory.columnar(10,
                new double[]{0,2,4,6,8,10,12,14,16,123});

        System.out.println("Sparse matrix:");
        System.out.println(Sparse.toString());

        System.out.println("Full matrix:");
        System.out.println(Full.toString());

        System.out.println("Identity matrix:");
        System.out.println(Identity.toString());

        System.out.println("Diagonal matrix:");
        System.out.println(Diagonal.toString());

        System.out.println("Anti-diagonal matrix:");
        System.out.println(AntiDiagonal.toString());

        System.out.println("Vector:");
        System.out.println(Vector.toString());

        System.out.println("Null matrix:");
        System.out.println(Null.toString());

        System.out.println("Constant matrix:");
        System.out.println(Constant.toString());

        System.out.println("Verse matrix:");
        System.out.println(Verse.toString());

        System.out.println("Columnar matrix:");
        System.out.println(Columnar.toString());

    }
}
