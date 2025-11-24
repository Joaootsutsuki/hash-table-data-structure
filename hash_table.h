#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 53
#define MAX_NAME 100

// Estrutura do nó da lista duplamente encadeada
typedef struct Node
{
    char name[MAX_NAME];
    struct Node *next;
    struct Node *prev;
} Node;

// Estrutura da tabela hash
typedef struct
{
    Node **table;
    int *counts; // Contador de elementos por chave
    int size;
} HashTable;

// ===== FUNCOES PARA CRIAR E DESTRUIR =====
int hashFunction(const char *name, int tableSize);
HashTable *createHashTable(int size);
void freeHashTable(HashTable *ht);
Node *createNode(const char *name);

// ===== OPERAÇÕES BASICAS =====
void insert(HashTable *ht, const char *name);
Node *search(HashTable *ht, const char *name);
int removeElement(HashTable *ht, const char *name);

// ===== ORDENAR =====
void sortKey(HashTable *ht, int key);
void quicksort(Node **arr, int low, int high);
int partition(Node **arr, int low, int high);

// ===== FUNÇÕES DE ANALISE =====
void displayHistogram(HashTable *ht);
void calculateStatistics(HashTable *ht);

// ===== FILES_UTILS =====
int loadNamesFromFile(HashTable *ht, const char *filename);

#endif