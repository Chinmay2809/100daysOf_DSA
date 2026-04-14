#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHARS 26
#define MAX_WORDS 100
#define MAX_WORD_LEN 100

char* alien_order(char** words, int words_size) {
    // Step 1: Initialize graph and indegree
    bool graph[MAX_CHARS][MAX_CHARS] = {false};
    int indegree[MAX_CHARS] = {0};
    bool exists[MAX_CHARS] = {false};
    
    // Mark existing characters
    for (int i = 0; i < words_size; i++) {
        for (int j = 0; words[i][j] != '\0'; j++) {
            exists[words[i][j] - 'a'] = true;
        }
    }
    
    // Step 2: Build graph by comparing adjacent words
    for (int i = 0; i < words_size - 1; i++) {
        char* w1 = words[i];
        char* w2 = words[i + 1];
        int min_len = strlen(w1) < strlen(w2) ? strlen(w1) : strlen(w2);
        
        // Check for invalid case: w2 is prefix of w1
        if (strlen(w1) > strlen(w2) && strncmp(w1, w2, min_len) == 0) {
            return strdup("");
        }
        
        // Find first differing character
        for (int j = 0; j < min_len; j++) {
            if (w1[j] != w2[j]) {
                int u = w1[j] - 'a';
                int v = w2[j] - 'a';
                if (!graph[u][v]) {
                    graph[u][v] = true;
                    indegree[v]++;
                }
                break;
            }
        }
    }
    
    // Step 3: Topological sort using Kahn's algorithm
    int queue[MAX_CHARS];
    int front = 0, rear = 0;
    
    // Add nodes with indegree 0 to queue
    for (int i = 0; i < MAX_CHARS; i++) {
        if (exists[i] && indegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    char* result = (char*)malloc((MAX_CHARS + 1) * sizeof(char));
    int idx = 0;
    
    while (front < rear) {
        int u = queue[front++];
        result[idx++] = u + 'a';
        
        for (int v = 0; v < MAX_CHARS; v++) {
            if (graph[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }
    
    // Check if all characters were included (no cycle)
    int total_chars = 0;
    for (int i = 0; i < MAX_CHARS; i++) {
        if (exists[i]) total_chars++;
    }
    
    if (idx != total_chars) {
        free(result);
        return strdup("");
    }
    
    result[idx] = '\0';
    return result;
}

int main() {
    // Test case
    char* words[] = {"baa", "abcd", "abca", "cab", "cad"};
    int words_size = 5;
    
    char* order = alien_order(words, words_size);
    
    if (strlen(order) == 0) {
        printf("Invalid order (cycle detected or invalid input)\n");
    } else {
        printf("Alien dictionary order: %s\n", order);
    }
    
    free(order);
    return 0;
}