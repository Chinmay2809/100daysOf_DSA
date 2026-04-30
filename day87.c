#include <stdbool.h>

// Helper function to check if Koko can finish all bananas with speed k within h hours
bool canFinish(int* piles, int pilesSize, int h, int k) {
    int hoursNeeded = 0;
    for (int i = 0; i < pilesSize; i++) {
        // Calculate hours needed for this pile: ceil(piles[i] / k)
        hoursNeeded += (piles[i] + k - 1) / k;
        
        // Early exit if we already exceed h hours
        if (hoursNeeded > h) {
            return false;
        }
    }
    return hoursNeeded <= h;
}

int minEatingSpeed(int* piles, int pilesSize, int h) {
    // Find the maximum pile size (the upper bound for binary search)
    int maxPile = 0;
    for (int i = 0; i < pilesSize; i++) {
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }
    
    // Binary search for the minimum valid eating speed
    int left = 1;
    int right = maxPile;
    int result = maxPile;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canFinish(piles, pilesSize, h, mid)) {
            // Can finish with speed mid, try a smaller speed
            result = mid;
            right = mid - 1;
        } else {
            // Cannot finish with speed mid, need larger speed
            left = mid + 1;
        }
    }
    
    return result;
}