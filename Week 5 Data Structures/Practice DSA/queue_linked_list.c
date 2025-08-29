#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Queue implementation using Singly Linked List
typedef struct _node
{   
    int data;
    struct _node *next;
} node;

typedef struct _queue
{
    node *front;
    node *rear;
} queue;

queue* create()
{
    queue *q = malloc(sizeof(queue));
    if (q == NULL)
    {
        return NULL;
    }

    q->front = q->rear = NULL;

    return q;
}

void enqueue(queue *q, int data)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return;
    }

    n->data = data;
    n->next = NULL;

    // if the queue is empty, add the first element to the queue
    if (q->rear == NULL)
    {
        q->front = q->rear = n;
        return;
    }
    
    // link the new node at last to the end of the list
    q->rear->next = n;

    // move the rear pointer to the new tail
    q->rear = n;

    // print(q);
}

int dequeue(queue *q)
{
    // temporarily store the pointer to free and the data to return
    node *tmp = q->front;
    int data = tmp->data;

    // move the front pointer to the next node
    q->front = q->front->next;

    // if the queue becomes empty: also set the rear pointer to NULL
    if (q->front == NULL)
    {   
        q->rear = NULL;
    }

    // free and return the data
    free(tmp);
    return data;
}

bool is_empty(queue *q)
{
    return q->front == NULL;
}

// Peek at the front element without removing it
int peek(queue *q)
{
    if (is_empty(q))
    {
        printf("Queue is empty!\n");
        return -1;
    }

    return q->front->data;
}

void print(queue *q)
{
    node *curr = q->front;
    while (curr != NULL)
    {
        printf("%d", curr->data);
        if (curr->next != NULL) printf(" -> ");
        curr = curr->next;
    }
    printf(" (END)\n");
}


int main(void)
{
    queue *q = create();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    print(q);
    printf("Peek: %d\n", peek(q));

    printf("dequeue(): %d\n", dequeue(q));
    printf("dequeue(): %d\n", dequeue(q));
    // printf("dequeue(): %d\n", dequeue(q));

    print(q);

    return 0;
}