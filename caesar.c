// Caesar cipher
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Signifies an error when user does not input two command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    } 
    
    // Converts argv[1] to an integer and storing it to a variable
    int key = atoi(argv[1]);
    
    // Signifies an error when user does not input a positive integer
    if (key <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;        
    }
    
    // Prompts user to input plaintext
    string pt = get_string("plaintext: ");
    
    printf("ciphertext: ");
    // Converts plaintext to ciphertext
    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        // Keep case of letter
        if (isupper(pt[i]))
        {
            // Get modulo number and add key to appropriate case
            printf("%c", 'A' + (pt[i] - 'A' + key) % 26);
        }
        else if (islower(pt[i]))
        {
            printf("%c", 'a' + (pt[i] - 'a' + key) % 26);
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
