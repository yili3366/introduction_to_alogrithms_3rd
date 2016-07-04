//
// Created by yijun on 7/4/16.
//

#include <gtest/gtest.h>

#include "OptimalBinarySearchTree.h"

TEST(OptimalBinarySearchTreeTest, OptimalBinarySearchTree) {
    OptimalBinarySearchTree *optimalBinarySearchTree = new OptimalBinarySearchTree();
    const int size = 6;
    double p[size] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
    double q[size] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    Info info = Info(size, size, size);

    std::vector<double> Pi(p, p + sizeof(p) / sizeof(double));
    std::vector<double> Qi(q, q + sizeof(q) / sizeof(double));

    ASSERT_TRUE(optimalBinarySearchTree != nullptr);

    info = optimalBinarySearchTree->OptimalBST(Pi, Qi, size);

    std::cout << " e " << std::endl;
    for (int i = 1; i < size + 1; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << " " << info.e[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << " root " << std::endl;
    for (int i = 1; i < size + 1; i++) {
        for (int j = 1; j < size; j++) {
            std::cout << " " << info.root[i][j];
        }
        std::cout << std::endl;
    }

   std::cout << " w " << std::endl;
    for (int i = 1; i < size + 1; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << " " << info.w[i][j];
        }
        std::cout << std::endl;
    }
}



