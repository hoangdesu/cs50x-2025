#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

// Need to also store the key for retrieval
typedef struct {
    char *key;
    char *value;
} Record;


void print(Record *hashtable[])
{
    printf("\nHashtable:\n");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (hashtable[i] != NULL)
            printf("%d. key: %s - value: %s\n", i, hashtable[i]->key, hashtable[i]->value);
        else
            printf("%d. (null)\n", i);
    }
    printf("\n");
}


int hash(char *key)
{
    int i = (key[0] - 'A') % MAX_SIZE;
    // printf("- hashing key=%s - i=%d\n", key, i);
    return i;
}


// Insert function with Linear Probing collision detection
void insert(Record *hashtable[], char *key, char* value)
{
    int index = hash(key);
    int start = index;

    while (hashtable[index] != NULL && hashtable[index]->key != NULL)
    {
        // Update existing key
        if (strcmp(hashtable[index]->key, key) == 0)
        {
            hashtable[index]->value = value;
            return;
        }

        // otherwise, keep going to the next available spot
        index = (index + 1) % MAX_SIZE;

        // if we wrap around back to where we started, it means the hashtable is full
        if (index == start)
        {
            printf("The hashtable is full! Cannot insert new record %s: %s\n", key, value);
            return;
        }
    }

    // if record is not yet in the hashtable, create a new record and add to the current index
    Record *newRecord = malloc(sizeof(Record));
    newRecord->key = key;
    newRecord->value = value;

    hashtable[index] = newRecord;
}


char *get(Record *hashtable[], char *key)
{
    int index = hash(key);
    int start = index;

    while (hashtable[index] != NULL)
    {
        // return the value with matching key
        if (strcmp(hashtable[index]->key, key) == 0)
        {
            return hashtable[index]->value;
        }

        // otherwise, keep on checking next index
        index = (index + 1) % MAX_SIZE;

        // back to where we started -> not found
        if (index == start) break;
    }

    return NULL;
}


int main(void)
{
    Record *hashtable[MAX_SIZE] = { NULL };

    print(hashtable);

    insert(hashtable, "Brian", "Nguyen"); // should be put at index 1
    insert(hashtable, "Hoang", "hoangdesu");

    insert(hashtable, "Zed", "best ASSasin");
    insert(hashtable, "Zed", "FAKER WHAT WAS THAT???"); // same key: should overwrite last value

    insert(hashtable, "Ziggs", "bing bong kaboom"); // collision: should move to next available index
    insert(hashtable, "Zoe", "one shot mtfk"); // another collision: should move to next available index
    
    insert(hashtable, "Jinx", "my first ADC"); // should be put at last index
    insert(hashtable, "Jihn", "anh Tu"); // collision: should wrap around the array

    // just filling up the hashtable
    insert(hashtable, "A", "A");
    insert(hashtable, "B", "B");
    insert(hashtable, "C", "C");
    insert(hashtable, "D", "D"); // full -> will NOT be inserted

    print(hashtable);

    // getting value from a key
    char *keys[] = { "Brian", "Zed", "Ahri", "Jinx", "Leblanc", "Jhin", "Ziggs", "Zoe" };
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        printf("> GET %s: %s\n", keys[i], get(hashtable, keys[i]));
    }
}