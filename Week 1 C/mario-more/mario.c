#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = get_int("Height: ");

    while (!(height >= 1 && height <= 8))
    {
        height = get_int("Height: ");
    }

    int space = height - 1;

    for (int row = 1; row <= height; row++)
    {
        for (int s = 0; s < space; s++)
        {
            printf(" ");
        }

        for (int c = 1; c <= row; c++)
        {
            printf("#");
        }

        printf("  ");

        for (int c = 1; c <= row; c++)
        {
            printf("#");
        }

        space--;
        printf("\n");
    }
}

// Height: 4
//    #  #
//   ##  ##
//  ###  ###
// ####  ####