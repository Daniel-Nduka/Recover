#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// number of bytes in jpeg
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Open memory card
    if (argc != 2)
    {
        printf("not valid\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("could not open file\n");
        return 1;
    }

    // create an image count
    int count_image = 0;

    // create a buffer for the output file
    char *filename = malloc(8 * sizeof(char));

    // create output file
    FILE *img = NULL;

    // create an unsigned char buffer
    uint8_t buffer[BLOCK_SIZE];

    // check for the begining of Jpegs.
    while (fread(buffer, sizeof(char), BLOCK_SIZE, raw_file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // print jpep numbers into file name
            sprintf(filename, "%03i.jpg", count_image);

            // Opening the filename in write mode
            img = fopen(filename, "w");
            count_image++;
        }
        if (img != NULL)
        {
            fwrite(buffer, sizeof(char), BLOCK_SIZE, img);
        }
    }

    // free the pointer and close the file pointers
    free(filename);
    fclose(raw_file);
    fclose(img);
    return 0;
}
