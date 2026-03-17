#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// Stack node
struct Stack {
    int val;
    struct Stack* next;
};

// Push to stack
void push(struct Stack** top, int val) {
    struct Stack* newNode = (struct Stack*)malloc(sizeof(struct Stack));
    newNode->val = val;
    newNode->next = *top;
    *top = newNode;
}

// Pop from stack
int pop(struct Stack** top) {
    struct Stack* temp = *top;
    int val = temp->val;
    *top = temp->next;
    free(temp);
    return val;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct Stack* s1 = NULL;
    struct Stack* s2 = NULL;

    // Push all elements into stacks
    while (l1) {
        push(&s1, l1->val);
        l1 = l1->next;
    }

    while (l2) {
        push(&s2, l2->val);
        l2 = l2->next;
    }

    int carry = 0;
    struct ListNode* result = NULL;

    // Process stacks
    while (s1 || s2 || carry) {
        int sum = carry;

        if (s1) sum += pop(&s1);
        if (s2) sum += pop(&s2);

        // Create new node at front
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = sum % 10;
        newNode->next = result;
        result = newNode;

        carry = sum / 10;
    }

    return result;
}