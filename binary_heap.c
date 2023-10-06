#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A utility function to swap two integers
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Structure for Min Heap
struct MinHeap {
    int *harr;          // pointer to array of elements in heap
    int capacity;       // maximum possible size of min heap
    int heap_size;      // Current number of elements in min heap
};

// Function to create a new Min Heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->heap_size = 0;
    minHeap->capacity = capacity;
    minHeap->harr = (int*) malloc(sizeof(int) * capacity);
    return minHeap;
}

// Function to heapify a subtree with the root at given index
void MinHeapify(struct MinHeap* minHeap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < minHeap->heap_size && minHeap->harr[left] < minHeap->harr[smallest])
        smallest = left;
    if (right < minHeap->heap_size && minHeap->harr[right] < minHeap->harr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&minHeap->harr[i], &minHeap->harr[smallest]);
        MinHeapify(minHeap, smallest);
    }
}

// Function to insert a new key 'k'
void insertKey(struct MinHeap* minHeap, int k) {
    if (minHeap->heap_size == minHeap->capacity) {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    // First insert the new key at the end
    minHeap->heap_size++;
    int i = minHeap->heap_size - 1;
    minHeap->harr[i] = k;

    // Fix the min heap property if it is violated
    while (i != 0 && minHeap->harr[(i - 1) / 2] > minHeap->harr[i]) {
        swap(&minHeap->harr[i], &minHeap->harr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to decrease value of key at index 'i' to new_val
void decreaseKey(struct MinHeap* minHeap, int i, int new_val) {
    minHeap->harr[i] = new_val;
    while (i != 0 && minHeap->harr[(i - 1) / 2] > minHeap->harr[i]) {
        swap(&minHeap->harr[i], &minHeap->harr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the root which is the minimum element
int extractMin(struct MinHeap* minHeap) {
    if (minHeap->heap_size <= 0)
        return INT_MAX;
    if (minHeap->heap_size == 1) {
        minHeap->heap_size--;
        return minHeap->harr[0];
    }

    // Store the minimum value, and remove it from heap
    int root = minHeap->harr[0];
    minHeap->harr[0] = minHeap->harr[minHeap->heap_size - 1];
    minHeap->heap_size--;
    MinHeapify(minHeap, 0);

    return root;
}

// Function to delete a key stored at index i
void deleteKey(struct MinHeap* minHeap, int i) {
    decreaseKey(minHeap, i, INT_MIN);
    extractMin(minHeap);
}

// Function to get the minimum key (key at root) from min heap
int getMin(struct MinHeap* minHeap) {
    return minHeap->harr[0];
}

// Driver program to test above functions
int main() {
    struct MinHeap* minHeap = createMinHeap(11);
    insertKey(minHeap, 3);
    insertKey(minHeap, 2);
    deleteKey(minHeap, 1);
    insertKey(minHeap, 15);
    insertKey(minHeap, 5);
    insertKey(minHeap, 4);
    insertKey(minHeap, 45);
    printf("%d ", extractMin(minHeap));
    printf("%d ", getMin(minHeap));
    decreaseKey(minHeap, 2, 1);
    printf("%d\n", getMin(minHeap));

    free(minHeap->harr);
    free(minHeap);

    return 0;
}
