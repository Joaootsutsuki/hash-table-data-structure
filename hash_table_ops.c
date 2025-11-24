#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

void insert(HashTable *ht, const char *name)
{
    int index = hashFunction(name, ht->size);
    Node *newNode = createNode(name);

    if (ht->table[index] == NULL)
    {
        ht->table[index] = newNode;
    }
    else
    {
        // Insere no início da lista
        newNode->next = ht->table[index];
        ht->table[index]->prev = newNode;
        ht->table[index] = newNode;
    }

    ht->counts[index]++;
}

// Busca um nome na tabela hash
Node *search(HashTable *ht, const char *name)
{
    int index = hashFunction(name, ht->size);
    Node *current = ht->table[index];

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Remove um nome da tabela hash
int removeElement(HashTable *ht, const char *name)
{
    int index = hashFunction(name, ht->size);
    Node *current = ht->table[index];

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            else
            {
                ht->table[index] = current->next;
            }

            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }

            free(current);
            ht->counts[index]--;
            return 1;
        }
        current = current->next;
    }

    return 0;
}