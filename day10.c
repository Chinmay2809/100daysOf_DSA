#include <stdlib.h>

int** transpose(int** matrix, int matrixSize, int* matrixColSize,
                int* returnSize, int** returnColumnSizes) {

    int rows = matrixSize;
    int cols = matrixColSize[0];

    // Allocate result matrix
    int** result = (int**)malloc(cols * sizeof(int*));
    *returnColumnSizes = (int*)malloc(cols * sizeof(int));

    for (int i = 0; i < cols; i++) {
        result[i] = (int*)malloc(rows * sizeof(int));
        (*returnColumnSizes)[i] = rows;
    }

    // Transpose logic
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    *returnSize = cols;
    return result;
}
