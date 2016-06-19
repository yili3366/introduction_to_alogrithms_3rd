//
// Created by yijun on 6/19/16.
//

#include "QuickSort.h"

int QuickSort::Partition(std::vector<int> &vi, int low, int high) {
    int pivot;
    int i;

    pivot = vi[high];
    i = low - 1;

    for (int j = low; j < high; j++) {
        if (vi[j] <= pivot) {
            i++;
            std::swap(vi[i], vi[j]);
        }
    }

    std::swap(vi[i + 1], vi[high]);
    return i + 1;
}

QuickSort::QuickSort(std::vector<int> &vi, int low, int high) {
    if (low < high) {
        int mid = Partition(vi, low, high);
        QuickSort(vi, low, mid - 1);
        QuickSort(vi, mid + 1, high);
    }
}