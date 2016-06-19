//
// Created by yijun on 6/19/16.
//

#ifndef CHAP6_HEAPSORT_H
#define CHAP6_HEAPSORT_H

class HeapSort {
public:
    void BuildMaxHeap(int A[]);
    void MaxHeapfiy(int A[], int i);
    HeapSort(int A[], int length);

private:
    inline int Parent(int i) {
        return (i >> 1);
    }

    inline int Left(int i) {
        return (i << 1);
    }

    inline int Right(int i) {
        return (i << 1) + 1;
    }

    inline void Swap (int &a, int &b) {
        int t;
        t = a;
        a = b;
        b = t;
    }

    int mHeapSize;
    int mLength;
};

#endif //CHAP6_HEAPSORT_H
