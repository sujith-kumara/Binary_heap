#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a task
typedef struct {
    char description[100];
    int priority;
} Task;

// Structure to represent a node in the priority queue (implemented as a linked list)
typedef struct Node {
    Task task;
    struct Node* next;
} Node;

// Structure to represent a priority queue
typedef struct {
    Node* front;
} PriorityQueue;

// Function to create a new task
Task createTask(char description[], int priority) {
    Task task;
    strcpy(task.description, description);
    task.priority = priority;
    return task;
}

// Function to create a new node
Node* createNode(Task task) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->task = task;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    return pq;
}

// Function to enqueue a task in the priority queue
void enqueue(PriorityQueue* pq, Task task) {
    Node* newNode = createNode(task);
    
    if (pq->front == NULL || task.priority > pq->front->task.priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        Node* current = pq->front;
        while (current->next != NULL && task.priority <= current->next->task.priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to dequeue a task from the priority queue
Task dequeue(PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Queue is empty.\n");
        exit(1);
    }

    Node* temp = pq->front;
    Task task = temp->task;
    pq->front = pq->front->next;
    free(temp);
    return task;
}

// Function to check if the priority queue is empty
int isEmpty(PriorityQueue* pq) {
    return pq->front == NULL;
}

// Function to print the tasks in the priority queue
void printQueue(PriorityQueue* pq) {
    Node* current = pq->front;
    while (current != NULL) {
        printf("Task: %s, Priority: %d\n", current->task.description, current->task.priority);
        current = current->next;
    }
}

int main() {
    PriorityQueue* pq = createPriorityQueue();
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue a task\n");
        printf("2. Dequeue a task\n");
        printf("3. Print tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                char description[100];
                int priority;
                scanf(" %99[^\n]", description); // Read up to 99 characters until a newline
                printf("Enter task priority: ");
                scanf("%d", &priority);
                Task task = createTask(description, priority);
                enqueue(pq, task);
                printf("Task enqueued.\n");
                break;

            case 2:
                if (!isEmpty(pq)) {
                    Task next_task = dequeue(pq);
                    printf("Dequeued Task: %s, Priority: %d\n", next_task.description, next_task.priority);
                } else {
                    printf("Queue is empty.\n");
                }
                break;

            case 3:
                printf("Tasks in the queue:\n");
                printQueue(pq);
                break;

            case 4:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}