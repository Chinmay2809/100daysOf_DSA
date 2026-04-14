#include <stdlib.h>

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
    
    int *indegree = (int *)calloc(numCourses, sizeof(int));
    int **graph = (int **)malloc(numCourses * sizeof(int *));
    int *graphSize = (int *)calloc(numCourses, sizeof(int));

    for (int i = 0; i < numCourses; i++) {
        graph[i] = (int *)malloc(numCourses * sizeof(int));
    }

    // Build graph
    for (int i = 0; i < prerequisitesSize; i++) {
        int a = prerequisites[i][0];
        int b = prerequisites[i][1];

        graph[b][graphSize[b]++] = a;
        indegree[a]++;
    }

    int *queue = (int *)malloc(numCourses * sizeof(int));
    int front = 0, rear = 0;

    // Push nodes with indegree 0
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int *result = (int *)malloc(numCourses * sizeof(int));
    int index = 0;

    // BFS
    while (front < rear) {
        int node = queue[front++];
        result[index++] = node;

        for (int i = 0; i < graphSize[node]; i++) {
            int neighbor = graph[node][i];
            indegree[neighbor]--;

            if (indegree[neighbor] == 0) {
                queue[rear++] = neighbor;
            }
        }
    }

    // If cycle exists
    if (index != numCourses) {
        *returnSize = 0;
        return NULL;
    }

    *returnSize = numCourses;
    return result;
}