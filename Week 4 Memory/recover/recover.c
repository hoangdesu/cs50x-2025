#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (!card)
    {
        printf("Could not open.\n");
        return 1;
    }

    // printf("uint8_t: %lu", sizeof(uint8_t));

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    // While there's still data left to read from the memory card
    // fread(data, size, number, inptr)
    int buffer_counter = 0;
    int img_ctr = 0;

    FILE *image = NULL;
    char filename[8];

    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // printf("\n-- buffer_counter = %d\n", buffer_counter);
        // printf("buffer = %d\n", *buffer);

        // printf("buffer0: %d\n", buffer[0]);

        // printf("buffer0 hex: %#x\n", buffer[0]);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            printf("\n-- image found! buffer_counter = %d\n", buffer_counter);
            // printf("ah hah!\n");

            // printf("*buffer = %d\n", *buffer);
            // printf("buffer0: %d\n", buffer[0]);
            printf("buffer0 hex: %#x\n", buffer[0]);


            printf("images = %d\n", img_ctr);

            // for (int i = 0; i < 512; i++)
            // {
            //     if (buffer[i])
            // }

            printf("buffer_3 = %#x\n", buffer[3]);

            // close old image
            if (image != NULL)
            {
                fclose(image);
            }

            // create new image
            sprintf(filename, "%03d.jpg", img_ctr);
            image = fopen(filename, "w");

            if (!image)
            {
                printf("Error creating image!\n");
                fclose(card);
                return 2;
            }

            // free(filename);
            // fclose(image);

            img_ctr++;
        }

        if (image != NULL)
        {
            // fwrite(data, size, number, outptr)
            fwrite(buffer, 1, BLOCK_SIZE, image);
        }

        buffer_counter++;
    }

    if (image != NULL)
    {
        fclose(image);
    }

    fclose(card);

    printf("Done!\n");
}