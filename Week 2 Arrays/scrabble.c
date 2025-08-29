#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int calculatePoint(string s);
string toLowerCase(string s);
void printWinner(int point1, int point2);

const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; // a-z

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    // printf("%d-%c", 'a' - 'A', 'a' - 'A');
    // printf("lower: %s", toLowerCase(p1));

    int point1 = calculatePoint(toLowerCase(p1));
    int point2 = calculatePoint(toLowerCase(p2));

    // printf("point1=%i, point2=%i", point1, point2);

    printWinner(point1, point2);

    return 0;
}

int calculatePoint(string s)
{
    int point = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        if (c >= 'a' && c <= 'z')
        {
            int index = s[i] - 97; // starting 'a' to have index 0

            // printf("s[%i]=%c, index=%i, point=%i, ", i, s[i], index, POINTS[index]);

            point += POINTS[index];
            // printf("new point=%i\n", point);
        }
    }

    return point;
}

string toLowerCase(string s)
{
    string lowerS = malloc(strlen(s) + 1);

    for (int i = 0; i < strlen(s); i++)
    {
        // printf("%c\n", s[i]);
        char c = s[i];
        if (c >= 'A' && c <= 'Z')
        {
            int diff = 'a' - 'A'; // 32
            lowerS[i] = s[i] + diff;
        }
        else
        {
            lowerS[i] += s[i];
        }
    }

    // printf("s:%s - lowerS:%s\n", s, lowerS);

    return lowerS;
}

void printWinner(int point1, int point2)
{
    if (point1 > point2)
    {
        printf("Player 1 wins!\n");
    }
    else if (point2 > point1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}