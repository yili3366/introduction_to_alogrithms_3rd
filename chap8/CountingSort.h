//
// Created by yijun on 6/19/16.
//

#ifndef CHAP8_COUNTINGSORT_H
#define CHAP8_COUNTINGSORT_H

class CountingSort {
public:
    CountingSort(int length);
    void CountSort(int *A, int *B, int k);
private:
    int mLength;
};

#endif //CHAP8_COUNTINGSORT_H
