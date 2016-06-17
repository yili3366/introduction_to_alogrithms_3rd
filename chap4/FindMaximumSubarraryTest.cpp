//
// Created by yijun on 6/15/16.
//

#include <iostream>
#include <gtest/gtest.h>

#include "FindMaximumSubarrary.h"

TEST(FindMaximumSubarraryTest, findMaximumSubarrary) {

    int A[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    param paramInfo;

    // do some initialization
    FindMaximumSubarrary *findMaxSubarrary = new FindMaximumSubarrary();

    ASSERT_TRUE(findMaxSubarrary != nullptr);

    paramInfo = findMaxSubarrary->findMaximumSubarrary(A, 0, 15);

    std::cout << " low " << paramInfo.low
            << " high " << paramInfo.high
            << " sum " << paramInfo.sum
            << std::endl;

    delete(findMaxSubarrary);
}