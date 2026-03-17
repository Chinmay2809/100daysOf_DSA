#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // Result array
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    
    // Deque to store indices (implemented as an array)
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int front = 0, rear = -1;
    
    for (int i = 0; i < numsSize; i++) {
        // Remove indices that are out of current window
        if (front <= rear && deque[front] < i - k + 1) {
            front++;
        }
        
        // Remove indices whose corresponding values are less than nums[i]
        while (front <= rear && nums[deque[rear]] < nums[i]) {
            rear--;
        }
        
        // Add current index to deque
        deque[++rear] = i;
        
        // The first window is complete, start recording results
        if (i >= k - 1) {
            result[i - k + 1] = nums[deque[front]];
        }
    }
    
    free(deque);
    return result;
}