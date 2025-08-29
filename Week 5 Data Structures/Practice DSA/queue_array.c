#include <stdio.h>
#include <stdlib.h>

// Implemented using Array

#define CAPACITY 4

typedef struct
{
    int arr[CAPACITY];
    int front;
    int size;
} queue_array;

void enqueue(queue_array *q, int data)
{
    if (q->size >= CAPACITY)
    {
        printf("Not enough space for %d\n", data);
        return;
    }

    int back = (q->front + q->size) % CAPACITY; // wraps around the array
    printf("back: %d - size: %d\n", back, q->size);
    q->arr[back] = data;
    q->size++;
}

int dequeue(queue_array *q)
{
    int tmp = q->arr[q->front];
    q->front++;
    q->size--;
    return tmp;
}

void print(queue_array *q)
{

    for (int i = q->front; i <= q->size+1; i++)
    {
        int back = i % CAPACITY; // wraps around
        // printf("back = %d: ", back);
        printf("%d ", q->arr[back]);
    }
    printf("\n");

    for (int i = 0; i < CAPACITY; i++)
    {
        printf("%d - ", q->arr[i]);
    }
}

int main(void)
{
    // Using Array
    queue_array q;
    q.front = 0;
    q.size = 0;
    
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 88);
    enqueue(&q, 99);

    printf("dequeued: %d\n", dequeue(&q));

    enqueue(&q, 77);
    enqueue(&q, 66);
    
    printf("dequeued: %d\n", dequeue(&q));

    print(&q);

    return 0;
}