//
// Created by yijun on 6/16/16.
//

#include <iostream>
#include <ctime>
#include <gtest/gtest.h>

#include "StrassenMatrixMultiply.h"

TEST(StrassenMatrixMultiplyTest, StrassenMatrixMultiply) {

    StrassenMatrixMultiply* matrixMultiply;
    int matrixSize = 0;
    int** matrixA;
    int** matrixB;
    int** matrixC;

    clock_t startTime;
    clock_t endTime;

    time_t start;
    time_t end;

    srand(time(0));

    std::cout << std::endl;
    std::cout << "Please Enter your Matrix Size(must be in a power of two(eg:32,64,512,..): ";
    std::cin >> matrixSize;

    matrixMultiply = new StrassenMatrixMultiply(matrixSize);

    matrixA = new int *[matrixSize];
    matrixB = new int *[matrixSize];
    matrixC = new int *[matrixSize];

    for (int i = 0; i < matrixSize; i++) {
        matrixA[i] = new int [matrixSize];
        matrixB[i] = new int [matrixSize];
        matrixC[i] = new int [matrixSize];
    }

    matrixMultiply->fillMatrix(matrixA, 5);
    matrixMultiply->fillMatrix(matrixB, 7);

    matrixMultiply->strassenMultiply(matrixA, matrixB, matrixC);

    matrixMultiply->printMatrix(matrixA);
    matrixMultiply->printMatrix(matrixB);
    matrixMultiply->printMatrix(matrixC);

}

