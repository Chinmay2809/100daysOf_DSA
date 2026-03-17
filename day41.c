#include <stdlib.h>
#include <stdio.h>

// Max Heap implementation (for left half - smaller numbers)
typedef struct {
    int* data;
    int size;
    int capacity;
} MaxHeap;

// Min Heap implementation (for right half - larger numbers)
typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

// Helper functions
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Max Heap operations
void maxHeapifyDown(MaxHeap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }
    
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        maxHeapifyDown(heap, largest);
    }
}

void maxHeapifyUp(MaxHeap* heap, int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && heap->data[index] > heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        maxHeapifyUp(heap, parent);
    }
}

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void maxHeapPush(MaxHeap* heap, int val) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = val;
        maxHeapifyUp(heap, heap->size);
        heap->size++;
    }
}

int maxHeapPop(MaxHeap* heap) {
    if (heap->size == 0) return 0;
    
    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    maxHeapifyDown(heap, 0);
    return max;
}

int maxHeapTop(MaxHeap* heap) {
    return heap->size > 0 ? heap->data[0] : 0;
}

// Min Heap operations
void minHeapifyDown(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        minHeapifyDown(heap, smallest);
    }
}

void minHeapifyUp(MinHeap* heap, int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && heap->data[index] < heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        minHeapifyUp(heap, parent);
    }
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void minHeapPush(MinHeap* heap, int val) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = val;
        minHeapifyUp(heap, heap->size);
        heap->size++;
    }
}

int minHeapPop(MinHeap* heap) {
    if (heap->size == 0) return 0;
    
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapifyDown(heap, 0);
    return min;
}

int minHeapTop(MinHeap* heap) {
    return heap->size > 0 ? heap->data[0] : 0;
}

// MedianFinder structure
typedef struct {
    MaxHeap* leftHeap;  // Max heap for left half (smaller numbers)
    MinHeap* rightHeap; // Min heap for right half (larger numbers)
} MedianFinder;

/** Initialize your data structure here. */
MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->leftHeap = createMaxHeap(50000);  // Adjust capacity as needed
    obj->rightHeap = createMinHeap(50000);
    return obj;
}

/** Adds a number into the data structure. */
void medianFinderAddNum(MedianFinder* obj, int num) {
    // Add to appropriate heap
    if (obj->leftHeap->size == 0 || num <= maxHeapTop(obj->leftHeap)) {
        maxHeapPush(obj->leftHeap, num);
    } else {
        minHeapPush(obj->rightHeap, num);
    }
    
    // Balance heaps: left heap can have at most one more element than right heap
    if (obj->leftHeap->size > obj->rightHeap->size + 1) {
        // Move one from left to right
        int val = maxHeapPop(obj->leftHeap);
        minHeapPush(obj->rightHeap, val);
    } else if (obj->rightHeap->size > obj->leftHeap->size) {
        // Move one from right to left
        int val = minHeapPop(obj->rightHeap);
        maxHeapPush(obj->leftHeap, val);
    }
}

/** Returns the median of current data stream */
double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->leftHeap->size > obj->rightHeap->size) {
        // Odd number of elements
        return (double)maxHeapTop(obj->leftHeap);
    } else {
        // Even number of elements
        return ((double)maxHeapTop(obj->leftHeap) + (double)minHeapTop(obj->rightHeap)) / 2.0;
    }
}

/** Frees the allocated memory */
void medianFinderFree(MedianFinder* obj) {
    free(obj->leftHeap->data);
    free(obj->leftHeap);
    free(obj->rightHeap->data);
    free(obj->rightHeap);
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 * double param_2 = medianFinderFindMedian(obj);
 * medianFinderFree(obj);
 */