//
// Created by yijun on 7/3/16.
//

#include "OptimalBinarySearchTree.h"

#include <limits>
#include <iostream>

Info::Info(int ne, int nroot, int nw) {
    e.resize(ne + 2);
    w.resize(nw + 2);
    root.resize(nroot + 2);

    for (int i = 0; i < ne + 2; i++) {
        e[i].resize(ne + 2);
    }

    for (int i = 0; i < nw + 2; i++) {
        w[i].resize(nw + 2);
    }

    for (int i = 0; i < nroot + 2; i++) {
        root[i].resize(nroot + 2);
    }
}

Info OptimalBinarySearchTree::OptimalBST(std::vector<double> &p, std::vector<double> &q, int n) {
    std::vector<std::vector<double>> e;
    std::vector<std::vector<double>> w;
    std::vector<std::vector<int>> root;
    Info info = Info(n, n, n);

    e.resize(n + 2);
    root.resize(n + 2);
    w.resize(n + 2);

    for (int i = 0; i < n + 2; i++) {
        e[i].resize(n + 2);
        root[i].resize(n + 2);
        w[i].resize(n + 2);
    }

    for (int i = 1; i < n + 2; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = std::numeric_limits<double>::max();
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }


    info.e = e;
    info.root = root;
    info.w = w;

    return info;
}

