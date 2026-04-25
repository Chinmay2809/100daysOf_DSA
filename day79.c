#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 1000

int adj[MAX][MAX];
int V;

int disc[MAX], low[MAX], stack[MAX], top, timeCounter;
bool inStack[MAX];
int sccCount;

int min(int a, int b) {
    return a < b ? a : b;
}

void tarjanDFS(int u) {
    disc[u] = low[u] = ++timeCounter;
    stack[++top] = u;
    inStack[u] = true;
    
    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {
            if (disc[v] == -1) {
                tarjanDFS(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
    
    // If u is root node of SCC
    if (low[u] == disc[u]) {
        sccCount++;
        printf("SCC %d: ", sccCount);
        while (1) {
            int w = stack[top--];
            inStack[w] = false;
            printf("%d ", w);
            if (w == u) break;
        }
        printf("\n");
    }
}

int findSCCs() {
    disc = (int*)malloc(V * sizeof(int));
    low = (int*)malloc(V * sizeof(int));
    inStack = (bool*)malloc(V * sizeof(bool));
    stack = (int*)malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) {
        disc[i] = -1;
        inStack[i] = false;
    }
    
    top = -1;
    timeCounter = 0;
    sccCount = 0;
    
    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i);
        }
    }
    
    free(disc);
    free(low);
    free(inStack);
    free(stack);
    
    return sccCount;
}