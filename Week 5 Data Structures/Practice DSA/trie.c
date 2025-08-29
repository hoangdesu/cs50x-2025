// Trie: 
//     - stands for re-TRIE-val, also called prefix tree
//     - used for retrieving things
//     - can efficiently check whether a particular string is in a set of strings
//     - lesson 1: https://www.youtube.com/watch?v=3CbFFVHQrk4
//     - lesson 2: https://www.youtube.com/watch?v=NDfAYZCHstI


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define NUM_CHARS 256
// support 256 ASCII characters
// can just support 26 letters or 10 digits, but need to perform bound checking


typedef struct _trie_node 
{
    struct _trie_node *children[NUM_CHARS];
    // this array acts like a lookup table
    // no need to search thru the whole array, just need to use the position of the char in the array
    // trade space for speed

    bool terminal;
} trie_node;


trie_node* create_node()
{
    trie_node *new_node = malloc(sizeof *new_node);

    // initialize default values for new node
    for (int i = 0; i < NUM_CHARS; i++) 
    {
        new_node->children[i] = NULL;
    }
    new_node->terminal = false;

    return new_node;
}


// value of root might have to be changed, so we're taking in a double pointer
bool trie_insert(trie_node **root, char *signed_text)
{
    if (*root == NULL)
    {
        *root = create_node();
    }

    // when a char is passed into a function, it will normally be passed as signed
    // prevents negative index for lookup table
    unsigned char *text = (unsigned char *) signed_text;

    trie_node *tmp = *root;
    for (int i = 0; i < strlen(signed_text); i++)
    {
        // if the character has not been in the lookup table, create a new node for it
        if (tmp->children[text[i]] == NULL)
        {
            tmp->children[text[i]] = create_node();
        }

        // move the temp pointer to next child node
        tmp = tmp->children[text[i]];
    }

    if (tmp->terminal)
    {
        return false;
    } 
    else {
        tmp->terminal = true;
        return true;
    }
}

void recursive_print_trie(trie_node *node, unsigned char *prefix, int length)
{
    // why 2? need 1 space for new char, and 1 extra space for NUlL character
    unsigned char new_prefix[length + 2];

    // The memcpy() function in C copies the specified number of bytes from one memory location to another memory location regardless of the type of data stored
    // copy all characters over to new prefix, leaving 2 last space empty
    memcpy(new_prefix, prefix, length);
    new_prefix[length + 1] = 0;

    if (node->terminal)
    {
        printf("Hit terminal. Final word: %s\n", prefix);
    }

    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (node->children[i] != NULL)
        {
            new_prefix[length] = i;
            recursive_print_trie(node->children[i], new_prefix, length + 1);
        }
    }
}


void print_trie(trie_node *root)
{
    if (root == NULL)
    {
        printf("Trie empty\n");
        return;
    }

    recursive_print_trie(root, NULL, 0);
}


// very similar to insert, instead we look up for a value
bool search_trie(trie_node *root, char *signed_text)
{
    unsigned char *text = (unsigned char *) signed_text;
    trie_node *tmp = root;

    for (int i = 0; i < strlen(signed_text); i++)
    {
        if (tmp->children[text[i]] == NULL)
        {
            return false;
        }

        // move the temp pointer to next child node
        tmp = tmp->children[text[i]];
    }

    // can simply return if the current node is the end
    return tmp->terminal;
}


bool delete_str(trie_node **root, char *signed_text)
{
    unsigned char *text = (unsigned char *) signed_text;

    // TODO


}


int main() 
{
    trie_node *root = NULL;

    trie_insert(&root, "cat");
    trie_insert(&root, "kit");
    trie_insert(&root, "cattle");
    trie_insert(&root, "zoe");
    trie_insert(&root, "kitty");
    trie_insert(&root, "ahri");
    trie_insert(&root, "car");
    trie_insert(&root, "zed");
    trie_insert(&root, "cattyhello");

    // all the words are gonna be sorted alphabetically
    print_trie(root);

    char *test_cases[] = {"cat", "zed", "car", "cattle", "syndra", "leblanc", "kitty", "kitt"};
    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++)
    {
        printf("Searching for %s: %d\n", test_cases[i], search_trie(root, test_cases[i]));
    }



    return 0;
}