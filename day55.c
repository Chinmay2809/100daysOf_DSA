#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int* rightSideView(struct TreeNode* root, int* returnSize) {
    
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * 1000);
    struct TreeNode* queue[2000];

    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 0;

    while (front < rear) {
        int size = rear - front;

        for (int i = 0; i < size; i++) {
            struct TreeNode* node = queue[front++];

            // If it's the last node of this level
            if (i == size - 1) {
                result[level++] = node->val;
            }

            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
    }

    *returnSize = level;
    return result;
}