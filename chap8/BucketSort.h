//
// Created by yijun on 6/20/16.
//

#ifndef CHAP8_BUCKETSORT_H
#define CHAP8_BUCKETSORT_H

#include <list>

struct Node {
    double value;
    Node *next;
};

class BucketSort {
public:
    BucketSort(int length);
    void bucketSort(double *A);
private:
    int mLength;
};

#endif //CHAP8_BUCKETSORT_H
