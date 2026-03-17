#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    // Handle edge case
    if (temperaturesSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // Allocate result array
    int* result = (int*)malloc(temperaturesSize * sizeof(int));
    *returnSize = temperaturesSize;
    
    // Initialize all results to 0
    for (int i = 0; i < temperaturesSize; i++) {
        result[i] = 0;
    }
    
    // Stack to store indices (monotonic decreasing stack)
    int* stack = (int*)malloc(temperaturesSize * sizeof(int));
    int top = -1;
    
    // Iterate through temperatures
    for (int i = 0; i < temperaturesSize; i++) {
        // While stack is not empty and current temperature is warmer than
        // the temperature at the index stored at top of stack
        while (top >= 0 && temperatures[i] > temperatures[stack[top]]) {
            int prevIndex = stack[top--];
            result[prevIndex] = i - prevIndex;
        }
        
        // Push current index to stack
        stack[++top] = i;
    }
    
    // Free stack memory
    free(stack);
    
    return result;
}