#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    // Handle edge cases
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // First, count frequencies using a hash map approach
    // Since we can't use actual hash maps in C easily, we'll use a simple approach
    // Note: This assumes numbers are within a reasonable range
    // For LeetCode, we need a more robust solution
    
    // Create arrays to store unique numbers and their frequencies
    int* uniqueNums = (int*)malloc(numsSize * sizeof(int));
    int* frequencies = (int*)malloc(numsSize * sizeof(int));
    int uniqueCount = 0;
    
    // Count frequencies
    for (int i = 0; i < numsSize; i++) {
        int found = -1;
        for (int j = 0; j < uniqueCount; j++) {
            if (uniqueNums[j] == nums[i]) {
                found = j;
                break;
            }
        }
        
        if (found != -1) {
            frequencies[found]++;
        } else {
            uniqueNums[uniqueCount] = nums[i];
            frequencies[uniqueCount] = 1;
            uniqueCount++;
        }
    }
    
    // Create buckets where index = frequency
    // Since max frequency can be at most numsSize
    int** buckets = (int**)malloc((numsSize + 1) * sizeof(int*));
    int* bucketSizes = (int*)calloc(numsSize + 1, sizeof(int));
    
    // Initialize buckets
    for (int i = 0; i <= numsSize; i++) {
        buckets[i] = (int*)malloc(uniqueCount * sizeof(int));
    }
    
    // Fill buckets
    for (int i = 0; i < uniqueCount; i++) {
        int freq = frequencies[i];
        buckets[freq][bucketSizes[freq]++] = uniqueNums[i];
    }
    
    // Collect top k frequent elements
    int* result = (int*)malloc(k * sizeof(int));
    int resultIndex = 0;
    
    // Start from highest frequency
    for (int freq = numsSize; freq >= 0 && resultIndex < k; freq--) {
        for (int i = 0; i < bucketSizes[freq] && resultIndex < k; i++) {
            result[resultIndex++] = buckets[freq][i];
        }
    }
    
    *returnSize = resultIndex;
    
    // Clean up
    free(uniqueNums);
    free(frequencies);
    for (int i = 0; i <= numsSize; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
    
    return result;
}