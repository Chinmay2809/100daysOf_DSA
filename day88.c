#include <stdlib.h>

// Comparison function for qsort
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

// Helper function to check if we can place m balls with at least minForce distance apart
bool canPlace(int* position, int positionSize, int m, int minForce) {
    int count = 1;  // Place first ball at the first position
    int lastPos = position[0];
    
    for (int i = 1; i < positionSize; i++) {
        if (position[i] - lastPos >= minForce) {
            count++;
            lastPos = position[i];
            
            if (count >= m) {
                return true;  // Successfully placed all m balls
            }
        }
    }
    
    return count >= m;
}

int maxDistance(int* position, int positionSize, int m) {
    // Sort the positions first
    qsort(position, positionSize, sizeof(int), compare);
    
    // Binary search for the maximum minimum distance
    int left = 1;  // Minimum possible distance
    int right = position[positionSize - 1] - position[0];  // Maximum possible distance
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canPlace(position, positionSize, m, mid)) {
            // Can place all balls with at least 'mid' distance apart
            // Try to find a larger minimum distance
            result = mid;
            left = mid + 1;
        } else {
            // Cannot place with 'mid' distance, need smaller distance
            right = mid - 1;
        }
    }
    
    return result;
}