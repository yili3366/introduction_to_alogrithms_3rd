//
// Created by yijun on 6/16/16.
//

#include "StrassenMatrixMultiply.h"

#include <iostream>

StrassenMatrixMultiply::StrassenMatrixMultiply(int matrixSize) {
    mMatrixSize = matrixSize;
}

int StrassenMatrixMultiply::strassenMultiply(int **matrixA, int **matrixB, int **matrixC) {

    int halfSize = mMatrixSize / 2;
    int rowSize = mMatrixSize / 2;

    int **A11;
    int **A12;
    int **A21;
    int **A22;

    int **B11;
    int **B12;
    int **B21;
    int **B22;

    int **C11;
    int **C12;
    int **C21;
    int **C22;

    int **P1;
    int **P2;
    int **P3;
    int **P4;
    int **P5;
    int **P6;
    int **P7;

    int **S1;
    int **S2;
    int **S3;
    int **S4;
    int **S5;
    int **S6;
    int **S7;
    int **S8;
    int **S9;
    int **S10;

    int columnSize = rowSize;

    if (mMatrixSize <= mThreshold) {
        mul(matrixA, matrixB, matrixC, mMatrixSize);
    } else {
        A11 = new int *[rowSize];
        A12 = new int *[rowSize];
        A21 = new int *[rowSize];
        A22 = new int *[rowSize];

        B11 = new int *[rowSize];
        B12 = new int *[rowSize];
        B21 = new int *[rowSize];
        B22 = new int *[rowSize];

        C11 = new int *[rowSize];
        C12 = new int *[rowSize];
        C21 = new int *[rowSize];
        C22 = new int *[rowSize];

        P1 = new int *[rowSize];
        P2 = new int *[rowSize];
        P3 = new int *[rowSize];
        P4 = new int *[rowSize];
        P5 = new int *[rowSize];
        P6 = new int *[rowSize];
        P7 = new int *[rowSize];


        S1 = new int *[rowSize];
        S2 = new int *[rowSize];
        S3 = new int *[rowSize];
        S4 = new int *[rowSize];
        S5 = new int *[rowSize];
        S6 = new int *[rowSize];
        S7 = new int *[rowSize];
        S8 = new int *[rowSize];
        S9 = new int *[rowSize];
        S10 = new int *[rowSize];

        for (int i = 0; i < rowSize; i++) {
            A11[i] = new int[columnSize];
            A12[i] = new int[columnSize];
            A21[i] = new int[columnSize];
            A22[i] = new int[columnSize];

            B11[i] = new int[columnSize];
            B12[i] = new int[columnSize];
            B21[i] = new int[columnSize];
            B22[i] = new int[columnSize];

            C11[i] = new int[columnSize];
            C12[i] = new int[columnSize];
            C21[i] = new int[columnSize];
            C22[i] = new int[columnSize];

            P1[i] = new int[columnSize];
            P2[i] = new int[columnSize];
            P3[i] = new int[columnSize];
            P4[i] = new int[columnSize];
            P5[i] = new int[columnSize];
            P6[i] = new int[columnSize];
            P7[i] = new int[columnSize];

            S1[i] = new int[columnSize];
            S2[i] = new int[columnSize];
            S3[i] = new int[columnSize];
            S4[i] = new int[columnSize];
            S5[i] = new int[columnSize];
            S6[i] = new int[columnSize];
            S7[i] = new int[columnSize];
            S8[i] = new int[columnSize];
            S9[i] = new int[columnSize];
            S10[i] = new int[columnSize];
        }

        // split input matrice
        for (int i = 0; i < mMatrixSize / 2; i++) {
            for (int j = 0; j < mMatrixSize / 2; j++) {
                A11[i][j] = matrixA[i][j];
                A12[i][j] = matrixA[i][j + mMatrixSize / 2];
                A21[i][j] = matrixA[i + mMatrixSize / 2][j];
                A22[i][j] = matrixA[i + mMatrixSize / 2][j + mMatrixSize / 2];

                B11[i][j] = matrixB[i][j];
                B12[i][j] = matrixB[i][j + mMatrixSize / 2];
                B21[i][j] = matrixB[i + mMatrixSize / 2][j];
                B22[i][j] = matrixB[i + mMatrixSize / 2][j + mMatrixSize / 2];
            }
        }

        //S1 to S10
        sub(B12, B22, S1, halfSize);
        add(A11, A12, S2, halfSize);
        add(A21, A22, S3, halfSize);
        sub(B21, B11, S4, halfSize);
        add(A11, A22, S5, halfSize);
        add(B11, B22, S6, halfSize);
        sub(A12, A22, S7, halfSize);
        add(B21, B22, S8, halfSize);
        sub(A11, A21, S9, halfSize);
        add(B11, B12, S10, halfSize);

        //P1[][] to P7[][]
        mul(A11, S1, P1, halfSize);
        mul(S2, B22, P2, halfSize);
        mul(S3, B11, P3, halfSize);
        mul(A22, S4, P4, halfSize);
        mul(S5, S6, P5, halfSize);
        mul(S7, S8, P6, halfSize);
        mul(S9, S10, P7, halfSize);

        //matrixC
        //C11
        add(P5, P4, C11, halfSize);
        sub(C11, P2, C11, halfSize);
        add(C11, P6, C11, halfSize);

        //C12
        add(P1, P2, C12, halfSize);

        //C21
        add(P3, P4, C21, halfSize);

        //C22
        add(P5, P1, C22, halfSize);
        sub(C22, P3, C22, halfSize);
        sub(C22, P7, C22, halfSize);

        for (int i = 0; i < columnSize; i++) {
            delete[] A11[i];
            delete[] A12[i];
            delete[] A21[i];
            delete[] A22[i];

            delete[] B11[i];
            delete[] B12[i];
            delete[] B21[i];
            delete[] B22[i];

            delete[] C11[i];
            delete[] C12[i];
            delete[] C21[i];
            delete[] C22[i];

            delete[] P1[i];
            delete[] P2[i];
            delete[] P3[i];
            delete[] P4[i];
            delete[] P5[i];
            delete[] P6[i];
            delete[] P7[i];

            delete[] S1[i];
            delete[] S2[i];
            delete[] S3[i];
            delete[] S4[i];
            delete[] S5[i];
            delete[] S6[i];
            delete[] S7[i];
            delete[] S8[i];
            delete[] S9[i];
            delete[] S10[i];
        }

        delete[] A11;
        delete[] A12;
        delete[] A21;
        delete[] A22;

        delete[] B11;
        delete[] B12;
        delete[] B21;
        delete[] B22;

        delete[] C11;
        delete[] C12;
        delete[] C21;
        delete[] C22;

        delete[] P1;
        delete[] P2;
        delete[] P3;
        delete[] P4;
        delete[] P5;
        delete[] P6;
        delete[] P7;

        delete[] S1;
        delete[] S2;
        delete[] S3;
        delete[] S4;
        delete[] S5;
        delete[] S6;
        delete[] S7;
        delete[] S8;
        delete[] S9;
        delete[] S10;
    }

    return 0;
}

int StrassenMatrixMultiply::add(int **matrixA, int **matrixB, int **matrixResult, int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixResult[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    return 0;
}

int StrassenMatrixMultiply::sub(int **matrixA, int **matrixB, int **matrixResult, int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixResult[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    return 0;
}

int StrassenMatrixMultiply::mul(int **matrixA, int **matrixB, int **matrixResult, int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixResult[i][j] = 0;
            for (int k = 0; k < matrixSize; k++) {
                matrixResult[i][j] = matrixResult[i][j] + matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return 0;
}

void StrassenMatrixMultiply::printMatrix(int **matrix) {
    std::cout << std::endl;
    for (int row = 0; row < mMatrixSize; row++) {
        for (int column = 0; column < mMatrixSize; column++) {
            std::cout << matrix[row][column] << "\t";
            if ((column + 1) % ((mMatrixSize)) == 0)
                std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void StrassenMatrixMultiply::fillMatrix(int **matrix, int mod) {
    for (int row = 0; row < mMatrixSize; row++) {
        for (int column = 0; column < mMatrixSize; column++) {
            matrix[row][column] = rand() % mod;
        }
    }
}
