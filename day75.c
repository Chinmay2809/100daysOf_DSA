#include <stdbool.h>
#include <stdlib.h>

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* color = (int*)malloc(graphSize * sizeof(int));
    
    // Initialize all nodes as uncolored
    for (int i = 0; i < graphSize; i++) {
        color[i] = -1;
    }

    // Traverse all nodes (handle disconnected graph)
    for (int i = 0; i < graphSize; i++) {
        if (color[i] == -1) {
            // BFS queue
            int* queue = (int*)malloc(graphSize * sizeof(int));
            int front = 0, rear = 0;

            queue[rear++] = i;
            color[i] = 0;  // Start coloring

            while (front < rear) {
                int node = queue[front++];

                for (int j = 0; j < graphColSize[node]; j++) {
                    int neighbor = graph[node][j];

                    // If not colored, color with opposite color
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        queue[rear++] = neighbor;
                    }
                    // If same color, not bipartite
                    else if (color[neighbor] == color[node]) {
                        free(queue);
                        free(color);
                        return false;
                    }
                }
            }
            free(queue);
        }
    }

    free(color);
    return true;
}