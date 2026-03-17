#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* data;       // Array to store deque elements
    int front;       // Index of the front element
    int rear;        // Index of the rear element
    int size;        // Current number of elements
    int capacity;    // Maximum capacity of the deque
} MyCircularDeque;

/** Initialize your data structure here. Set the maximum size of the deque to be k. */
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    obj->data = (int*)malloc(k * sizeof(int));
    obj->front = 0;
    obj->rear = 0;
    obj->size = 0;
    obj->capacity = k;
    return obj;
}

/** Adds an item at the front of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if (obj->size == obj->capacity) {
        return false;  // Deque is full
    }
    
    // Move front pointer backward (circularly)
    obj->front = (obj->front - 1 + obj->capacity) % obj->capacity;
    obj->data[obj->front] = value;
    obj->size++;
    
    // If this was the first element, update rear to point to same position
    if (obj->size == 1) {
        obj->rear = obj->front;
    }
    
    return true;
}

/** Adds an item at the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if (obj->size == obj->capacity) {
        return false;  // Deque is full
    }
    
    // Insert at current rear position
    obj->data[obj->rear] = value;
    // Move rear pointer forward (circularly)
    obj->rear = (obj->rear + 1) % obj->capacity;
    obj->size++;
    
    return true;
}

/** Deletes an item from the front of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (obj->size == 0) {
        return false;  // Deque is empty
    }
    
    // Move front pointer forward (circularly)
    obj->front = (obj->front + 1) % obj->capacity;
    obj->size--;
    
    return true;
}

/** Deletes an item from the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (obj->size == 0) {
        return false;  // Deque is empty
    }
    
    // Move rear pointer backward (circularly)
    obj->rear = (obj->rear - 1 + obj->capacity) % obj->capacity;
    obj->size--;
    
    return true;
}

/** Get the front item from the deque. */
int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (obj->size == 0) {
        return -1;  // Deque is empty
    }
    return obj->data[obj->front];
}

/** Get the last item from the deque. */
int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (obj->size == 0) {
        return -1;  // Deque is empty
    }
    // Rear points to the next position after the last element
    // So the last element is at (rear - 1 + capacity) % capacity
    int lastIndex = (obj->rear - 1 + obj->capacity) % obj->capacity;
    return obj->data[lastIndex];
}

/** Checks whether the circular deque is empty or not. */
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->size == 0;
}

/** Checks whether the circular deque is full or not. */
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return obj->size == obj->capacity;
}

/** Deallocates memory for the deque. */
void myCircularDequeFree(MyCircularDeque* obj) {
    free(obj->data);
    free(obj);
}

/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 * bool param_3 = myCircularDequeDeleteFront(obj);
 * bool param_4 = myCircularDequeDeleteLast(obj);
 * int param_5 = myCircularDequeGetFront(obj);
 * int param_6 = myCircularDequeGetRear(obj);
 * bool param_7 = myCircularDequeIsEmpty(obj);
 * bool param_8 = myCircularDequeIsFull(obj);
 * myCircularDequeFree(obj);
 */