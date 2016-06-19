//
// Created by yijun on 6/19/16.
//

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "QuickSort.h"

TEST(QuickSortTest, QuickSort) {
    int A[11] = {3, 5, 7, 9, 2, 3, 1, 0, 7, 5, 4};

    std::vector<int> va(A, A + 11);
    std::vector<int>::iterator iter;

    QuickSort* quickSort = new QuickSort(va, 0, va.size() - 1);
    ASSERT_TRUE(quickSort != nullptr);

    for (iter = va.begin(); iter != va.end(); iter++) {
        std::cout << " " << (*iter);
    }
    std::cout << std::endl;

    delete quickSort;
}