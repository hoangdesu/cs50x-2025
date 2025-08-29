#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // printf("Applying grayscale filter\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("height=%d, width=%d, blue=%d\n", height, width,
            // image[height][width].rgbtBlue);

            // image[i][j].rgbtBlue = 255;

            // image[i][j].rgbtBlue *= 1.5;
            // image[i][j].rgbtGreen *= 1.2;
            // image[i][j].rgbtRed *= 1.5;

            // printf("blue=%u, green=%u, red=%u\n", image[i][j].rgbtBlue, image[i][j].rgbtGreen,
            // image[i][j].rgbtRed);

            int avg =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // printf("%u\n", avg);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

            // printf("%d\n", avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
            //                 .189 * image[i][j].rgbtBlue);
            // int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
            //                   .168 * image[i][j].rgbtBlue);
            // int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
            //                  .131 * image[i][j].rgbtBlue);

            // printf("sepiaRed=%u, sepiaGreen=%u, sepiaBlue=%u\n", sepiaRed, sepiaGreen,
            // sepiaBlue);

            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            int k = width - 1 - j;
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // int y = i > 0 ? i - 1 : 0;
            // int x = j > 0 ? j - 1 : 0;

            // int yEnd = (i == height - 1) ? i : i + 1;
            // int xEnd = (j == width - 1) ? j : j + 1;

            int elements = 0;

            int r = 0;
            int g = 0;
            int b = 0;

            // for (; y <= yEnd; y++) {
            //     for (x; x <= xEnd; x++) {
            //         b += image[x][y].rgbtBlue;
            //         g += image[x][y].rgbtGreen;
            //         r += image[x][y].rgbtRed;
            //         ++elements;

            //         printf("i=%d, j=%d, y=%d, yEnd=%d, x=%d, xEnd=%d, elements=%d\n", i, j, y,
            //         yEnd, x, xEnd, elements);
            //     }
            // }

            int yStart = (i == 0) ? 0 : i - 1;
            int yEnd = (i == height - 1) ? i : i + 1;

            int xStart = (j == 0) ? 0 : j - 1;
            int xEnd = (j == width - 1) ? j : j + 1;

            for (int y = yStart; y <= yEnd; y++)
            {
                for (int x = xStart; x <= xEnd; x++)
                {
                    b += image[y][x].rgbtBlue;
                    g += image[y][x].rgbtGreen;
                    r += image[y][x].rgbtRed;
                    ++elements;
                }
            }

            tempImage[i][j].rgbtBlue = round((float) b / (float) elements);
            tempImage[i][j].rgbtGreen = round((float) g / (float) elements);
            tempImage[i][j].rgbtRed = round((float) r / (float) elements);
        }
    }

    // copy over
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempImage[i][j];
        }
    }

    return;
}