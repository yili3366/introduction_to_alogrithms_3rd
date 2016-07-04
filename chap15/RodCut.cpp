//
// Created by yijun on 6/30/16.
//

#include <algorithm>
#include <iostream>
#include "RodCut.h"

int RodCut::CutRod(int *p, int n) {
    int q;
    q = -1;

    if (n == 0) {
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        q = std::max(q, p[i] + CutRod(p, n - i));
    }

    return q;
}

int RodCut::MemorizedCutRod(int *p, int n) {
    int r[n];

    for (int i = 0; i <= n; i++) {
        r[i] = -1;
    }

    return MemorizedCutRodAux(p, n, r);
}

int RodCut::MemorizedCutRodAux(int *p, int n, int *r) {
    int q;

    if (r[n] >= 0) {
        return r[n];
    }

    if (n == 0) {
        q = 0;
    } else {
        q = -1;
        for (int i = 1; i <= n; i++) {
            q = std::max(q, p[i] + MemorizedCutRodAux(p, n - i, r));
        }
    }

    r[n] = q;

    return q;
}

int RodCut::BottomUpCutRod(int p[], int n) {
    int r[n];
    r[0] = 0;
    int q;

    for (int i = 0; i <= n; i++) {
        r[i] = 0;
    }

    for (int j = 0; j <= n; j++) {
        q = -1;

        for (int i = 0; i <= j; i++) {
            q = std::max(q, p[i] + r[j - i]);
        }
        r[j] = q;
    }

    return r[n];
}

std::vector<RodCutInfo> RodCut::ExtendedBottomUpCutRod(int *p, int n) {
    std::vector<RodCutInfo> rodInfo;
    rodInfo.resize(n);
    for (int i = 0; i < n; i++) {
        rodInfo[i].r = 0;
        rodInfo[i].s = 0;
    }
//    rodInfo[0].r = 0;

    for (int j = 1; j <= n; j++) {
        int q = -1;
        for (int i = 1; i <= j; i++) {
            if (q < p[i] + rodInfo[j - i].r) {
                q = p[i] + rodInfo[j - i].r;
                rodInfo[j].s = i;
            }
        }
        rodInfo[j].r = q;
    }

    return rodInfo;
}

void RodCut::PrintCutRodSolution(int p[], int n) {
    std::vector<RodCutInfo> rodInfo;

//    for (int i = 0; i < n; i++) {
        rodInfo = ExtendedBottomUpCutRod(p, n);
//        while (n > 0) {
//            std::cout << "s[" << n << "]" << rodInfo[n].s << std::endl;
//            std::cout << "r[" << n << "]" << rodInfo[n].r << std::endl;
//            n = n - rodInfo[n].s;
//        }
//    }
    for (int i = 0; i <= n; i++) {
            std::cout << "s[" << i << "]" << rodInfo[i].s << std::endl;
            std::cout << "r[" << i << "]" << rodInfo[i].r << std::endl;
    }

}
