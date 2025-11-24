#include <stdio.h>
#include <math.h>
#include "hash_table.h"

void displayHistogram(HashTable *ht)
{
    int i, j;
    int maxCount = 0;

    printf("\n=== HISTOGRAMA DE DISTRIBUICAO ===\n\n");

    // Encontra o valor máximo
    for (i = 0; i < ht->size; i++)
    {
        if (ht->counts[i] > maxCount)
        {
            maxCount = ht->counts[i];
        }
    }

    for (i = 0; i < ht->size; i++)
    {
        printf("Chave %2d [%5d]: ", i, ht->counts[i]);

        int numBars = (ht->counts[i] * 60) / maxCount;
        for (j = 0; j < numBars; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    printf("\nLegenda: # = elementos na chave\n");
    printf("Escala: 60 caracteres = %d elementos (maximo)\n", maxCount);
}

// Calcula estatísticas da tabela hash
void calculateStatistics(HashTable *ht)
{
    int i;
    int total = 0;
    int empty = 0;
    int maxChain = 0;
    int minChain = ht->counts[0];
    double avgChain, variance = 0, stdDev;

    for (i = 0; i < ht->size; i++)
    {
        total += ht->counts[i];

        if (ht->counts[i] == 0)
        {
            empty++;
        }
        else if (ht->counts[i] < minChain)
        {
            minChain = ht->counts[i];
        }

        if (ht->counts[i] > maxChain)
        {
            maxChain = ht->counts[i];
        }
    }

    avgChain = (double)total / ht->size;

    // Calcula desvio padrão
    for (i = 0; i < ht->size; i++)
    {
        variance += (ht->counts[i] - avgChain) * (ht->counts[i] - avgChain);
    }
    variance /= ht->size;
    stdDev = sqrt(variance);

    printf("\n=== ESTATISTICAS DA TABELA HASH ===\n");
    printf("Total de elementos: %d\n", total);
    printf("Tamanho da tabela: %d\n", ht->size);
    printf("Chaves vazias: %d (%.2f%%)\n", empty, (empty * 100.0) / ht->size);
    printf("Maior cadeia: %d elementos\n", maxChain);
    printf("Menor cadeia: %d elementos\n", minChain);
    printf("Media por chave: %.2f elementos\n", avgChain);
    printf("Desvio padrao: %.2f\n", stdDev);
    printf("Fator de carga: %.4f\n", (double)total / ht->size);

    // Análise da uniformidade
    double uniformityScore = (stdDev / avgChain) * 100;
    printf("\n=== ANALISE DE UNIFORMIDADE ===\n");
    printf("Coeficiente de variacao: %.2f%%\n", uniformityScore);

    if (uniformityScore < 10)
    {
        printf("Distribuicao: EXCELENTE (muito proxima do uniforme)\n");
    }
    else if (uniformityScore < 20)
    {
        printf("Distribuicao: BOA (razoavelmente uniforme)\n");
    }
    else if (uniformityScore < 30)
    {
        printf("Distribuicao: REGULAR (desvios moderados)\n");
    }
    else
    {
        printf("Distribuicao: RUIM (desvios significativos)\n");
    }

    printf("\nHipotese do Hashing Uniforme:\n");
    printf("Esperado: %.2f elementos por chave\n", avgChain);
    printf("Desvio: %.2f elementos\n", stdDev);
    printf("Razao max/media: %.2f\n", maxChain / avgChain);
}