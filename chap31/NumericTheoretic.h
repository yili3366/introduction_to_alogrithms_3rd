//
// Created by yijun on 9/25/16.
//

#ifndef CHAP31_NUMERICTHEORETIC_H
#define CHAP31_NUMERICTHEORETIC_H

struct DXY {
    int d;
    int x;
    int y;
};

class NumericTheoretic {
public:
    int Euclid(int a, int b);
    DXY ExtendedEuclid(int a, int b);
    void ModularLinearEquationSolver(int a, int b, int n);
    int ModularExponentation(int a, int b, int n);
    bool Witness(int a, int n);
    bool MillerRabin(int n, int s);
    void PollardRHO(int n);
};

#endif //CHAP31_NUMERICTHEORETIC_H
