// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Counter for words stored from dictionary
unsigned int words = 0;

// Hashes word to a number between 0 and N
// From: https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    for (const char *c = word; *c != '\0'; c++)
    {
        hash = ((hash << 5) + hash) + tolower(*c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (true)
    {
        // Malloc a node * for each new word
        node *ptr = malloc(sizeof(node));
        // Check that enough memory is available
        if (ptr == NULL)
        {
            return false;
        }

        // Scans a word from the dictionary and saves it to ptr->word
        fscanf(file, "%s", ptr->word);
        ptr->next = NULL;
        if (feof(file))
        {
            free(ptr);
            break;
        }

        words++;
        int hashCode = hash(ptr->word);

        if (hashtable[hashCode] != NULL)
        {
            // Points ptr->next to the pointer the head of the list is pointing to (first node)
            ptr->next = hashtable[hashCode];
            // Safely re-assign the head pointer to the new node
            hashtable[hashCode] = ptr;             
        }
        // Points the head of the list to the new node
        hashtable[hashCode] = ptr;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (words > 0)
    {
        return words;
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Set cursor to head of the list where the word is linked
    node *cursor = hashtable[hash(word)];
    
    while (cursor != NULL)
    {
        // Compare the words
        int compare = strcasecmp(cursor->word, word);
        
        // The words match if strcasecmp returns 0
        if (compare == 0)
        {
            return true;
        }
        
        // Cursor points to where cursor->next is pointing to
        // Simply moving to the next location
        cursor = cursor->next;
    }
    
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor1 = NULL;
    node *temp = NULL;
    
    for (int i = 0; i < N; i++)
    {
        cursor1 = hashtable[i];
        
        while (cursor1 != NULL)
        {
            temp = cursor1;
            cursor1 = cursor1->next;
            free(temp);
        }
    }
    return true;
}

