//
// Created by yijun on 7/1/16.
//

#include <gtest/gtest.h>
#include "MatrixChainMultiply.h"

TEST(MatrixChainMultiplyTest, MatrixChainMultiply) {
    int k[] = {30, 35, 15, 5, 10, 20, 25};
    std::vector<int> p(k, k + sizeof(k) / sizeof(k[0]));
    std::vector<std::vector<int>> m;
    std::vector<std::vector<int>> s;
    MatrixChainMultiply *matrixChainMultiply = new MatrixChainMultiply();

    ASSERT_TRUE(matrixChainMultiply != nullptr);

    matrixChainMultiply->MatrixChainOrder(p, m, s);
    matrixChainMultiply->PrintOptimalParens(s, 0, p.size() - 2);

    std::cout << std::endl;
    std::cout << "MemorizedMatrixChain" << std::endl;
    std::cout << matrixChainMultiply->MemorizedMatrixChain(p) << std::endl;
//    matrixChainMultiply->PrintOptimalParens(s, 0, p.size() - 2);
}
