//
// Created by yijun on 6/20/16.
//

#include "BucketSort.h"

BucketSort::BucketSort(int length) {
    mLength = length;
}

void BucketSort::bucketSort(double *A) {

    const int bucketSize = 10;
    Node B[bucketSize];
    int number = 0;
    Node *p;
    Node *q;
    int counter = 0;

    // make B[i] an empty list
    for (int i = 0; i < bucketSize; i++) {
        B[i].value = 0;
        B[i].next = nullptr;
    }

    for (int i = 0; i < mLength; i++) {
        Node *insert = new Node();
        insert->value = A[i];
        insert->next = nullptr;
        number = A[i] * bucketSize;

        if (B[number].next == nullptr) {
            B[number].next = insert;
        } else {
            p = &B[number];
            q = B[number].next;
            while ((q != nullptr) && (q->value <= A[i])) {
                q = q->next;
                p = p->next;
            }
            insert->next = q;
            p->next = insert;
        }
    }

    //contatenate the lists B[i] together
    for (int i = 0; i < bucketSize; i++) {
        p = B[i].next;

        if (p == nullptr) {
            continue;
        }

        while (p != nullptr) {
            A[counter++] = p->value;
            p = p->next;
        }
    }
}
