#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

// Need to also store the key for retrieval
typedef struct Record_t {
    char *key;
    char *value;
    struct Record_t *next;
} Record;


void print(Record *hashtable[])
{
    printf("\nHashtable:\n");

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (hashtable[i] == NULL) {
            printf("%d. (null)\n", i);

        } else {
            printf("%d. ", i);
            // printf("%d. %s: %s\n", i, hashtable[i]->key, hashtable[i]->value);
            
            int j = 1;
            Record *ptr = hashtable[i];
            while (ptr != NULL)
            {
                printf("[%d] %s: %s", j, ptr->key, ptr->value);

                if (ptr->next != NULL)
                {
                    printf(" -> ");
                }

                ptr = ptr->next;
                j++;

            }
            printf("\n");
        }
    }

    printf("\n");
}


int hash(char *key)
{
    int i = (key[0] - 'A') % MAX_SIZE;
    // printf("- hashing key=%s - i=%d\n", key, i);
    return i;
}


void insert(Record *hashtable[], char *key, char *value)
{
    int i = hash(key);

    // Record *testRecord = malloc(sizeof(Record));
    // testRecord->key = "TEST KEY";
    // testRecord->value = "TEST VALUE";
    // testRecord->next = NULL;

    Record *newRecord = malloc(sizeof(Record));
    newRecord->key = key;
    newRecord->value = value;
    newRecord->next = NULL;

    // if the slot is currently empty
    if (hashtable[i] == NULL)
    {
        // simply add it to the hashtable
        hashtable[i] = newRecord;
    } 
    // something is already here
    else
    {
        // update the current value if the key is the same
        if (strcmp(key, hashtable[i]->key) == 0)
        {
            hashtable[i]->value = value;
        }
        // point the new record to the current record, insert it to the hashtable as the first node (head) -> make it a linked list
        else
        {
            newRecord->next = hashtable[i];
            hashtable[i]= newRecord;
        }        
    }

}

char *get(Record *hashtable[], char *key)
{
    int i = hash(key);

    Record *ptr = hashtable[i];
    while (ptr != NULL)
    {
        if (strcmp(key, ptr->key) == 0)
        {
            return ptr->value;
        }

        ptr = ptr->next;
    }

    return NULL;
}


int main(void)
{
    Record *hashtable[MAX_SIZE] = { NULL };

    print(hashtable);

    // hashtable.insert(key, val)

    insert(hashtable, "Brian", "Nguyen"); // should be put at index 1
    insert(hashtable, "Hoang", "hoangdesu");

    insert(hashtable, "Zed", "best ASSasin");
    insert(hashtable, "Zed", "FAKER WHAT WAS THAT???"); // same key: should overwrite last value

    insert(hashtable, "Ziggs", "bing bong kaboom"); // collision: should be inserted before Zed (first node in the linked list)
    insert(hashtable, "Zoe", "one shot mtfk"); // another collision: should be before Ziggs => should be: Zoe -> Ziggs -> Zed
    
    insert(hashtable, "Jinx", "my first ADC"); // should be put at last index
    insert(hashtable, "Jhin", "anh Tu"); // collision: should wrap around the array

    // this version of hashtable has a lot more spaces than 10 slots
    insert(hashtable, "A", "A");
    insert(hashtable, "B", "B");
    insert(hashtable, "C", "C");
    insert(hashtable, "D", "D");
    insert(hashtable, "E", "E");
    insert(hashtable, "Fizz", "nhay mua tung tang");

    print(hashtable);

    char *keys[] = { "Brian", "Zed", "Ahri", "Jinx", "Leblanc", "Jhin", "Ziggs", "Zoe", "Fizz" };
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        printf("> GET %s: %s\n", keys[i], get(hashtable, keys[i]));
    }
}