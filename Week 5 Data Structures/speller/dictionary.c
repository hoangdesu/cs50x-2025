// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct _node
{
    char word[LENGTH + 1];
    struct _node *next;
} node;

// The number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];
int dict_size = 0;

// helper function
void print_table()
{
    for (int i = 0; i < N; i++)
    {
        printf("\n\n\ttable[%d]:\n", i);

        node *tmp = table[i];

        int word_count = 0;
        while (tmp != NULL)
        {
            printf("%s", tmp->word);
            if (tmp->next != NULL)
            {
                printf(" -> ");
            }
            tmp = tmp->next;
            word_count++;
        }
        printf("\n\t[Word counts for table[%d]: %d]\n", i, word_count);
    }
    printf("\n");
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';

    int total = 2602; // my birthday :3
    for (int i = 0; word[i] != '\0'; i++)
    {
        total += tolower(word[i]);
    }

    return total % N;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i = hash(word);
    node *tmp = table[i];
    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
            return true;
        tmp = tmp->next;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        printf("Error openning dictionary file\n");
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1]; // buffer for each word

    // fscanf(source, "%s", word);
    // printf("- word = %s\n", word);

    // testing: all the nodes in the table are initialized to null
    // for (int i = 0; i < 26; i++)
    // {
    //     printf("...table[%d]: %s\n", i, table[i]->word);
    // }
    // return false;

    // Add each word to the hash table
    while (fscanf(source, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));

        // malloc can potentially fail
        if (new_node == NULL)
        {
            return false;
        }

        // setting the values for each node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hashing the word
        int word_hash = hash(word);
        // printf("- word = %s, hash: %d\n", word, word_hash);

        // Insert node into hash table at that location
        // - recall that hash table is an array of linked lists
        // - insert new node at the beginning of the linked list

        if (table[word_hash] == NULL)
        {
            table[word_hash] = new_node;
        }
        else
        {
            // first, set the next pointer of new node to point at the current head of the current
            // linked list
            new_node->next = table[word_hash];

            // point the head to new node
            table[word_hash] = new_node;
        }

        // once a word has been loaded into memory, increase the dictionary's word count
        dict_size++;
    }

    // Close the dictionary file
    fclose(source);

    // testing: printing out the first node of each slot in table
    // for (int i = 0; i < 26; i++)
    // {
    //     printf("table[%d]: %s\n", i, table[i]->word);
    // }

    // print_table();

    // return false;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *tmp = ptr;
            ptr = ptr->next; // move ahead first
            free(tmp);       // then free safely
        }
    }

    return true;
}
