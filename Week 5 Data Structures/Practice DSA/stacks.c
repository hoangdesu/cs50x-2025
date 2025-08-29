#include <stdio.h>
#include <stdlib.h>

// Implemented using Array

#define CAPACITY 10

typedef struct
{
    int arr[CAPACITY];
    int top;
} stack_array;

void push(stack_array *s, int data)
{
    s->arr[s->top] = data;
    s->top++;
}

int pop(stack_array *s)
{
    // int removed = s->arr[s->top-1];
    // s->arr[s->top] = 0; // not really needed. only need to change the top pointer and overwrite new value
    
    s->top--;
    return s->arr[s->top];
}

void print(stack_array *s)
{
    // only need to loop upto the top of the stack
    for (int i = 0; i < s->top; i++)
    {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

// not necessary
void clean(stack_array *s)
{
    for (int i = 0; i < CAPACITY; i++)
    {
        s->arr[i] = 0;
    }
}

// Using Linked List
typedef struct _stack_ll
{
    int val;
    struct _stack_ll *next;
} stack_linkedlist;

stack_linkedlist* push_ll(stack_linkedlist *s, int data)
{
    stack_linkedlist *node = malloc(sizeof(stack_linkedlist));
    if (node == NULL)
    {
        return NULL;
    }

    node->val = data;
    node->next = NULL;

    printf("pushing: %d (%p)\n", node->val, node);

    node->next = s;
    s = node;

    return s;
}

stack_linkedlist* pop_ll(stack_linkedlist *s)
{
    // TODO: check list is not empty before pop
    stack_linkedlist *tmp = s;
    s = s->next;
    free(tmp);
    return s;
}

void print_ll(stack_linkedlist *s)
{
    if (s == NULL)
    {
        printf("(END)\n");
        return;
    }

    printf("%d -> ", s->val);
    print_ll(s->next);

    // stack_linkedlist *ptr = s;
    // while (ptr != NULL)
    // {
    //     printf("%d -> ", ptr->val);
    //     ptr = ptr->next;
    // }
}

int main(void)
{
    // Using Array
    stack_array sArr;
    sArr.top = 0;
    // clean(&sArr);

    push(&sArr, 5);
    push(&sArr, 1);
    
    int removed = pop(&sArr);
    printf("Removed: %d\n", removed);
    push(&sArr, 9);
    push(&sArr, 8);

    print(&sArr);

    // Using Linked List
    printf("Using Linked List:\n");
    stack_linkedlist *sll = NULL;

    printf("sll = %p\n", sll);

    sll = push_ll(sll, 3);
    sll = push_ll(sll, 5);
    sll = push_ll(sll, 9);
    sll = push_ll(sll, 6);

    sll = pop_ll(sll);
    sll = pop_ll(sll);

    print_ll(sll);

    return 0;
}
