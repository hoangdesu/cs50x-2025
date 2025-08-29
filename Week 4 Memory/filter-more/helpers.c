#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
            int r = 0;
            int g = 0;
            int b = 0;

            int elements = 0;

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    int gx_kernel[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gy_kernel[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel
            int rx = 0;
            int gx = 0;
            int bx = 0;

            int ry = 0;
            int gy = 0;
            int by = 0;

            int gIndex = 0; // supposed to go from 0 -> 8

            for (int y = i - 1; y <= i + 1; y++)
            {
                for (int x = j - 1; x <= j + 1; x++)
                {
                    // skipping the edges
                    // if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    if (y < 0 || y >= height || x < 0 || x >= width)
                    {
                        ++gIndex;
                        continue;
                    }

                    // actually calculate the values for R, G, B
                    rx += image[y][x].rgbtRed * gx_kernel[gIndex];
                    gx += image[y][x].rgbtGreen * gx_kernel[gIndex];
                    bx += image[y][x].rgbtBlue * gx_kernel[gIndex];

                    ry += image[y][x].rgbtRed * gy_kernel[gIndex];
                    gy += image[y][x].rgbtGreen * gy_kernel[gIndex];
                    by += image[y][x].rgbtBlue * gy_kernel[gIndex];

                    ++gIndex;

                    printf("i=%d, j=%d, gIndex=%d\n", i, j, gIndex);
                }
            }

            // calculate combined Gx and Gy
            float finalR = round(sqrt(pow(rx, 2) + pow(ry, 2)));
            float finalG = round(sqrt(pow(gx, 2) + pow(gy, 2)));
            float finalB = round(sqrt(pow(bx, 2) + pow(by, 2)));

            // capped values at 0 - 255
            finalR = finalR > 255 ? 255 : (finalR < 0 ? 0 : finalR);
            finalG = finalG > 255 ? 255 : (finalG < 0 ? 0 : finalG);
            finalB = finalB > 255 ? 255 : (finalB < 0 ? 0 : finalB);

            // write to copied image
            copy[i][j].rgbtRed = (BYTE) finalR;
            copy[i][j].rgbtGreen = (BYTE) finalG;
            copy[i][j].rgbtBlue = (BYTE) finalB;
        }
    }

    // copy over
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}