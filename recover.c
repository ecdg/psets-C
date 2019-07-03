// Recovers JPEGs from a forensic image
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }
    
    argv[1] = memfile;
    
    // Open memorycard file
    FILE *file = fopen(memfile, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", memfile);
        return 2;
    }

    // Global data we need to proceed
    unsigned char *buffer = malloc(512);
    char filename[9];
    int counter = 0;
    FILE *img = NULL;

    while (fread(buffer, 512, 1, file) == 1)
    {
        // Check for JPG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPG is already open, close it to start the next one
            if (counter > 0)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");

            // Check if JPG file was created, if not, return error
            if (img == NULL)
            {
                fclose(file);
                free(buffer);
                fprintf(stderr, "Could not create %s", filename);
                return 3;
            }
            //Increase counter for next JPG
            counter++;
        }

        if (!counter)
        {
            continue;
        }

        fwrite(buffer, 512, 1, img);
    }

    // When memorycard ends, close all files
    fclose(file);
    fclose(img);
    free(buffer);
    return 0;
}
