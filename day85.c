int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // If middle element is greater than rightmost element,
        // the minimum is in the right half
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } 
        // Otherwise, the minimum is in the left half (including mid)
        else {
            right = mid;
        }
    }
    
    return nums[left];
}