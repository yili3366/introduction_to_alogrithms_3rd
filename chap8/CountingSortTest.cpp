//
// Created by yijun on 6/19/16.
//

#include <gtest/gtest.h>

#include "CountingSort.h"

TEST(CountingSortTest, CountingSort) {
    const int length = 11;
    int A[length] = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
    int B[length] = {-1,};

    CountingSort * countingSort = new CountingSort(length);
    ASSERT_TRUE(countingSort != nullptr);

    countingSort->CountSort(A, B, 100);

    for (int i = 0; i < length; i++) {
        std::cout << " " << B[i];
    }

    std::cout << std::endl;
}
