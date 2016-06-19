//
// Created by yijun on 6/19/16.
//

#include "HeapSort.h"

void HeapSort::BuildMaxHeap(int *A) {
    mHeapSize = mLength;

    for (int i = mLength / 2 - 1; i >= 0; i--) {
        MaxHeapfiy(A, i);
    }
}

void HeapSort::MaxHeapfiy(int *A, int i) {
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

HeapSort::HeapSort(int *A, int heapLength) {
    mLength = heapLength;
    BuildMaxHeap(A);

    for (int i = heapLength - 1; i >= 1; i--) {
        Swap(A[0], A[i]);
        mHeapSize--;
        MaxHeapfiy(A, 0);
    }
}
