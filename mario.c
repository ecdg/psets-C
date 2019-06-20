// One-sided pyramid
// User decides how tall a pyramid should be
// From levels 1 to 8

#include <cs50.h>
#include <stdio.h>

int h;

int main(void)
{
    // User prompts the height
    do
    {
        h = get_int("Select the pyramid's height from levels 1 to 8: ");
    }
    while (h < 1 || h > 8);

    // Generate and draw the half-pyramid
    for (int i = 0; i < h; i++)
    {
        // For spaces and hashes
        for (int j = 1; j <= h; j++)
        {
            if (i + j < h)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        // Prints a new line with each iteration
        printf("\n");
    }
}

