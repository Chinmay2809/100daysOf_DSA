int findPeakElement(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Compare mid with its next element
        if (nums[mid] < nums[mid + 1]) {
            // Peak is on the right side
            left = mid + 1;
        } else {
            // Peak is on the left side (including mid)
            right = mid;
        }
    }
    
    return left;
}