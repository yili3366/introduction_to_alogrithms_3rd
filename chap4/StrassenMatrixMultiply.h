//
// Created by yijun on 6/16/16.
//

#ifndef CHAP4_STRASSENMATRIXMULTIPLY_H
#define CHAP4_STRASSENMATRIXMULTIPLY_H


class StrassenMatrixMultiply {
public:
    StrassenMatrixMultiply(int maxtrixSize = 64);

    int strassenMultiply(int **matrixA, int **matrixB, int **matrixC);

    int add(int **matrixA, int **matrixB, int **matrixResult, int matrixSize);

    int sub(int **matrixA, int **matrixB, int **matrixResult, int matrixSize);

    int mul(int **matrixA, int **matrixB, int **matrixResult, int matrixSize);

    void fillMatrix(int **matrixA, int mod);
    void printMatrix(int **matrix);

private:
    int mMatrixSize;
    const int mThreshold = 64;
};

#endif //CHAP4_STRASSENMATRIXMULTIPLY_H
