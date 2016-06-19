//
// Created by yijun on 6/19/16.
//

#include <iostream>
#include <gtest/gtest.h>

#include "HeapSort.h"

TEST(HeapSortTest, HeapSort) {

    int A[9] = {5, 13, 2, 25, 7, 17, 20, 8, 4};

    HeapSort * heapSort = new HeapSort(A, 9);

    ASSERT_TRUE(heapSort != nullptr);

    for (int i = 0; i < 9; i++) {
        std::cout << " " << A[i];
    }

    std::cout << std::endl;

    delete heapSort;
}