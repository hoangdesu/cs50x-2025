#include <stdio.h>
#include <string.h>

struct node {
    int id;
    char name;
} node_t; 

int main(void)
{
    struct node a;
    struct node b;

    printf("a.id=%d\n", a.id);
    printf("node_t.id=%d\n", node_t.id);



    return 0;
}