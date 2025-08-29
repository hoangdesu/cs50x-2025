#include <cs50.h> // custom header file
#include <stdio.h>

int main(void)
{
    // Getting user inputs
    string name = get_string("What's your name? ");

    // Say hello to name
    printf("hello, %s\n", name);
}