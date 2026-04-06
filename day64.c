#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // Adjust as needed, or use dynamic allocation for larger grids

typedef struct {
    int x;
    int y;
    int time;
} QueueNode;

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    
    // Directions: up, down, left, right
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // Queue for BFS
    QueueNode queue[m * n];
    int front = 0, rear = 0;
    
    int freshCount = 0;
    int minutes = 0;
    
    // Initialize: enqueue all initially rotten oranges
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                queue[rear].x = i;
                queue[rear].y = j;
                queue[rear].time = 0;
                rear++;
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }
    
    // If no fresh oranges initially, return 0
    if (freshCount == 0) return 0;
    
    // BFS
    while (front < rear) {
        QueueNode curr = queue[front];
        front++;
        
        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dirs[i][0];
            int newY = curr.y + dirs[i][1];
            
            // Check bounds and if neighbor is fresh
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] == 1) {
                grid[newX][newY] = 2;  // Mark as rotten
                freshCount--;
                
                queue[rear].x = newX;
                queue[rear].y = newY;
                queue[rear].time = curr.time + 1;
                rear++;
                
                minutes = queue[rear - 1].time; // Update minutes
            }
        }
    }
    
    // If fresh oranges remain, return -1
    return (freshCount == 0) ? minutes : -1;
}