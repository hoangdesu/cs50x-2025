#include <stdio.h>
#include <stdlib.h>

typedef struct dllist
{
    int val;
    struct dllist *prev;
    struct dllist *next;
} dllnode;

dllnode *create(int val)
{
    dllnode *n = malloc(sizeof(dllnode));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = val;
    n->prev = NULL;
    n->next = NULL;

    return n;
}

dllnode* insert(dllnode *list, int val)
{
    dllnode *n = malloc(sizeof(dllnode));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = val;
    n->prev = NULL;
    n->next = NULL;

    list->prev = n;
    n->next = list;
    list = n;

    return list;
}

void print(dllnode *list)
{
    if (list == NULL)
    {
        printf("(END)\n");
        return;
    }

    printf("%d -> ", list->val);
    print(list->next);
}

void print_reverse(dllnode *list)
{
    printf("Printing in reverse: ");

    // Move the pointer to the end
    dllnode *ptr = list;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    // ptr is pointing at the last node at this point
    
    printf("last ptr = %d\n", ptr->val);

    while (ptr != NULL)
    {
        printf("%d -> ", ptr->val);
        ptr = ptr->prev;
    }
    // ptr is pointing at NULL at this point

    printf("(END)\n");
    
    // printf("current = %d\n", ptr->val);
}

int delete(dllnode *list, int target)
{
    if (list == NULL)
    {
        return target;
    }
    else if (list->val == target)
    {
        printf("deleting %d...\n", list->val);
        
        // Temporary store the deleting value to return
        int d = list->val;

        // Point the prev's next pointer to next
        list->prev->next = list->next;

        // Point the next's prev pointer to prev
        list->next->prev = list->prev;
        
        // Free the current node
        free(list);

        return d;
    }
    
    return delete(list->next, target);
}

void insert_last(dllnode *list, int val)
{
    if (list->next == NULL)
    {
        printf("list->val = %d\n", list->val);

        dllnode *n = malloc(sizeof(dllnode));
        if (n == NULL) {
            return;
        }

        n->val = val;
        n->prev = list;
        n->next = NULL;

        list->next = n;

        return;
    }

    insert_last(list->next, val);
}

// Recursively free the list from the END of the list
void destroy(dllnode *list)
{
    if (list == NULL)
    {
        return;
    }

    destroy(list->next);

    printf("Freeing %d...\n", list->val);
    free(list);
}

int main(void)
{
    dllnode *dllist = create(10);

    dllist = insert(dllist, 20); // 20 -> 10
    dllist = insert(dllist, 30); // 30 -> 20 -> 10
    dllist = insert(dllist, 50);

    insert_last(dllist, 69);
    dllist = insert(dllist, 40);

    int d = delete(dllist, 30); // 10 -> 20 -> 50 -> 40
    printf("deleted: %d\n", d);

    int d1 = delete(dllist, 99);
    printf("did not deleted: %d\n", d1);

    print(dllist);

    print_reverse(dllist);

    destroy(dllist);

    print(dllist);

    return 0;
}