#include <stdio.h>
#include <string.h>
#include "hash_table.h"

int loadNamesFromFile(HashTable *ht, const char *filename)
{
    FILE *file = fopen(filename, "r");
    char name[MAX_NAME];
    int count = 0;

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo: %s\n", filename);
        return 0;
    }

    while (fgets(name, MAX_NAME, file) != NULL)
    {
        name[strcspn(name, "\n")] = '\0';
        name[strcspn(name, "\r")] = '\0';

        if (strlen(name) > 0)
        {
            insert(ht, name);
            count++;
        }
    }

    fclose(file);
    printf("Carregados %d nomes do arquivo.\n", count);
    return count;
}