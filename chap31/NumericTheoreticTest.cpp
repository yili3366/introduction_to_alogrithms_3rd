//
// Created by yijun on 9/26/16.
//

#include <gtest/gtest.h>
#include "NumericTheoretic.h"

TEST(NumericTheoretic, NumericTheoretic_MillerRabin_Test) {
    NumericTheoretic numericTheoretic;
    DXY dxy;
    int d;

    dxy = numericTheoretic.ExtendedEuclid(99, 78);
    std::cout << " d " << dxy.d << std::endl;
    std::cout << " x " << dxy.x << std::endl;
    std::cout << " y " << dxy.y << std::endl;

    d = numericTheoretic.ModularExponentation(7, 560, 561);
    std::cout << " d " << d << std::endl;

    if (numericTheoretic.MillerRabin(561, 7)) {
        std::cout << " prime " << std::endl;
    }
}