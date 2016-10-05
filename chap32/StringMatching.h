//
// Created by yijun on 10/4/16.
//

#ifndef CHAP32_STRINGMATCHING_H
#define CHAP32_STRINGMATCHING_H

#include <iostream>
#include <string>
#include <vector>

class StringMatching {
public:
    void RabinKarpMatcher(std::string T, std::string P, int d, int q);
//    void FiniteAutomationMatcher(std::string T, int m);
    void KMPMatcher(std::string T, std::string P);
private:
    std::map<int, int> ComputePrefixFunction(std::string P);
};

#endif //CHAP32_STRINGMATCHING_H
