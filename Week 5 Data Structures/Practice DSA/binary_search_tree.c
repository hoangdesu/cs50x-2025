#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct
{
    int val;
    struct node_struct *left;
    struct node_struct *right;
} node;

void print_tree(node *tree);
void free_tree(node *root);

int main(void)
{
    node *tree = NULL;

    node *root_node = malloc(sizeof(node));
    if (root_node == NULL)
    {
        free_tree(tree);
        return 1;
    }
    root_node->val = 5;
    root_node->left = NULL;
    root_node->right = NULL;
    tree = root_node;
    
    node *left_node = malloc(sizeof(node));
    if (left_node == NULL)
    {
        free_tree(tree);
        return 1;
    }
    left_node->val = 1;
    left_node->left = NULL;
    left_node->right = NULL;
    tree->left = left_node;

    node *right_node = malloc(sizeof(node));
    if (right_node == NULL)
    {
        free_tree(tree);
        return 1;
    }
    right_node->val = 2;
    right_node->left = NULL;
    right_node->right = NULL;
    tree->right = right_node;

    node *right_node2 = malloc(sizeof(node));
    if (right_node2 == NULL)
    {
        free_tree(tree);
        return 1;
    }
    right_node2->val = 3;
    right_node2->left = NULL;
    right_node2->right = NULL;
    right_node->right = right_node2;

    node *left_node_1_2 = malloc(sizeof(node));
    if (left_node_1_2 == NULL)
    {
        free_tree(tree);
        return 1;
    }
    left_node_1_2->val = 4;
    left_node_1_2->left = NULL;
    left_node_1_2->right = NULL;
    right_node2->left = left_node_1_2;

    node *right_node_2_2 = malloc(sizeof(node));
    if (right_node_2_2 == NULL)
    {
        free_tree(tree);
        return 1;
    }
    right_node_2_2->val = 6;
    right_node_2_2->left = NULL;
    right_node_2_2->right = NULL;
    right_node2->right = right_node_2_2;

    print_tree(tree);
    // Tree:
    //  5
    // 1 2
    //    3
    //   4 6

    // In-order DFS: Left → Root → Right
    // 1 -> 5 -> 2 -> 4 -> 3 -> 6

    free_tree(tree);
    printf("\nAfter free: ");
    print_tree(tree);

}


void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }

    // An In-order variant of Depth-First Search (DFS) strategy
    // Only by changing the print order willchange the traversal type
    // This one is Left → Root → Right
    print_tree(root->left);
    printf("%d -> ", root->val);
    print_tree(root->right);
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
