//
// Created by yijun on 6/15/16.
//

#ifndef CHAP4_FINDMAXIMUMSUBARRARY_H
#define CHAP4_FINDMAXIMUMSUBARRARY_H

typedef struct {
    int low;
    int high;
    int sum;
} param;

class FindMaximumSubarray {
public:
    param findMaximumSubarray(int A[], int low, int high);

private:
    param findMaxCrossingSubarray(int A[], int low, int mid, int high);
};

#endif //CHAP4_FINDMAXIMUMSUBARRARY_H
