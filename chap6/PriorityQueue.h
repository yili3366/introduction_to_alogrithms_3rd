//
// Created by yijun on 6/19/16.
//

#ifndef CHAP6_PRIORITYQUEUE_H
#define CHAP6_PRIORITYQUEUE_H

enum ERROR {
    kSuccess = 0,
    kHeapUnderflow,
};

class PriorityQueue {
public:
    PriorityQueue(int heapSize);

    void MaxHeapInsert(int A[], int key);

    int HeapExtractMax(int A[]);

    void HeapIncreaseKey(int A[], int i, int key);

    void MaxHeapfiy(int A[], int i);

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

    inline void Swap(int &a, int &b) {
        int t;
        t = a;
        a = b;
        b = t;
    }

    int mHeapSize;
};

#endif //CHAP6_PRIORITYQUEUE_H
