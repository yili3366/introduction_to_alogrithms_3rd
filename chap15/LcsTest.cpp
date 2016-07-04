//
// Created by yijun on 7/3/16.
//

#include <gtest/gtest.h>
#include "Lcs.h"

TEST(LCSTest, LCS) {

    std::string x = "ABCBDAB";
    std::string y = "BDCABA";

    LCS *lcs = new LCS();
//    Info *info = new Info();
    Info info = Info();

    ASSERT_TRUE(lcs != nullptr);

    info = lcs->LCSLength(x, y);
    for (int i = 0; i < x.length()+1; i++) {
        for (int j = 0; j < y.length()+1; j++) {
            if (j != 0) {
                std::cout << " ";
            }
            std::cout << info.c[i][j];
        }
        std::cout << std::endl;
    }

    lcs->PrintLCS(info.b, x, x.length(), y.length());
}
