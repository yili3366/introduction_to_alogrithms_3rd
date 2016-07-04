//
// Created by yijun on 7/3/16.
//


#include <iostream>
#include "Lcs.h"

Info LCS::LCSLength(const std::string &x, const std::string &y) {
    int m;
    int n;
    Info info = Info();

//    if (x.size() == 0 || y.size() == 0) {
//        return 0;
//    }

    m = x.length();
    n = y.length();

    std::vector<std::vector<int>> b;
    std::vector<std::vector<int>> c;
    std::vector<std::vector<int>>::iterator iterB;
    std::vector<std::vector<int>>::iterator iterC;

    b.resize(m + 1);
    for (iterB = b.begin(); iterB != b.end(); iterB++) {
        (*iterB).resize(n + 1);
    }

    c.resize(m + 1);
    for (iterC = c.begin(); iterC != c.end(); iterC++) {
        (*iterC).resize(n + 1);
    }

    for (int i = 0; i <= m; i++) {
        c[i][0] = 0;
    }

    for (int j = 0; j <= n; j++) {
        c[0][j] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = kUpLeft;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = kUp;
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = kLeft;
            }
        }
    }

    info.b = b;
    info.c = c;

    return info;
}
void LCS::PrintLCS(std::vector<std::vector<int>> &b, std::string x, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }

    if (b[i][j] == kUpLeft) {
        PrintLCS(b, x, i - 1, j - 1);
        std::cout << x[i - 1] << std::endl;
    } else if (b[i][j] == kUp) {
        PrintLCS(b, x, i - 1, j);
    } else {
        PrintLCS(b, x, i, j - 1);
    }
}
