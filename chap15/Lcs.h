//
// Created by yijun on 7/3/16.
//

#ifndef CHAP15_LCS_H
#define CHAP15_LCS_H

#include <vector>

enum Direction {
    kInit = 0,
    kUpLeft = 1,
    kUp = 2,
    kLeft = 3,
};

struct Info {
    std::vector<std::vector<int>> b;
    std::vector<std::vector<int>> c;
};

class LCS {
public:
    Info LCSLength(const std::string &x, const std::string &y);
    void PrintLCS(std::vector<std::vector<int>> &b, std::string x, int i, int j);
};

#endif //CHAP15_LCS_H
