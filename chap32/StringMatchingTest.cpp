//
// Created by yijun on 10/4/16.
//

#include <gtest/gtest.h>
#include "StringMatching.h"

TEST(StringMatching, StringMatching_RabinKarp_Test) {
    StringMatching stringMatching;
    std::string T{"2359023141526739921"};
    std::string P{"31415"};
    int d = 10;
    int q = 13;

    stringMatching.RabinKarpMatcher(T, P, d, q);
}

TEST(StringMatching, StringMatching_KMPMatcher_Test) {
    StringMatching stringMatching;
    std::string T1{"bacbababaabcbab"};
    std::string T2{"abababacaba"};
    std::string P{"ababaca"};

    std::cout << " test t1 bacbababaabcbab " << std::endl;
    stringMatching.KMPMatcher(T1, P);

    std::cout << " test t2 ababaca " << std::endl;
    stringMatching.KMPMatcher(T2, P);
}
