int mySqrt(int x) {
    if (x == 0 || x == 1) {
        return x;
    }
    
    int left = 1;
    int right = x;
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Use division to avoid overflow when multiplying mid * mid
        if (mid <= x / mid) {
            result = mid;  // mid is a candidate answer
            left = mid + 1; // Try to find a larger valid square root
        } else {
            right = mid - 1; // mid is too large, search left half
        }
    }
    
    return result;
}