//
// Created by yijun on 9/6/16.
//

#include <vector>

#include <gtest/gtest.h>
#include "Matrix.h"

TEST(LupSolve, Matrix) {
    std::vector<std::vector<double>> L;
    std::vector<std::vector<double>> U;
    std::vector<std::vector<double>> P;
    std::vector<double> b;
    std::vector<double> x;
    std::vector<double> Pi;

    Matrix<double> *matrix = new Matrix<double>{};
    ASSERT_TRUE(matrix != nullptr);

    L = {{1.0, 0, 0}, {0.2, 1.0, 0}, {0.6, 0.5, 1.0}};
    U = {{5.0, 6.0, 3.0}, {0, 0.8, -0.6}, {0, 0, 2.5}};
    P = {{0, 0, 1.0}, {1.0, 0, 0}, {0, 1.0, 0}};
    b = {3.0, 7.0, 8.0};

    Pi.resize(P.size());
    for (int i = 0; i < P.size(); i++) {
        for (int j = 0; j < P.begin()->size(); j++) {
            if (P.at(i).at(j) == 1) {
                Pi.at(i) = j;
            }
        }
    }

    for (int i = 0; i < Pi.size(); i++) {
        std::cout << i << "  " << Pi.at(i) << std::endl;
    }

    x = matrix->LupSolve(L, U, Pi, b);

    std::cout << " x is " << std::endl;
    for (int i = 0; i < L.size(); i++) {
        std::cout << "  " << x.at(i) << "  ";
    }
    std::cout << std::endl;
}

TEST(LuDecomposition, Matrix) {
    std::vector<std::vector<double>> A;
    struct LU<double> lu;

    A = {{2, 3, 1, 5},
         {6, 13, 5, 19},
         {2, 19, 10, 23},
         {4, 10, 11, 31}};

    Matrix<double> *matrix = new Matrix<double>{};
    ASSERT_TRUE(matrix != nullptr);

    lu = matrix->LuDecomposition(A);

    std::cout << " print L " << std::endl;
    for (int i = 0; i < A.begin()->size(); i++) {
        for (int j = 0; j < A.begin()->size(); j++) {
            std::cout << "  " << lu.L.at(i).at(j) << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << " print U " << std::endl;
    for (int i = 0; i < A.begin()->size(); i++) {
        for (int j = 0; j < A.begin()->size(); j++) {
            std::cout << "  " << lu.U.at(i).at(j) << "  ";
        }
        std::cout << std::endl;
    }
}

TEST(LupDecomposition, Matrix) {
    std::vector<std::vector<double>> A;
    std::vector<double> Pi;

    A = {{2, 0, 2, 0.6},
         {3, 3, 4, -2},
         {5, 5, 4, 2},
         {-1, -2, 3.4, -1}};

    Matrix<double> *matrix = new Matrix<double>{};
    ASSERT_TRUE(matrix != nullptr);

    Pi = matrix->LupDecomposition(A);

    std::cout << " A " << std::endl;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.begin()->size(); j++) {
            std::cout << "  " << A.at(i).at(j) << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << " Pi " << std::endl;
    for (int i = 0; i < A.size(); i++) {
        std::cout << "  " << Pi.at(i) << "  ";
    }
    std::cout << std::endl;
}
