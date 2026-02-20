#include <stdio.h>

int maxSubarraySumCircular(int* nums, int n) {
    int total = nums[0];
    int maxSum = nums[0], curMax = nums[0];
    int minSum = nums[0], curMin = nums[0];

    for(int i = 1; i < n; i++) {
        int x = nums[i];

        curMax = (curMax + x > x) ? curMax + x : x;
        maxSum = (maxSum > curMax) ? maxSum : curMax;

        curMin = (curMin + x < x) ? curMin + x : x;
        minSum = (minSum < curMin) ? minSum : curMin;

        total += x;
    }

    if(maxSum < 0)
        return maxSum;

    int circular = total - minSum;
    return (maxSum > circular) ? maxSum : circular;
}