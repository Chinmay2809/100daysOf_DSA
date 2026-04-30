#include <stdbool.h>

// Helper function to check if we can ship all packages within given days with capacity 'cap'
bool canShip(int* weights, int weightsSize, int days, int cap) {
    int daysNeeded = 1;  // Start with day 1
    int currentLoad = 0;
    
    for (int i = 0; i < weightsSize; i++) {
        // If a single package exceeds capacity, impossible
        if (weights[i] > cap) {
            return false;
        }
        
        // If adding this package exceeds capacity, start a new day
        if (currentLoad + weights[i] > cap) {
            daysNeeded++;
            currentLoad = weights[i];
            
            // Early exit if we already exceed available days
            if (daysNeeded > days) {
                return false;
            }
        } else {
            currentLoad += weights[i];
        }
    }
    
    return daysNeeded <= days;
}

int shipWithinDays(int* weights, int weightsSize, int days) {
    // Find the lower and upper bounds for binary search
    int left = 0;  // Minimum capacity is the max single package weight
    int right = 0; // Maximum capacity is the sum of all weights
    
    for (int i = 0; i < weightsSize; i++) {
        if (weights[i] > left) {
            left = weights[i];  // Max individual weight
        }
        right += weights[i];    // Total sum of all weights
    }
    
    // Binary search for the minimum valid capacity
    int result = right;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canShip(weights, weightsSize, days, mid)) {
            // Can ship within days with capacity 'mid', try smaller capacity
            result = mid;
            right = mid - 1;
        } else {
            // Cannot ship within days, need larger capacity
            left = mid + 1;
        }
    }
    
    return result;
}