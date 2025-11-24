#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "hash_table.h"

int hashFunction(const char *name, int tableSize)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *name++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % tableSize;
}

HashTable *createHashTable(int size)
{
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (Node **)calloc(size, sizeof(Node *));
    ht->counts = (int *)calloc(size, sizeof(int));
    return ht;
}

void freeHashTable(HashTable *ht)
{
    int i;
    for (i = 0; i < ht->size; i++)
    {
        Node *current = ht->table[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht->counts);
    free(ht);
}

// Cria um novo nó
Node *createNode(const char *name)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strncpy(newNode->name, name, MAX_NAME - 1);
    newNode->name[MAX_NAME - 1] = '\0';
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}