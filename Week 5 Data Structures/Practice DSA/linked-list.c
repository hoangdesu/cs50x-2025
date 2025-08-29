#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node;

int main(void)
{
    printf("hehe\n");
    node *linked_list = NULL;

    for (int i = 1; i < 4; i++){
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        n->val = i;
        // n->next = NULL;

        n->next = linked_list;

        linked_list = n;
    }

    node *ptr = linked_list;
    while (ptr != NULL)
    {
        printf("%d\n", ptr->val);
        ptr = ptr->next;
    }

    return 0;
}