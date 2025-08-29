#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct
{
    int val;
    struct node_struct *next;
} node;

node* create(int val)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = val;
    n->next = NULL;
    
    return n;
}

void traverse(node *linked_list)
{
    node *ptr = linked_list;
    while (ptr != NULL)
    {
        printf("%d", ptr->val);
        if (ptr->next != NULL)
        {
            printf(" -> ");
        }

        // if (ptr->next == NULL)
        // {
        //     printf("END\n");
        // }

        ptr = ptr->next;
    }

    printf(" (END)\n");

    // for (node *ptr = linked_list; ptr != NULL; ptr = ptr->next)
    // {
    //     printf("%d", ptr->val);

    // }
}


void recursive_traverse(node *list)
{    
    if (list->next == NULL)
    {
        printf("%d (END)\n", list->val);
        return;
    }
    
    printf("%d -> ", list->val);

    recursive_traverse(list->next);
}


// In C, function arguments are passed by value — even pointers. So p is a copy of ptr, and reassigning p doesn’t touch ptr in main.
// => Solution: You need to pass a pointer to the pointer (a double pointer)
void insert_using_double_ptr(node **head, int val)
{
    printf("head: %p\n", head);

    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return;
    }

    n->val = val;

    // make head pointer to point at the newly created node
    // then point the new node to the previous head
    n->next = *head;
    *head = n;

    printf("new head: %p\n", head);   
}

node* insert(node *head, int new_val)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = new_val;
    n->next = head;
    head = n;

    return head;
}


void insert_last(node *list, int val)
{
    // - This loop has a problem: it will make pointer go out of bound.
    // - at the end, ptr will NOT point to any node
    // - in fact, we need ptr to stop right at the end of the list

    // node *ptr = list;
    // while (ptr != NULL)
    // {
    //     ptr = ptr-> next;
    // }

    // printf("Reached end of list: %d\n", ptr->val); // this will cause segfault, since ptr now is NULL aka NOT pointing at any node. Therefore no value presented

    // first, traverse all the way to the end of the list
    node *ptr = list;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    // now ptr points at the last node of the list

    // printf("Reached end of list: %d - ptr->next: %s\n", ptr->val, ptr->next);

    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return;
    }
    n->val = val;
    n->next = NULL;

    // attach the new node to the end of the list
    ptr->next = n;

    // printf("Reached end of list: %d - ptr->next: %d\n", ptr->val, ptr->next->val);
}


void recursive_insert_last(node *list, int val)
{
    // when reach the end of the list
    if (list->next == NULL)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return;
        }
        
        n->val = val;
        n->next = NULL;

        // list now represents the last node. Add new node to the end
        list->next = n;

        return;
    }

    recursive_insert_last(list->next, val);
}


int find(node *list, int target)
{
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->val == target) return 1;
    }

    return 0;
}


int index_of(node *list, int target)
{
    int i = 0;
    for (node *p = list; p != NULL; p = p->next)
    {
        if (p->val == target) return i;
        i++;
    }
    return -1;
}


node* insert_sorted(node *sorted_list, int val)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = val;
    n->next = NULL;

    node *ptr = sorted_list;
    while (ptr != NULL)
    {
        // insert in the middle
        // need to check if ptr->next is not null
        if (val >= ptr->val && ptr->next != NULL && val < ptr->next->val)
        {   
            // make the current node point to the new node
            // point the new node to the node behind
            node *nextPtr = ptr->next;
            ptr->next = n;
            n->next = nextPtr;

            return sorted_list;
        }
        
        // insert first
        else if (val < ptr->val)
        {
            n->next = ptr;
            ptr = n;
            return ptr;
        }
    
        // insert last
        else if (ptr->next == NULL)
        {
            ptr->next = n;
            return sorted_list;
        }
        
        // printf("updating ptr: %d\n", ptr->val);
        ptr = ptr->next;

    }
    
    return ptr;
}

void free_list(node *linked_list)
{
    node *ptr = linked_list;
    while(ptr->next != NULL)
    {
        node *next = ptr; // store the next pointer in a temp variable
        free(ptr);
        ptr = next;
    }
}

// Recursive version of free_list()
void destroy(node* list)
{
    if (list == NULL)
    {
        return;
    }
    destroy(list->next);
    free(list);
}

node* delete(node *linked_list, int val)
{
    // special case: deleting the head
    if (linked_list->val == val)
    {
        node *tmp = linked_list;
        linked_list = linked_list->next;
        free(tmp);
        return linked_list;
    }

    node *ptr = linked_list;
    while (ptr->next != NULL)
    {
        if (ptr->next->val == val)
        {
            node *tmp = ptr->next;
            ptr->next = ptr->next->next;
            free(tmp);
            return linked_list;
        }
        ptr = ptr->next;
    }

    return linked_list;
}


int main(void)
{
    node *linked_list = create(1);

    printf("create: %p\n", linked_list);

    insert_using_double_ptr(&linked_list, 2);
    printf("insert 2: %p\n", linked_list);
    
    insert_using_double_ptr(&linked_list, 3);
    printf("insert 3: %p\n", linked_list);


    linked_list = insert(linked_list, 6);
    linked_list = insert(linked_list, 7);


    printf("before insert 9: %p\n", linked_list);
    insert_last(linked_list, 9);
    insert_last(linked_list, 10);


    recursive_insert_last(linked_list, 11);
    recursive_insert_last(linked_list, 5);

    traverse(linked_list);
    recursive_traverse(linked_list);

    int find9 = find(linked_list, 9);
    printf("9 %s\n", find9 == 1 ? "found" : "not found");
    printf("8 %s\n", find(linked_list, 8) == 1 ? "found" : "not found");
    
    printf("index of 7: %d\n", index_of(linked_list, 7));
    printf("index of 6: %d\n", index_of(linked_list, 6));
    printf("index of 11: %d\n", index_of(linked_list, 11));
    printf("index of 5: %d\n", index_of(linked_list, 5));
    printf("index of 8: %d\n", index_of(linked_list, 8));

    printf("Deleting 2 (middle): ");
    linked_list = delete(linked_list, 2);
    traverse(linked_list);

    printf("Deleting 7 (head): ");
    linked_list = delete(linked_list, 7);
    traverse(linked_list);

    printf("Deleting 5 (tail): ");
    linked_list = delete(linked_list, 5);
    traverse(linked_list);

    free_list(linked_list);
    printf("After free: ");
    traverse(linked_list);


    node *sorted_linked_list = create(5);
    
    // insert 3 into 2 - 5: 3 > 2 && 3 < 5 => val > ptr->val && val < ptr->next->val
    
    insert_last(sorted_linked_list, 8);

    sorted_linked_list = insert_sorted(sorted_linked_list, 6);
    sorted_linked_list = insert_sorted(sorted_linked_list, 3);
    sorted_linked_list = insert_sorted(sorted_linked_list, 15);
    sorted_linked_list = insert_sorted(sorted_linked_list, 2);
    sorted_linked_list = insert_sorted(sorted_linked_list, 12);
    sorted_linked_list = insert_sorted(sorted_linked_list, 19);
    sorted_linked_list = insert_sorted(sorted_linked_list, 8);

    printf("Sorted linked list:\n");
    traverse(sorted_linked_list);

    // free_list(sorted_linked_list);
    destroy(sorted_linked_list);
    printf("After free: ");
    traverse(sorted_linked_list);
    
    return 0;
}