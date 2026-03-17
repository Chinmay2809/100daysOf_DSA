#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int leastInterval(char* tasks, int tasksSize, int n) {
    // Count frequency of each task (A-Z)
    int freq[26] = {0};
    for (int i = 0; i < tasksSize; i++) {
        freq[tasks[i] - 'A']++;
    }
    
    // Find maximum frequency
    int maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }
    
    // Count how many tasks have the maximum frequency
    int maxCount = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == maxFreq) {
            maxCount++;
        }
    }
    
    // Calculate result using formula
    // (maxFreq - 1) * (n + 1) + maxCount
    int result = (maxFreq - 1) * (n + 1) + maxCount;
    
    // Result cannot be less than total number of tasks
    return (result > tasksSize) ? result : tasksSize;
}