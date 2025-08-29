#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// If this hashtable declared globally (outside main) without initialized, this is fine
// => Because Global variables in C are automatically zero-initialized (all elements become NULL).
// But if it's inside main, it has to be init to {NULL}

// char *hashtable[MAX_SIZE];

void print(char *hashtable[])
{
    printf("\nHashtable:\n");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("%d. %s\n", i, hashtable[i]);
    }
    printf("\n");
}

// A simple hash function that has NO collision detection
int hash(char *s)
{
    return (s[0] - 'A') % MAX_SIZE;
}

void insert(char *hashtable[], char *key, char *value)
{
    int index = hash(key);
    hashtable[index] = value;
    printf("inserting %s: %s at %d\n", key, value, index);
}

char *get(char *hashtable[], char *key)
{
    int index = hash(key);
    return hashtable[index];
}

int main(void)
{
    char *hashtable[MAX_SIZE] = {NULL}; // array has to be init to {NULL}

    print(hashtable);

    printf("Brian: %d\n", hash("Brian"));
    printf("Cun: %d\n", hash("Cun"));
    printf("Zed: %d\n", hash("Zed"));
    printf("Bro: %d\n", hash("Bro")); // collision

    insert(hashtable, "Brian", "Nguyen");
    insert(hashtable, "Zed", "the Master of Shadows");
    insert(hashtable, "Bro", "Mance");

    printf("get Brian: %s\n", get(hashtable, "Brian"));
    printf("get Zed: %s\n", get(hashtable, "Zed"));
    printf("get Ahri: %s\n", get(hashtable, "Ahri"));

    print(hashtable);
}
