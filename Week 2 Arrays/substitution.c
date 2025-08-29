#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // argc = argument count (int)
    // argv = argument values (string array)
    // printf("argc=%i, argv[0]=%s, argv[1]=%s\n", argc, argv[0], argv[1]);

    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // having a key, not sure if it's valid yet
    string key = argv[1];

    // handles invalid characters in key
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalnum(key[i]))
        {
            printf("Invalid character in key\n");
            return 1;
        }
    }

    // handles duplicated characters in key
    // using an array like a hashmap
    char seenChar[26];

    for (int i = 0; key[i] != '\0'; i++)
    {
        char lowerChar = tolower(key[i]);
        int charIndex = lowerChar - 'a';
        // printf("%i: %c, charIndex=%i, seenChar[i]=%c, isalnum(seenChar[i])=%i \n", i, lowerChar, charIndex, seenChar[i], isalnum(seenChar[i]));

        // no value in array -> allocate
        if (isalnum(seenChar[charIndex]) == 0)
        {
            seenChar[charIndex] = lowerChar;
        }
        else
        {
            printf("Duplicated keys\n");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");

    string cipher = encrypt(plaintext, key);
    printf("ciphertext: %s\n", cipher);

    free(cipher); // Free allocated memory

    return 0;
}

string encrypt(string plaintext, string key)
{
    // ind: 0123456789...
    // abc: ABCDEFGHIJKLMNOPQRSTUVWXYZ
    // key: NQXPOMAFTRHLZGECYJIUWSKDVB

    // ex: HELLO
    // ->: FOLLE

    // string cipher = malloc(strlen(plaintext) + 1);

    // strcpy(cipher, plaintext);
    // printf("cipher: %s, len: %lu", cipher, strlen(cipher));
    // for (int i = 0; i < strlen(cipher); i++)
    // {
    //     printf("- %i:%c\n", i, cipher[i]);
    // }

    // char cipherArr[strlen(plaintext) + 1]; // this doesnt work with the check50. The local array will be destroyed

    // int len = sizeof(cipherArr) / sizeof(char);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%i=%c\n", i, cipherArr[i]);
    // }

    // for (int i = 0; i < strlen(plaintext); i++)
    // {
    //     char c = plaintext[i];
    //     if (c >= 65 && c <= 90)
    //     {
    //         int index = c - 'A';
    //         cipherArr[i] = key[index];
    //     }
    //     else if (c >= 97 && c <= 122)
    //     {
    //         int index = c - 'a';
    //         cipherArr[i] = key[index];
    //     }
    //     else
    //     {
    //         cipherArr[i] = plaintext[i];
    //     }
    // }

    // string s = "ogstr";

    // string copy = malloc(strlen(s) + 1); // +1 for null terminator
    // if (!copy) return "";

    // strcpy(copy, s);

    // printf("Original: %s\n", s);
    // printf("Copy: %s\n", copy);

    // free(copy);

    // cipherArr[strlen(plaintext)] = '\0';

    // string cipher = cipherArr;

    // got problem with memory allocation. redoing...
    int length = strlen(plaintext);

    char *cipherArr = malloc(length + 1);
    if (!cipherArr)
        return NULL; // Handle allocation failure

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char c = plaintext[i];
        if (isupper(c))
        {
            int index = c - 'A';
            cipherArr[i] = toupper(key[index]);
        }
        else if (islower(c))
        {
            int index = c - 'a';
            cipherArr[i] = tolower(key[index]);
        }
        else
        {
            cipherArr[i] = plaintext[i];
        }
    }

    cipherArr[length] = '\0'; // Null-terminate the string

    return cipherArr;
}