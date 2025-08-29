#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// need to add struct tag here for self-reference
typedef struct node_struct { 
    int num;
    struct node_struct *next; // self-referencing
} node;


int main(void)
{
    node *linked_list = NULL;

    // node *n = malloc(sizeof(node));
    printf("sizeof(node): %lu\n", sizeof(node));

    for (int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->num = i;
        n->next = linked_list;
        linked_list = n;
    }

    node *ptr = linked_list;
    while (ptr != NULL)
    {
        
    }
    

    return 0;
}
