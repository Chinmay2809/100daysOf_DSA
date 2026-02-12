#include <stdio.h>
#include <stdlib.h>

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    
    int count[1001] = {0};  

    for (int i = 0; i < nums1Size; i++) {
        count[nums1[i]]++;
    }

    int *result = (int*)malloc(sizeof(int) * (nums1Size < nums2Size ? nums1Size : nums2Size));
    int k = 0;

    for (int i = 0; i < nums2Size; i++) {
        if (count[nums2[i]] > 0) {
            result[k++] = nums2[i];
            count[nums2[i]]--;
        }
    }

    *returnSize = k;
    return result;
}
