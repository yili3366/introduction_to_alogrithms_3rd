//
// Created by yijun on 6/19/16.
//

#ifndef CHAP7_QUICKSORT_H
#define CHAP7_QUICKSORT_H

#include <vector>

class QuickSort {
public:
    int Partition(std::vector<int> &vi, int low, int high);
    QuickSort(std::vector<int> &vi, int low, int high);
};

#endif //CHAP7_QUICKSORT_H
