// Vigenere cipher
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{    
    // Signifies an error when user does not input two command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        
        return 1;
    }
    else 
    {
        /* Iterates over each char and sends an error when programs receives 
         * a non-alphabetical character */
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./vigenere keyword\n");
                
                return 1;
            }    
        }
    }
    
    // Store key as string and get length
    string key = argv[1];
    int keyLen = strlen(key);
    
    // Get text to encode
    string pt = get_string("plaintext: ");
    
    printf("ciphertext: ");
    // Loop through text
    for (int i = 0, j = 0, n = strlen(pt); i < n; i++)
    {            
        // Get key for this letter
        int letterKey = tolower(key[j % keyLen]) - 'a';
        
        // Keep case of letter
        if (isupper(pt[i]))
        {
            // Get modulo number and add to appropriate case
            printf("%c", 'A' + (pt[i] - 'A' + letterKey) % 26);
            
            // Only increment j when used
            j++;
        }
        else if (islower(pt[i]))
        {
            printf("%c", 'a' + (pt[i] - 'a' + letterKey) % 26);
            j++;
        }
        else
        {
            // Return unchanged
            printf("%c", pt[i]);
        }
    }
    
    printf("\n");
    
    return 0;
}
