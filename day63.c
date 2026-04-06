#include <stdlib.h>

// Structure for queue to perform BFS
typedef struct {
    int row;
    int col;
} Pixel;

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize, int** returnColumnSizes) {
    // Get the original color of the starting pixel
    int originalColor = image[sr][sc];
    
    // If the color is already the same, no need to do anything
    if (originalColor == color) {
        *returnSize = imageSize;
        *returnColumnSizes = imageColSize;
        return image;
    }
    
    // Get dimensions
    int rows = imageSize;
    int cols = imageColSize[0];
    
    // Create a queue for BFS (maximum size rows * cols)
    Pixel* queue = (Pixel*)malloc(sizeof(Pixel) * rows * cols);
    int front = 0, rear = 0;
    
    // Start from the initial pixel
    queue[rear].row = sr;
    queue[rear].col = sc;
    rear++;
    
    // Mark the starting pixel
    image[sr][sc] = color;
    
    // Directions: up, down, left, right
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // BFS loop
    while (front < rear) {
        Pixel current = queue[front];
        front++;
        
        // Check all 4 adjacent pixels
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dirs[i][0];
            int newCol = current.col + dirs[i][1];
            
            // Check if the new position is within bounds
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                // Check if the pixel has the original color
                if (image[newRow][newCol] == originalColor) {
                    // Change its color and add to queue
                    image[newRow][newCol] = color;
                    queue[rear].row = newRow;
                    queue[rear].col = newCol;
                    rear++;
                }
            }
        }
    }
    
    // Free the queue memory
    free(queue);
    
    // Set return values
    *returnSize = imageSize;
    *returnColumnSizes = imageColSize;
    
    return image;
}