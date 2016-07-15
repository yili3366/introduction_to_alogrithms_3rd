//
// Created by yijun on 7/10/16.
//

#include <gtest/gtest.h>
#include "FibHeap.h"

TEST(FibHeapTest, FibHeap) {
    FibHeap<int> *fibHeap1 = new FibHeap<int>();
    FibHeap<int> *fibHeap2 = new FibHeap<int>();
    FibHeap<int> *fibHeap3 = new FibHeap<int>();
    int array1[] = {23, 7, 3, 17, 24, 18, 52, 38, 30, 26, 46, 39, 41, 35};
    int array2[] = {25, 8, 4, 19, 26, 20, 54, 40, 32, 28, 48, 42, 45, 37};
    std::vector<int> vec1(array1, array1 + sizeof(array1) / sizeof(int));
    std::vector<int> vec2(array2, array2 + sizeof(array2) / sizeof(int));
    std::vector<int>::iterator iter;

    ASSERT_TRUE(fibHeap1 != nullptr);
    ASSERT_TRUE(fibHeap2 != nullptr);

    for (iter = vec1.begin(); iter != vec1.end(); iter++) {
        FibHeapNode<int> *fibHeap1Node = new FibHeapNode<int>(*iter);
        fibHeap1->FibHeapInsert(fibHeap1, fibHeap1Node);
    }

    for (iter = vec2.begin(); iter != vec2.end(); iter++) {
        FibHeapNode<int> *fibHeap2Node = new FibHeapNode<int>(*iter);
        fibHeap2->FibHeapInsert(fibHeap2, fibHeap2Node);
    }

    FibHeapNode<int> *fibHeap1Node1 = fibHeap1->FibHeapSearch(fibHeap1, 3);
    FibHeapNode<int> *fibHeap1Node2 = fibHeap1->FibHeapSearch(fibHeap1, 35);
    FibHeapNode<int> *fibHeap1Node3 = fibHeap1->FibHeapSearch(fibHeap1, 41);

    if (fibHeap1Node1 != nullptr) {
        fibHeap1->FibHeapDelete(fibHeap1, fibHeap1Node1);
    }

    std::cout << " after delete 3 " << std::endl;
    fibHeap1->FibheapPrint(fibHeap1);

    if (fibHeap1Node2 != nullptr) {
        fibHeap1->FibHeapDelete(fibHeap1, fibHeap1Node2);
    }

    std::cout << " after delete 35 " << std::endl;
    fibHeap1->FibheapPrint(fibHeap1);

    if (fibHeap1Node3 != nullptr) {
        fibHeap1->FibHeapDelete(fibHeap1, fibHeap1Node3);
    }

    std::cout << " after delete 41 " << std::endl;
    fibHeap1->FibheapPrint(fibHeap1);


    fibHeap2->FibHeapExtractMin(fibHeap2);
    std::cout << " fibheap2 after extractmin " << std::endl;
    fibHeap2->FibheapPrint(fibHeap2);

    fibHeap3 = fibHeap3->FibHeapUnion(fibHeap2, fibHeap1);

    fibHeap3->FibheapPrint(fibHeap3);
}
