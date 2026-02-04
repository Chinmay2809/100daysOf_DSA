#include <stdio.h>

long long missingNum(int arr[], int size) {
    long long n = size + 1;
    long long expected_sum = n * (n + 1) / 2;
    long long actual_sum = 0;

    for (int i = 0; i < size; i++) {
        actual_sum += arr[i];
    }

    return expected_sum - actual_sum;
}