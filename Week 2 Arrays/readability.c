#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// int count_words(string s)
// {
//     int w = 0;
//     int a = strlen(s);
//     for (int i = 0; i < a; i++)
//     {
//         if (s[i] == ' ')
//         {
//             w++;
//         }
//     }
//     return (w + 1);
// }

// int count_letters(string s)
// {
//     int l = 0;
//     int a = strlen(s);
//     for (int i = 0; i < a; i++)
//     {
//         if (isupper(s[i]) || islower(s[i]))
//         {
//             l++;
//         }
//     }
//     return l;
// }

// int count_sentences(string s)
// {
//     int l = 0;
//     int a = strlen(s);
//     for (int i = 0; i < a; i++)
//     {
//         if (s[i] == '.' || s[i] == '!' || s[i] == '?')
//         {
//             l++;
//         }
//     }
//     return l;
// }

int main(void)
{
    string text = get_string("Text: ");

    // string text = "One fish. Two fish. Red fish. Blue fish.";
    // string text = "Would you like them here or there? I would not like them here or there. I
    // would not like them anywhere."; string text = "It was a bright cold day in April, and the
    // clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort
    // to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though
    // not quickly enough to prevent a swirl of gritty dust from entering along with him.";

    int words = 1;
    int sentences = 0;
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        // printf("%c", text[i]);

        char c = text[i];
        if (c == ' ')
            words++;
        else if (c == '.' || c == '?' || c == '!')
            sentences++;
        else if (isalpha(c))
            letters++;
    }

    float avgLetters = (float) letters / (float) words * 100.0;
    float avgSentences = (float) sentences / (float) words * 100.0;

    // Coleman-Liau index formula
    int index = round(0.0588 * avgLetters - 0.296 * avgSentences - 15.8);
    // int index = round(0.0588 * (letters / (float) words * 100.0) - 0.296 * (sentences / (float)
    // words * 100.0) - 15.8);

    // printf("\n words=%i, sentences=%i, letters=%i, index=%i \n", words, sentences, letters,
    // index);

    // int W = count_words(text);
    // int L = count_letters(text);
    // int S = count_sentences(text);

    // printf("\n-----\n W=%i, L=%i, S=%i \n", W, L, S);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}