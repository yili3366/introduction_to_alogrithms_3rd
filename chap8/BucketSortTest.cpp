//
// Created by yijun on 6/20/16.
//

#include <gtest/gtest.h>

#include "BucketSort.h"

TEST(BucketSortTest, BucketSort) {
    const int length = 10;
    double A[length] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    BucketSort* bucketSort = new BucketSort(10);
    ASSERT_TRUE(bucketSort != nullptr);

    bucketSort->bucketSort(A);

    for (int i = 0; i < length; i++) {
        std::cout << " " << A[i];
    }

    std::cout << std::endl;
}