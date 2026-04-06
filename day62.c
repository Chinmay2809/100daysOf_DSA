#include <stdbool.h>
#include <stdlib.h>

bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize) {
    // Array to track visited rooms
    bool* visited = (bool*)calloc(roomsSize, sizeof(bool));
    
    // Stack for DFS (or queue for BFS)
    int* stack = (int*)malloc(roomsSize * sizeof(int));
    int top = -1;
    
    // Start from room 0
    visited[0] = true;
    stack[++top] = 0;
    
    // DFS traversal
    while (top >= 0) {
        int currentRoom = stack[top--];
        
        // Get all keys from current room
        for (int i = 0; i < roomsColSize[currentRoom]; i++) {
            int key = rooms[currentRoom][i];
            
            // If the room corresponding to this key hasn't been visited
            if (!visited[key]) {
                visited[key] = true;
                stack[++top] = key;
            }
        }
    }
    
    // Check if all rooms are visited
    bool result = true;
    for (int i = 0; i < roomsSize; i++) {
        if (!visited[i]) {
            result = false;
            break;
        }
    }
    
    // Free allocated memory
    free(visited);
    free(stack);
    
    return result;
}