#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int key;
    int degree;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
};

struct BinomialHeap {
    struct Node* head;
};

// Function to create a new node with a given key
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to merge two binomial trees of the same degree
struct Node* mergeTrees(struct Node* tree1, struct Node* tree2) {
    if (tree1->key < tree2->key) {
        tree1->sibling = tree2->child;
        tree2->child = tree1;
        tree1->parent = tree2;
        tree2->degree++;
        return tree2;
    } else {
        tree2->sibling = tree1->child;
        tree1->child = tree2;
        tree2->parent = tree1;
        tree1->degree++;
        return tree1;
    }
}

// Function to find the minimum key in the binomial heap
int findMin(struct BinomialHeap* heap) {
    if (heap->head == NULL) {
        printf("Heap is empty\n");
        return INT_MAX;  // Return a special value to indicate an empty heap
    }
    int minKey = heap->head->key;
    struct Node* currentNode = heap->head;
    while (currentNode != NULL) {
        if (currentNode->key < minKey) {
            minKey = currentNode->key;
        }
        currentNode = currentNode->sibling;
    }
    return minKey;
}

// Function to union two binomial heaps
struct BinomialHeap* unionHeaps(struct BinomialHeap* heap1, struct BinomialHeap* heap2) {
    struct BinomialHeap* resultHeap = (struct BinomialHeap*)malloc(sizeof(struct BinomialHeap));
    resultHeap->head = NULL;

    // Merge the binomial trees from both heaps
    struct Node* carry = NULL;
    struct Node* tree1 = heap1->head;
    struct Node* tree2 = heap2->head;

    while (tree1 || tree2 || carry) {
        struct Node* combinedTree = NULL;
        if (tree1 && tree2) {
            if (tree1->degree == tree2->degree) {
                combinedTree = carry ? mergeTrees(carry, tree1) : tree1;
                tree1 = tree1->sibling;
                tree2 = tree2->sibling;
            } else if (tree1->degree < tree2->degree) {
                combinedTree = tree1;
                tree1 = tree1->sibling;
            } else {
                combinedTree = tree2;
                tree2 = tree2->sibling;
            }
        } else if (tree1) {
            combinedTree = tree1;
            tree1 = tree1->sibling;
        } else if (tree2) {
            combinedTree = tree2;
            tree2 = tree2->sibling;
        } else {
            combinedTree = carry;
            carry = NULL;
        }

        combinedTree->sibling = resultHeap->head;
        resultHeap->head = combinedTree;
    }

    return resultHeap;
}

// Function to insert a key into the binomial heap
struct BinomialHeap* insertKey(struct BinomialHeap* heap, int key) {
    struct BinomialHeap* newHeap = (struct BinomialHeap*)malloc(sizeof(struct BinomialHeap));
    newHeap->head = createNode(key);
    heap = unionHeaps(heap, newHeap);
    return heap;
}
struct BinomialHeap* extractMin(struct BinomialHeap* heap) {
    if (heap->head == NULL) {
        printf("Heap is empty\n");
        return heap;  // Return the unchanged heap (empty)
    }

    struct Node* minNode = heap->head;
    struct Node* prevNode = NULL;
    struct Node* currentNode = heap->head;

    // Find the minimum node in the root list
    while (currentNode->sibling != NULL) {
        if (currentNode->sibling->key < minNode->key) {
            minNode = currentNode->sibling;
            prevNode = currentNode;
        }
        currentNode = currentNode->sibling;
    }

    // Remove the minimum node from the root list
    if (prevNode) {
        prevNode->sibling = minNode->sibling;
    } else {
        heap->head = minNode->sibling;
    }

    // Reverse the children of the minimum node
    struct Node* child = minNode->child;
    struct Node* temp = NULL;
    while (child != NULL) {
        temp = child->sibling;
        child->sibling = heap->head;
        child->parent = NULL;
        heap->head = child;
        child = temp;
    }

    // Create a new heap for the remaining binomial trees and union it with the current heap
    struct BinomialHeap* remainingHeap = (struct BinomialHeap*)malloc(sizeof(struct BinomialHeap));
    remainingHeap->head = NULL;
    remainingHeap->head = minNode->child;  // The children of the minimum node

    // Free the memory of the minimum node
    free(minNode);

    // Union the current heap with the heap of remaining trees
    heap = unionHeaps(heap, remainingHeap);

    return heap;
}
// Function to delete a node with a given key from the binomial heap
struct BinomialHeap* deleteKey(struct BinomialHeap* heap, int key) {
    // Find the node with the specified key and decrease its key to INT_MIN
    struct Node* nodeToDelete = NULL;
    struct Node* prevNode = NULL;
    struct Node* currentNode = heap->head;

    while (currentNode) {
        if (currentNode->key == key) {
            nodeToDelete = currentNode;
            break;
        }
        prevNode = currentNode;
        currentNode = currentNode->sibling;
    }

    if (nodeToDelete) {
        // Decrease the key to INT_MIN (assuming INT_MIN represents negative infinity)
        nodeToDelete->key = INT_MIN;

        if (prevNode) {
            prevNode->sibling = currentNode->sibling;
        } else {
            heap->head = currentNode->sibling;
        }

        // Extract the minimum node to remove the node with the specified key
        heap = extractMin(heap);
    } else {
        printf("Key not found in the heap\n");
    }

    return heap;
}

int main() {
    struct BinomialHeap* binHeap = (struct BinomialHeap*)malloc(sizeof(struct BinomialHeap));
    binHeap->head = NULL;

    // Example usage of the binomial heap operations
    binHeap = insertKey(binHeap, 10);
    binHeap = insertKey(binHeap, 5);
    binHeap = insertKey(binHeap, 20);
    binHeap = insertKey(binHeap, 1);

    printf("Minimum key in the heap: %d\n", findMin(binHeap));

    binHeap = deleteKey(binHeap, 5);

    printf("Minimum key in the heap after deletion: %d\n", findMin(binHeap));

    return 0;
}
