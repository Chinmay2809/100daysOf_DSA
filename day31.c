#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* stack;      // Stack storing values
    int* min;        // Stack storing minimum values
    int top;         // Current top index
    int capacity;    // Current capacity
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->capacity = 10000;
    obj->stack = (int*)malloc(obj->capacity * sizeof(int));
    obj->min = (int*)malloc(obj->capacity * sizeof(int));
    obj->top = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->top >= obj->capacity - 1) {
        obj->capacity *= 2;
        obj->stack = (int*)realloc(obj->stack, obj->capacity * sizeof(int));
        obj->min = (int*)realloc(obj->min, obj->capacity * sizeof(int));
    }
    
    obj->top++;
    obj->stack[obj->top] = val;
    
    // Store the current minimum
    if (obj->top == 0) {
        obj->min[obj->top] = val;
    } else {
        int prevMin = obj->min[obj->top - 1];
        obj->min[obj->top] = (val < prevMin) ? val : prevMin;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->top >= 0) {
        obj->top--;
    }
}

int minStackTop(MinStack* obj) {
    return (obj->top >= 0) ? obj->stack[obj->top] : INT_MIN;
}

int minStackGetMin(MinStack* obj) {
    return (obj->top >= 0) ? obj->min[obj->top] : INT_MIN;
}

void minStackFree(MinStack* obj) {
    free(obj->stack);
    free(obj->min);
    free(obj);
}