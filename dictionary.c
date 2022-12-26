// Implements a dictionary's functionality
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// COUNTER
int count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash word to obtain hash value
    int destination = hash(word);

    //compares word to respective indexed linked list
    node *m = table[destination];

    while (m != NULL)
    {
        if (strcasecmp(word, m -> word) == 0)
        {
            return true;
        }
        else
        {
            m = m -> next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //returns ascii value of first character
    int start = toupper(word[0]);
    int location = start - 65;
    return location;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    //memory to read into
    char buff [LENGTH + 1];

    //read strings from file one at a time
    while (fscanf(file, "%s", buff) != EOF)
    {
        //create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n -> word, buff);
        n -> next = NULL;

        //hash word to obtain a hash value
        int destination = hash(buff);

        //insert node into hash table at that location
        if (table[destination] == NULL)
        {
            table[destination] = n;
        }
        else
        {
            n -> next = table[destination];
            table[destination] = n;
        }
        //what about repeated words
        count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //creates 2 nodes
    node *tmp = NULL;
    node *current = NULL;

    //for the size of the table array
    for (int x = 0; x < N; x++)
    {
        current = table[x];

        while (current != NULL)
        {
            tmp = current -> next;
            free(current);
            current = tmp;
        }
    }
    return true;
}
