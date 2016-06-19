//
// Created by yijun on 6/19/16.
//

#include <iostream>
#include <gtest/gtest.h>

#include "PriorityQueue.h"

TEST(PriorityQueueTest, PriorityQueue) {
    const int size = 9;
    //int A[size] = {5, 13, 2, 25, 7, 17, 20, 8, 4};
    int A[size] = {0,};
    int max;
    int key;

    PriorityQueue *priorityQueue = new PriorityQueue(size);
    ASSERT_TRUE(priorityQueue != nullptr);

    for (int i = 0; i < size; i++) {
        key = rand() % 77;
        std::cout << " " << key  << " ";

        priorityQueue->MaxHeapInsert(A, key);
    }
    std::cout << std::endl;

    std::cout << " max is: ";
    for (int i = 0; i < size; i++) {
        max = priorityQueue->HeapExtractMax(A);
        std::cout << " " << max << " ";
    }
    std::cout << std::endl;
}
