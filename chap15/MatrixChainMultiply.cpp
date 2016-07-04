//
// Created by yijun on 7/1/16.
//

#include <iostream>
#include <limits>
#include "MatrixChainMultiply.h"

Info MatrixChainMultiply::MatrixChainOrder(std::vector<int> &p,
                                           std::vector<std::vector<int>> &m,
                                           std::vector<std::vector<int>> &s) {
    Info info = Info();

    int n = p.size() - 1;
    m.resize(n);

    for (int i = 0; i < n; i++) {
        m[i].resize(n);
    }

    s.resize(n);

    for (int i = 0; i < n; i++) {
        s[i].resize(n);
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = std::numeric_limits<int>::max();
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    info.SetM(m);
    info.SetS(s);

    return info;
}

void MatrixChainMultiply::PrintOptimalParens(const std::vector<std::vector<int>> &s, int i, int j) {
    if (i < j) {
        std::cout << "(";
        PrintOptimalParens(s, i, s[i][j]);
        PrintOptimalParens(s, s[i][j] + 1, j);
        std::cout << ")";
    } else {
        std::cout << "M[" << i << "]";
    }
}

int MatrixChainMultiply::MemorizedMatrixChain(std::vector<int> &p) {
    int n = p.size() - 1;

    std::vector<std::vector<int>> m;

    m.resize(n);

    for (int i = 0; i < n; i++) {
        m[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            m[i][j] = std::numeric_limits<int>::max();
        }
    }

    return LookupChain(m, p, 0, n);
}

int MatrixChainMultiply::LookupChain(std::vector<std::vector<int>> &m, std::vector<int> &p, int i, int j) {
    int q;

    if (m[i][j] < std::numeric_limits<int>::max()) {
        return m[i][j];
    }

    if (i == j) {
        m[i][j] = 0;
    } else {
        for (int k = i; k <= j - 1; k++) {
            q = LookupChain(m, p, i, k) + LookupChain(m, p, k + 1, j) + p[i - 1] * p[k] * p[j];
            if (q < m[i][j]) {
                m[i][j] = q;
            }
        }
    }

    return m[i][j];
}
