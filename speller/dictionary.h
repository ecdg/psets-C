// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Represents number of buckets in a hash table
#define N 70000

// Prototypes
bool load(const char *dictionary);
unsigned int size(void);
bool check(const char *word);
bool unload(void);

#endif // DICTIONARY_H
