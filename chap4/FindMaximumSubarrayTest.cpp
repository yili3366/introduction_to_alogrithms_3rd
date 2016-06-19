//
// Created by yijun on 6/15/16.
//

#include <iostream>
#include <gtest/gtest.h>

#include "FindMaximumSubarray.h"

TEST(FindMaximumSubarrayTest, findMaximumSubarray) {

    int A[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    param paramInfo;

    // do some initialization
    FindMaximumSubarray *findMaxSubarrary = new FindMaximumSubarray();

    ASSERT_TRUE(findMaxSubarrary != nullptr);

    paramInfo = findMaxSubarrary->findMaximumSubarray(A, 0, 15);

    std::cout << " low " << paramInfo.low
            << " high " << paramInfo.high
            << " sum " << paramInfo.sum
            << std::endl;

    delete(findMaxSubarrary);
}
