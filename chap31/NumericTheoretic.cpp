//
// Created by yijun on 9/25/16.
//

#include <cmath>
#include <iostream>
#include <bitset>
#include <vector>
#include "NumericTheoretic.h"

int NumericTheoretic::Euclid(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return Euclid(a, b);
    }
}

DXY NumericTheoretic::ExtendedEuclid(int a, int b) {
    DXY dxy;

    if (b == 0) {
        dxy.d = a;
        dxy.x = 1;
        dxy.y = 0;
        return dxy;
    } else {
        DXY dxy1 = ExtendedEuclid(b, a % b);
        dxy.d = dxy1.d;
        dxy.x = dxy1.x;
        dxy.y = dxy1.x - a / b * dxy1.y;
        return dxy;
    }
}

void NumericTheoretic::ModularLinearEquationSolver(int a, int b, int n) {
    DXY dxy = ExtendedEuclid(a, n);

    if (b % dxy.d != 0) {
        int x0 = (dxy.x * b / dxy.d) % n;
        for (int i = 0; i < dxy.d; i++) {
            std::cout << (x0 + i * (n / dxy.d)) % n;
        }
    } else {
        std::cout << " no solutions " << std::endl;
    }
}

int NumericTheoretic::ModularExponentation(int a, int b, int n) {
    int c = 0;
    int d = 1;

    std::bitset<8 * sizeof(b)> bitsetOfb(b);

    for (int i = 8 * sizeof(b) - 1; i >= 0; i--) {
        c = 2 * c;
        d = (d * d) % n;
        if (bitsetOfb[i] == 1) {
            c = c + 1;
            d = (d * a) % n;
        }
    }

    return d;
}

bool NumericTheoretic::Witness(int a, int n) {
    std::srand(static_cast<unsigned>(time(nullptr)));

    int j = 1;
    double u = 1;
    double t;
    std::vector<int> x;

    std::cout << " n " << n << std::endl;

    for (;; u += 2) {
        t = std::log2((n - 1) / u);
//        std::cout << " t " << t << " static cast " << static_cast<int>(t) << std::endl;
//        std::cout << " static cast delta " << t - static_cast<int>(t)<< std::endl;
        if ((t - static_cast<int>(t)) == 0.0) {
            break;
        }
    }

    std::cout << " t " << t << " u " << u << std::endl;

    x.resize(static_cast<int>(t + 1));

    x.at(0) = ModularExponentation(a, u, n);
    std::cout << " x0 " << x.at(0) << std::endl;

    for (int i = 1; i < t + 1; i++) {
        x.at(i) = (x.at(i - 1) * x.at(i - 1)) % n;
        if (x.at(i) == 1 && x.at(i - 1) != 1 && x.at(i - 1) != (n - 1)) {
            return true;
        }
    }

    std::cout << " output x " << std::endl;
    for (std::vector<int>::iterator iter = x.begin(); iter != x.end(); iter++) {
        std::cout << "  " << *iter << "  ";
    }
    std::cout << std::endl;

    if (x.at(t) != 1) {
        return true;
    }

    return false;
}

bool NumericTheoretic::MillerRabin(int n, int s) {
    for (int j = 1; j <= s; j++) {
        int a = rand() % n;

        while (a == 0) {
            a = rand() % n;
        }

        if (Witness(a, n)) {
            return false;
        }
    }

    return true;
}

void NumericTheoretic::PollardRHO(int n) {
    int i = 1;
//    std

    int x = std::rand() % (n - 1);
    int y = x;
    int k = 2;
    int d;

    while (true) {
        i = i + 1;
        x = (x * x - 1) % n;
        d = Euclid(y - x, n);
        if (d != 1 && d != n) {
            std::cout << "  " << d << "  " << std::endl;
        }

        if (i == k) {
            y = x;
            k = 2 * k;
        }
    }
}
