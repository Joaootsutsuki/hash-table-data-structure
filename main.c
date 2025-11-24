#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "hash_table.h"

void displayMenu()
{
    printf("\n=== MENU ===\n");
    printf("1. Inserir nome\n");
    printf("2. Buscar nome\n");
    printf("3. Remover nome\n");
    printf("4. Ordenar chave\n");
    printf("5. Exibir histograma\n");
    printf("6. Exibir estatisticas\n");
    printf("7. Listar nomes de uma chave\n");
    printf("8. Carregar arquivo\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main()
{
    HashTable *ht = createHashTable(TABLE_SIZE);
    int choice;
    char name[MAX_NAME];
    int key;

    printf("=== TABELA HASH COM ENCADEAMENTO ===\n");
    printf("Tamanho da tabela: %d\n", TABLE_SIZE);

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Limpa buffer

        switch (choice)
        {
        case 1:
            printf("Digite o nome: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            insert(ht, name);
            printf("Nome inserido com sucesso!\n");
            break;

        case 2:
            printf("Digite o nome: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            if (search(ht, name) != NULL)
            {
                printf("Nome encontrado!\n");
            }
            else
            {
                printf("Nome nao encontrado.\n");
            }
            break;

        case 3:
            printf("Digite o nome: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            if (removeElement(ht, name))
            {
                printf("Nome removido com sucesso!\n");
            }
            else
            {
                printf("Nome nao encontrado.\n");
            }
            break;

        case 4:
            printf("Digite a chave (0-%d): ", TABLE_SIZE - 1);
            scanf("%d", &key);
            sortKey(ht, key);
            printf("Chave %d ordenada!\n", key);
            break;

        case 5:
            displayHistogram(ht);
            break;

        case 6:
            calculateStatistics(ht);
            break;

        case 7:
            printf("Digite a chave (0-%d): ", TABLE_SIZE - 1);
            scanf("%d", &key);
            if (key >= 0 && key < TABLE_SIZE)
            {
                printf("\nNomes na chave %d (%d elementos):\n", key, ht->counts[key]);
                Node *current = ht->table[key];
                int count = 0;
                while (current != NULL && count < 20)
                {
                    printf("  - %s\n", current->name);
                    current = current->next;
                    count++;
                }
                if (count == 20 && current != NULL)
                {
                    printf("  ... (mostrando primeiros 20)\n");
                }
            }
            break;

        case 8:
            printf("Digite o caminho do arquivo: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            loadNamesFromFile(ht, name);
            break;

        case 0:
            printf("Encerrando...\n");
            freeHashTable(ht);
            return 0;

        default:
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}