//
// Created by yijun on 6/19/16.
//

#include "PriorityQueue.h"
#include <iostream>


PriorityQueue::PriorityQueue(int heapSize) {
    //mHeapSize = heapSize;
    mHeapSize = 0;
}

int PriorityQueue::HeapExtractMax(int A[]) {
    int max = A[0];

    if (mHeapSize  < 1) {
        std::cout << " heap underflow " << std::endl;
        return kHeapUnderflow;
    }

    A[0] = A[mHeapSize - 1];
    mHeapSize--;
    MaxHeapfiy(A, 0);
    return max;
}

void PriorityQueue::MaxHeapfiy(int *A, int i) {
    int l = Left(i);
    int r = Right(i);
    int largest = 0;

    if (l < mHeapSize && A[l] > A[i]) {
        largest = l;
    } else {
        largest = i;
    }

    if (r < mHeapSize && A[r] > A[largest]) {
        largest = r;
    }

    if (largest != i) {
        Swap(A[i], A[largest]);
        MaxHeapfiy(A, largest);
    }
}

void PriorityQueue::HeapIncreaseKey(int *A, int i, int key) {
    if (key < A[i]) {
        std::cout << " new key is smaller than current key" << std::endl;
        return;
        //return kNewKeySmallerThanCurrentKey;
    }

    A[i] = key;
    while (i > 0 && A[Parent(i)] < A[i]) {
        Swap(A[i], A[Parent(i)]);
        i = Parent(i);
    }
}

void PriorityQueue::MaxHeapInsert(int *A, int key) {
    mHeapSize++;
    A[mHeapSize - 1] = -1;
    HeapIncreaseKey(A, mHeapSize - 1, key);
}