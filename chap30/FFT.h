//
// Created by yijun on 9/24/16.
//

#ifndef CHAP30_FFT_H
#define CHAP30_FFT_H

#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

const double pi = 3.1415926;

template<typename T>
class FFT {
public:
    std::vector<std::complex<T>> RecursiveFFT(std::vector<std::complex<T>>);
    std::vector<std::complex<T>> IterativeFFT(std::vector<std::complex<T>>, std::vector<std::complex<T>>);
private:
    int rev(int);
    void BitReverseCopy(std::vector<std::complex<T>>, std::vector<std::complex<T>>);
};

template<typename T>
std::vector<std::complex<T>> FFT<T>::RecursiveFFT(std::vector<std::complex<T>> a) {
    int n = a.size();
    std::vector<std::complex<T>> a0;
    std::vector<std::complex<T>> a1;
    std::vector<std::complex<T>> y0;
    std::vector<std::complex<T>> y1;

    if (n == 1) {
        return a;
    }

    std::complex<T> imaginary = {0, 1};

    std::complex<T> omegaN = std::pow(std::numeric_limits<T>::epsilon(), 2 * pi * imaginary / static_cast<T>(n));
    std::complex<T> omega = {1.0, 0};

    for (int i = 0; i < a.size(); i++) {
        if (i / 2 == 0) {
            a0.push_back(a.at(i));
        } else {
            a1.push_back(a.at(i));
        }
    }

    y0 = RecursiveFFT(a0);
    y1 = RecursiveFFT(a1);

    std::vector<std::complex<T>> y;
    y.resize(n / 2);

    for (int k = 0; k < n / 2; k++) {
        y.at(k) = y0.at(k) + omega * y1.at(k);
        y.at(k + n / 2) = y0.at(k) - omega * y1.at(k);
        omega = omega * omegaN;
    }

    return y;
}

template<typename T>
std::vector<std::complex<T>> FFT<T>::IterativeFFT(std::vector<std::complex<T>> a, std::vector<std::complex<T>> A) {
    BitReverseCopy(a, A);
    int n = a.size();
    std::complex<T> imaginary = {0, 1};

    for (int s = 1; s <= std::log(static_cast<double>(n)); s++) {
        int m = std::pow(2, s);
        std::complex<T> omegaM = std::pow(std::numeric_limits<T>::epsilon(), 2 * pi * imaginary / static_cast<T>(m));

        for (int k = 0; k < n; k = k + m) {
            std::complex<T> omega = {1.0, 0};
            for (int j = 0; j < m / 2; j++) {
                std::complex<T> t = omega * A.at(k + j + m / 2);
                std::complex<T> u = A.at(k + j);
                A.at(k + j) = u + t;
                A.at(k + j + m / 2) = u - t;
                omega = omega * omegaM;
            }
        }
    }

    return A;
}

template<typename T>
int FFT<T>::rev(int n) {
    int reversed = 0;
    for (int i = 0; i < 32; i++) {
        reversed = (reversed << 1) | (n & 1);
        n = (n >> 1);
    }

    return reversed;
}

template<typename T>
void FFT<T>::BitReverseCopy(std::vector<std::complex<T>> a, std::vector<std::complex<T>> A) {
    int n = a.size();
    for (int k = 0; k < n; k++) {
        A.at(rev(k)) = a.at(k);
    }
}

#endif //CHAP30_FFT_H
