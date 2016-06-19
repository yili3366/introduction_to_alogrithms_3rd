#include "FindMaximumSubarray.h"

#include <iostream>

param FindMaximumSubarray::findMaxCrossingSubarray(int A[], int low, int mid, int high)
{

    int i;
    param param;
    int sum = 0;
    int leftSum = A[mid] - 1;
    int maxLeft;
    int maxRight;
    int rightSum;

    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    sum = 0;
    rightSum = A[mid + 1] - 1;

    for (int j = mid + 1; j <= high; j++) {
        sum += A[j];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = j;
        }
    }

    param.low = maxLeft;
    param.high = maxRight;
    param.sum = leftSum + rightSum;

    return param;
}

param FindMaximumSubarray::findMaximumSubarray(int A[], int low, int high)
{
    int mid;
    param leftSum;
    param rightSum;
    param crossSum;
    param param;

    if (low == high) {
        param.low = low;
        param.high = high;
        param.sum = A[low];
        return param;
    } else {
        mid = (low + high) / 2;
        leftSum = findMaximumSubarray(A, low, mid);
        rightSum = findMaximumSubarray(A, mid + 1, high);
        crossSum = findMaxCrossingSubarray(A, low, mid, high);

        if (leftSum.sum >= rightSum.sum && leftSum.sum >= crossSum.sum) {
            return leftSum;
        } else if (rightSum.sum >= leftSum.sum && rightSum.sum >= crossSum.sum) {
            return rightSum;
        } else {
            return crossSum;
        }
    }
}
