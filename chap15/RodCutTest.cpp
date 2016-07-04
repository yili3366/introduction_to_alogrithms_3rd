//
// Created by yijun on 7/1/16.
//

#include <iostream>
#include <gtest/gtest.h>

#include "RodCut.h"

TEST(RodCutTest, RodCut) {
    const int size = 11;
    RodCut *rodCut = new RodCut();
    int p[size] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    ASSERT_TRUE(rodCut != nullptr);

    rodCut->PrintCutRodSolution(p, size - 1);

    std::cout << "MemorizedCutRod" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << rodCut->MemorizedCutRod(p, i) << std::endl;
    }

    std::cout << "BottomUpCutRod" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << rodCut->BottomUpCutRod(p, i) << std::endl;
    }

    std::cout << "CutRod" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << rodCut->CutRod(p, i) << std::endl;
    }
}
