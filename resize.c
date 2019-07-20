// Resizes a BMP file by the factor inputted on command line
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(argv[1]);

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Variables for new width and height
    int inWidth = bi.biWidth;
    int inHeight = bi.biHeight;
    int outWidth = inWidth * n;
    int outHeight = inHeight * n;

    // Determine padding for scanlines and header files
    int inPadding = (4 - (inWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (outWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Change headers information
    bi.biHeight = outHeight;
    bi.biWidth = outWidth;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * outWidth) + outPadding) * abs(outHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Allocate a memory to store one scanline
    RGBTRIPLE scanline[outWidth * sizeof(RGBTRIPLE)];

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inHeight); i < biHeight; i++)
    {
        // Iterate over pixels in scanline
        for (int j = 0; j < inWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Create a new scanline in a temporary array
            for (int k = 0; k < n; k++)
            {
                scanline[(j * n) + k] = triple;
            }
        }

        // Skip over padding, if any
        fseek(inptr, inPadding, SEEK_CUR);

        // Write the current scanline n times
        for (int j = 0; j < n; j++)
        {
            // write a new scanline once
            fwrite(scanline, sizeof(RGBTRIPLE), outWidth, outptr);

            // Write new padding
            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}
