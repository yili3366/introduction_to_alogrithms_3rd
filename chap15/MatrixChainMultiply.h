//
// Created by yijun on 7/1/16.
//

#ifndef CHAP15_MATRIXCHAINMULTIPLY_H
#define CHAP15_MATRIXCHAINMULTIPLY_H

#include <vector>

class Info {
private:
    std::vector<std::vector<int>> m;
    std::vector<std::vector<int>> s;
public:
    inline void SetM(std::vector<std::vector<int>> &in) {
        m = in;
    };

    inline void SetS(std::vector<std::vector<int>> &in) {
        s = in;
    };
};

class MatrixChainMultiply {
public:
    Info MatrixChainOrder(std::vector<int> &p, std::vector<std::vector<int>> &m, std::vector<std::vector<int>> &s);
    void PrintOptimalParens(const std::vector<std::vector<int>> &s, int i, int j);
    int MemorizedMatrixChain(std::vector<int> &p);
    int LookupChain(std::vector<std::vector<int>> &m, std::vector<int> &p, int i, int j);
};

#endif //CHAP15_MATRIXCHAINMULTIPLY_H
