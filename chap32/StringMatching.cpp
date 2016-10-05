//
// Created by yijun on 10/4/16.
//

#include <cmath>
#include <map>
#include "StringMatching.h"

void StringMatching::RabinKarpMatcher(std::string T, std::string P, int d, int q) {
    int n;
    int m;
    int h;

    n = T.length();
    m = P.length();
    h = static_cast<int>(std::pow(d, m - 1)) % q;
    int p = 0;
    int t = 0;

    std::cout << " m " << m << std::endl;

    for (int i = 0; i < m; i++) {
        p = (d * p + P.at(i)) % q;
        t = (d * t + T.at(i)) % q;
    }


    for (int s = 0; s <= n - m; s++) {
        std::cout << " t " << t << std::endl;
        if (p == t) {
//            std::cout << " P.substr(0, m - 1) " << P.substr(0, m - 1) << std::endl;
//            std::cout << " T.substr(s, s + m - 1) " << T.substr(0, s + m - 1) << std::endl;
            if (P.substr(0, m).compare(T.substr(s, m)) == 0) {
                std::cout << "P.substr(0, m - 1)" << P.substr(0, m) << std::endl;
                std::cout << "T.substr(s, s + m - 1)" << T.substr(s, m) << std::endl;
                std::cout << "Pattern occurs with shift " << s << std::endl;
            }
        }

        if (s < n - m) {
            t = (d * (t - T.at(s) * h) + T.at(s + m)) % q;
        }

        if (t < 0) {
            t = t + q;
        }
    }
}

void StringMatching::KMPMatcher(std::string T, std::string P) {
    int n;
    int m;
    std::map<int, int> Pi;

    n = T.length();
    m = P.length();
    Pi = ComputePrefixFunction(P);
    int q = 0;

    for (int i = 0; i < n; i++) {
        while (q > 0 && P.at(q) != T.at(i)) {
            q = Pi.at(q);
        }

        if (P.at(q) == T.at(i)) {
            q = q + 1;
        }

        if (q == m) {
            std::cout << " Pattern occurs with shift " << i - m + 2 << std::endl;
            q = Pi.at(q);
        }
    }
}

std::map<int, int> StringMatching::ComputePrefixFunction(std::string P) {
    int m = P.length();
    std::map<int, int> Pi;
    int k = 0;
    int q;

    Pi.insert(std::make_pair(1, 0));

    for (q = 1; q < m; q++) {
        while (k > 0 && P.at(k) != P.at(q)) {
            k = Pi.at(k);
        }
        if (P.at(k) == P.at(q)) {
            k = k + 1;
        }
        Pi.insert(std::make_pair(q + 1, k));
    }

#if 0
    for (std::map<int, int>::iterator iter = Pi.begin(); iter != Pi.end(); iter++) {
        std::cout << "  " << iter->first << "  " << iter->second << "  ";
    }
    std::cout << std::endl;
#endif

    return Pi;
}
