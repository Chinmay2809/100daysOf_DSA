int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        // Check which half is properly sorted
        if (nums[left] <= nums[mid]) {
            // Left half is sorted
            if (target >= nums[left] && target < nums[mid]) {
                // Target is in left sorted half
                right = mid - 1;
            } else {
                // Target is in right half
                left = mid + 1;
            }
        } else {
            // Right half is sorted
            if (target > nums[mid] && target <= nums[right]) {
                // Target is in right sorted half
                left = mid + 1;
            } else {
                // Target is in left half
                right = mid - 1;
            }
        }
    }
    
    return -1;
}