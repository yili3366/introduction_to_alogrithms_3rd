//
// Created by yijun on 6/19/16.
//

#include "CountingSort.h"

CountingSort::CountingSort(int length) {
    mLength = length;
}

void CountingSort::CountSort(int *A, int *B, int k) {
    int *C = new int[sizeof(int) * k];

    for (int i = 0; i < k; i++) {
        C[i] = 0;
    }

    for (int j = 0; j < mLength; j++) {
        C[A[j]] = C[A[j]] + 1;
    }

    for (int i = 1; i < k; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = mLength - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }

    delete [] C;
}