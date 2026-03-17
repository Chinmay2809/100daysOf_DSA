#include <stdlib.h>
#include <stdbool.h>

// Stack implementation
typedef struct {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = 100;
    stack->data = (int*)malloc(stack->capacity * sizeof(int));
    stack->top = -1;
    return stack;
}

void pushToStack(Stack* stack, int val) {
    if (stack->top >= stack->capacity - 1) {
        stack->capacity *= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
    }
    stack->data[++stack->top] = val;
}

int popFromStack(Stack* stack) {
    return stack->data[stack->top--];
}

int peekStack(Stack* stack) {
    return stack->data[stack->top];
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// Queue implementation using two stacks
typedef struct {
    Stack* inputStack;   // Stack for push operations
    Stack* outputStack;  // Stack for pop/peek operations
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->inputStack = createStack();
    queue->outputStack = createStack();
    return queue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    pushToStack(obj->inputStack, x);
}

/** Helper function to transfer elements from input stack to output stack */
void transferElements(MyQueue* obj) {
    if (isStackEmpty(obj->outputStack)) {
        while (!isStackEmpty(obj->inputStack)) {
            pushToStack(obj->outputStack, popFromStack(obj->inputStack));
        }
    }
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    transferElements(obj);
    return popFromStack(obj->outputStack);
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    transferElements(obj);
    return peekStack(obj->outputStack);
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    return isStackEmpty(obj->inputStack) && isStackEmpty(obj->outputStack);
}

/** Frees the queue. */
void myQueueFree(MyQueue* obj) {
    freeStack(obj->inputStack);
    freeStack(obj->outputStack);
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);
 * int param_2 = myQueuePop(obj);
 * int param_3 = myQueuePeek(obj);
 * bool param_4 = myQueueEmpty(obj);
 * myQueueFree(obj);
 */