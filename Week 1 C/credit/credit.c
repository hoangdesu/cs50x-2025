#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DIGITS 16

int main(void)
{
    // string card = get_string("Number: ");
    // printf("%s\n", card);

    long number = get_long("Number: ");
    // printf("%ld\n", number);

    char card[MAX_DIGITS + sizeof(char)];
    sprintf(card, "%ld", number);

    // printf("%s - %lu - %lu\n", card, sizeof(card), sizeof(card[0]));

    // for (int i = 0; i < sizeof(card); i++)
    // {
    //     printf("%d: %c\n",i, card[i]);
    // }

    // card[15] = '\0';
    // printf("Last char: %c", card[sizeof(card) - 1]);

    // printf("\nis 1 digit: %d - is last digit: %d", isdigit(card[1]), isdigit(card[15]));

    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    // int i = sizeof(card) - 1;
    // while (i >= 0)
    // {
    //     printf("i=%d, num=%c", i, card[i]);
    //     if (isdigit(card[i]) != 0)
    //     {
    //         printf("- is digit");
    //     }

    //     printf("\n");

    //     i--;
    // }

    // while (!isdigit(card[i]))
    // {
    //     i--;
    // }

    // starting digit: second-to-last
    // i--;
    // i++;

    // printf("\nstarting digit=%c, i=%d\n", card[i], i);

    // int sum = 0;
    // bool doubled = false;

    // while (i >= 0)
    // {
    //     if (isdigit(card[i]))
    //     {
    //         // if (doubled)
    //         // {
    //         //     sum += atoi(card[i]) * 2;
    //         // }
    //         // else
    //         // {
    //         //     sum += atoi(card[i]);
    //         // }

    //         // printf("i=%d - Char %c: Ascii %d - atoi: %d - ascii to num: %d\n", i, card[i], card[i], atoi(&card[i]), card[i]-48);

    //         int value = (card[i] - 48); // converting from char representation of number to its value
    //         printf("i=%d, value = %d\n", i, value);

    //         // if (doubled)
    //         // {
    //         //     doubledSum += value * 2;
    //         // }
    //         // else
    //         // {
    //         //     normalSum += value;
    //         // }

    //         // doubled = !doubled;
    //     }

    //     i--; // decrease index to head
    // }

    // printf("doubled sum=%d - normal sum=%d\n", doubledSum, normalSum);

    int sum = 0;
    for (int i = strlen(card) - 2; i >= 0; i -= 2)
    {
        // printf("i=%d, char=%c\n", i, card[i]);
        int value = (card[i] - 48);
        // printf("value=%d\n", value);
        // sum += (value * 2);

        value *= 2;

        if (value > 9)
        {
            int firstDigit = value / 10;
            int secondDigit = value % 10;

            sum += (firstDigit + secondDigit);
        }
        else
        {
            sum += value;
        }
    }

    // printf("sum1=%d\n", sum);

    // printf("%d, %d", 12/10, 12%10);

    for (int i = strlen(card) - 1; i >= 0; i -= 2)
    {
        int value = (card[i] - 48);
        sum += value;
    }

    // printf("sum2=%d\n", sum);

    int lastDigit = sum % 10;

    if (lastDigit != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // printf("valid\n");

        string name = "";

        // switch (card[0])
        // {
        //     // All American Express numbers start with 34 or 37;
        //     case '3':
        //         name = "AMEX";
        //         break;
        //     case '4':
        //         name = "VISA";
        //         break;
        //     case '5':
        //         name = "MASTERCARD";
        //         break;
        // }

        // All American Express numbers start with 34 or 37;
        if (card[0] == '3' && strlen(card) == 15)
        {
            if (card[1] == '4' || card[1] == '7')
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // most MasterCard numbers start with 51, 52, 53, 54, or 55
        else if (card[0] == '5' && strlen(card) == 16)
        {
            if (card[1] == '1' || card[1] == '2' || card[1] == '3' || card[1] == '4' || card[1] == '5')
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (card[0] == '4' && (strlen(card) == 13 || strlen(card) == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

// 4003600000000014