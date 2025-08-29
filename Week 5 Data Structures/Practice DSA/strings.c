#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Strings in C using char pointer vs char array
    char *name;

    // free to reassign, since we're simply just pointing it to another char array
    name = "hi";
    name = "heyy";

    printf("name = %s\n", name);

    char username[10];

    // char array is fixed, strings can't be re-assigned. Have to use strcpy function
    strcpy(username, "doroke");
    strcpy(username, "hoangdesu");
    // strcpy(username, "hoangdesuhahahahahahaha"); // overflow buffer

    printf("username = %s\n", username);

    return 0;
}