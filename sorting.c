#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h" 

// Função de partição para o quicksort
int partition(Node **arr, int low, int high)
{
    char *pivot = arr[high]->name;
    int i = low - 1;
    int j;

    for (j = low; j < high; j++)
    {
        if (strcmp(arr[j]->name, pivot) < 0)
        {
            i++;
            Node *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Node *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Implementação do quicksort
void quicksort(Node **arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Ordena os elementos de uma chave específica
void sortKey(HashTable *ht, int key)
{
    if (key < 0 || key >= ht->size || ht->counts[key] == 0)
    {
        return;
    }

    // Cria array temporário para ordenação
    Node **arr = (Node **)malloc(ht->counts[key] * sizeof(Node *));
    Node *current = ht->table[key];
    int i = 0;

    while (current != NULL)
    {
        arr[i++] = current;
        current = current->next;
    }

    // Ordena usando quicksort
    quicksort(arr, 0, ht->counts[key] - 1);

    // Reconstrói a lista encadeada ordenada
    ht->table[key] = arr[0];
    arr[0]->prev = NULL;

    for (i = 0; i < ht->counts[key] - 1; i++)
    {
        arr[i]->next = arr[i + 1];
        arr[i + 1]->prev = arr[i];
    }

    arr[ht->counts[key] - 1]->next = NULL;

    free(arr);
}