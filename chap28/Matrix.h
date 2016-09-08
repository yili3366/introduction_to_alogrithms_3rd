//
// Created by yijun on 9/6/16.
//

#ifndef CHAP28_MATRIX_H
#define CHAP28_MATRIX_H

#include <vector>

template<typename T>
struct LU {
    std::vector<std::vector<T>> L;
    std::vector<std::vector<T>> U;
};

template<typename T>
class Matrix {
public:
    std::vector<T> LupSolve(std::vector<std::vector<T>> L,
                            std::vector<std::vector<T>> U,
                            std::vector<T> Pi,
                            std::vector<T> b);
    LU<T> LuDecomposition(std::vector<std::vector<T>> A);
    std::vector<T> LupDecomposition(std::vector<std::vector<T>> &A);
private:
//    T Sum(std::vector<std::vector<T>> Matrix, std::vector<T> vector, int i, int j);
};

#if 0
template<typename T>
T Matrix<T>::Sum(std::vector<std::vector<T>> Matrix, std::vector<T> vector, int lower, int upper) {
    T sum = 0;
    for (int j = lower; j < upper; j++) {
        sum = Matrix.at(upper).at(j) * vector.at(j);
    }

    return sum;
}
#endif

template<typename T>
std::vector<T> Matrix<T>::LupSolve(std::vector<std::vector<T>> L,
                                   std::vector<std::vector<T>> U,
                                   std::vector<T> Pi,
                                   std::vector<T> b) {
    int n = L.begin()->size();
    std::vector<T> x;
    std::vector<T> y;

    x.resize(n);
    y.resize(n);

    std::cout << " print L " << std::endl;
    for (typename std::vector<std::vector<T>>::iterator row = std::begin(L); row != std::end(L); row++) {
        for (typename std::vector<T>::iterator column = std::begin(*row); column != std::end(*row); column++) {
            std::cout << "  " << *column << "  ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < n; i++) {
        T sumLy = 0.0;

        for (int j = 0; j < i; j++) {
            sumLy = sumLy + L.at(i).at(j) * y.at(j);
        }

        y.at(i) = b.at(Pi.at(i)) - sumLy;
    }


    for (int i = n - 1; i >= 0; i--) {
        T sumUx = 0.0;

        for (int j = i + 1; j < n; j++) {
            sumUx = sumUx + U.at(i).at(j) * x.at(j);
        }

        x.at(i) = (y.at(i) - sumUx) / U.at(i).at(i);
    }

    return x;
}

template<typename T>
LU<T> Matrix<T>::LuDecomposition(std::vector<std::vector<T>> A) {
    int n = A.begin()->size();
    std::vector<std::vector<T>> L;
    std::vector<std::vector<T>> U;

    struct LU<T> lu;

    L.resize(n);
    U.resize(n);

    for (int i = 0; i < n; i++) {
        L.at(i).assign(n, 1);
        U.at(i).assign(n, 1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            U.at(i).at(j) = 0;
        }

        for (int k = i + 1; k < n; k++) {
            L.at(i).at(k) = 0;
        }
    }

    for (int k = 0; k < n; k++) {
        U.at(k).at(k) = A.at(k).at(k);

        for (int i = k + 1; i < n; i++) {
            L.at(i).at(k) = A.at(i).at(k) / U.at(k).at(k);
            U.at(k).at(i) = A.at(k).at(i);
        }

        for (int i = k + 1; i < n; i++) {
            for (int j = k + 1; j < n; j++) {
                A.at(i).at(j) = A.at(i).at(j) - L.at(i).at(k) * U.at(k).at(j);
            }
        }
    }

    lu.L = L;
    lu.U = U;

    return lu;
}

template<typename T>
std::vector<T> Matrix<T>::LupDecomposition(std::vector<std::vector<T>> &A) {
    int n = A.begin()->size();
    std::vector<T> Pi;

    Pi.resize(n);

    for (int i = 0; i < n; i++) {
        Pi.at(i) = i;
    }

    for (int k = 0; k < n; k++) {
        T p = 0;
        int k1 = k;

        for (int i = k; i < n; i++) {
            if (std::abs(A.at(i).at(k)) > p) {
                p = std::abs(A.at(i).at(k));
                k1 = i;
            }
        }

        std::cout << " k1 " << k1 << std::endl;
        if (p == 0) {
            std::cout << "singular matrix" << std::endl;
        }

        std::swap(Pi.at(k), Pi.at(k1));
        for (int i = 0; i < n; i++) {
            std::swap(A.at(k).at(i), A.at(k1).at(i));
        }

        for (int i = k + 1; i < n; i++) {
            A.at(i).at(k) = A.at(i).at(k) / A.at(k).at(k);
            for (int j = k + 1; j < n; j++) {
                A.at(i).at(j) = A.at(i).at(j) - A.at(i).at(k) * A.at(k).at(j);
            }
        }
    }

    return Pi;
}

#endif //CHAP28_MATRIX_H