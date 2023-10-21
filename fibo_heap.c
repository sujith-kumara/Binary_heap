#include <stdio.h>
#include <stdlib.h>

#define NIL 0

struct fheap_node {
    struct fheap_node *parent;
    struct fheap_node *left;
    struct fheap_node *right;
    struct fheap_node *child;
    int degree;
    int mark;
    int key;
};

struct fheap_node *min = NIL;
int nNodes = 0;

/* Creating Fibonacci heap */
void create_fib() {
    min = NIL;
    nNodes = 0;
}

/* Inserting into Fibonacci heap */
void Finsert(int val) {
    struct fheap_node *fheap = (struct fheap_node *)malloc(sizeof(struct fheap_node));
    fheap->key = val;
    fheap->parent = NIL;
    fheap->left = NIL;
    fheap->right = NIL;
    fheap->child = NIL;

    if (min != NIL) {
        fheap->right = min;
        fheap->left = min->left;
        min->left = fheap;
        fheap->left->right = fheap;
        if (val < min->key) {
            min = fheap;
        }
    } else {
        min = fheap;
        min->left = min;
        min->right = min;
    }
    nNodes++;
}

/* Displaying Fibonacci heap */
void display(struct fheap_node *min1) {
    struct fheap_node *q, *chil;
    if (min == NIL) {
        printf("\nFibonacci heap is empty");
        return;
    }
    q = min;
    printf("\nFibonacci heap display");
    do {
        printf("\t%d ", q->key);
        if (q->child != NIL) {
            display(q->child);
        }
        q = q->right;
    } while (q != min);
}

/* Finding the minimum key in the heap */
void findmin() {
    printf("\nMinimum is %d: ", min->key);
}

int main() {
    int option, n;

    create_fib();
    while (1) {
        printf("\nMenu\n");
        printf("1: Create Fibonacci heap\n");
        printf("2: Insert into Fibonacci heap\n");
        printf("3: Find min in Fibonacci heap\n");
        printf("4: Display\n");
        printf("5: Exit\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                create_fib();
                break;
            case 2:
                printf("\nEnter the element: ");
                scanf("%d", &n);
                Finsert(n);
                break;
            case 3:
                findmin();
                break;
            case 4:
                display(min);
                break;
            case 5:
                exit(0);
            default:
                printf("\nWrong choice... Try again\n");
        }
    }

    return 0;
}
