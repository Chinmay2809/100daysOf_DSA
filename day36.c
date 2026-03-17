#include <stdlib.h>
#include <stdbool.h>

// Min Heap implementation
typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

// Heap helper functions
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(MinHeap* heap, int index) {
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
        heapifyDown(heap, smallest);
    }
}

void heapifyUp(MinHeap* heap, int index) {
    int parent = (index - 1) / 2;
    
    if (index > 0 && heap->data[index] < heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        heapifyUp(heap, parent);
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
        heapifyUp(heap, heap->size);
        heap->size++;
    }
}

void minHeapPop(MinHeap* heap) {
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapifyDown(heap, 0);
    }
}

int minHeapTop(MinHeap* heap) {
    return heap->size > 0 ? heap->data[0] : -1;
}

void minHeapFree(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

// KthLargest structure
typedef struct KthLargest KthLargest;

struct KthLargest {
    MinHeap* minHeap;
    int k;
};

// Forward declaration of kthLargestAdd
int kthLargestAdd(KthLargest* obj, int val);

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
    obj->k = k;
    obj->minHeap = createMinHeap(k);
    
    // Add initial numbers to the heap
    for (int i = 0; i < numsSize; i++) {
        kthLargestAdd(obj, nums[i]);
    }
    
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    // If heap has less than k elements, add directly
    if (obj->minHeap->size < obj->k) {
        minHeapPush(obj->minHeap, val);
    }
    // If heap is full and new value is larger than smallest in heap
    else if (val > minHeapTop(obj->minHeap)) {
        minHeapPop(obj->minHeap);
        minHeapPush(obj->minHeap, val);
    }
    
    // Return the smallest element in heap (kth largest overall)
    return minHeapTop(obj->minHeap);
}

void kthLargestFree(KthLargest* obj) {
    minHeapFree(obj->minHeap);
    free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 * kthLargestFree(obj);
 */