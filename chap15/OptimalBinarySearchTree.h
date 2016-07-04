//
// Created by yijun on 7/3/16.
//

#ifndef CHAP15_OPTIMALBINARYSEARCHTREE_H
#define CHAP15_OPTIMALBINARYSEARCHTREE_H

#include <vector>

struct Info {
public:
    Info(int ne, int nroot, int nw);
    std::vector<std::vector<double >> e;
    std::vector<std::vector<double >> w;
    std::vector<std::vector<int>> root;
};

class OptimalBinarySearchTree {
public:
    Info OptimalBST(std::vector<double> &p, std::vector<double> &q, int n);
};

#endif //CHAP15_OPTIMALBINARYSEARCHTREE_H
