#include <stdio.h>
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int top = 0;
    int bottom = matrixSize - 1;
    int left = 0;
    int right = matrixColSize[0] - 1;

    int total = matrixSize * matrixColSize[0];
    int *result = (int*)malloc(total * sizeof(int));
    int k = 0;

    while (top <= bottom && left <= right) {

        for (int i = left; i <= right; i++)
            result[k++] = matrix[top][i];
        top++;

        for (int i = top; i <= bottom; i++)
            result[k++] = matrix[i][right];
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                result[k++] = matrix[bottom][i];
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                result[k++] = matrix[i][left];
            left++;
        }
    }

    *returnSize = total;
    return result;
}
