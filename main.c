#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "src/metricas.h"
#include "src/bubblesort.h"
#include "src/insertionsort.h"
#include "src/selectionsort.h"

// ---- FUNÇÕES AUXILIARES DE GERAÇÃO DE DADOS ----
void gerarVetorAleatorio(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = rand() % 100000;
}

void gerarVetorOrdenado(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = i;
}

void gerarVetorInverso(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = n - i;
}

int main() {
    int N = 30000;
    int *vetor  = (int *)malloc(N * sizeof(int));
    int *buffer = (int *)malloc(N * sizeof(int));
    if (vetor == NULL || buffer == NULL) return 1;
 
    srand(42);
    struct timespec inicio, fim;
    Metricas m;
 
    const char *cenarios[] = { "Aleatorio", "Ordenado (Melhor Caso)", "Inverso (Pior Caso)" };
 
    // PROBLEMA 1 
    for (int c = 0; c < 3; c++) {
 
        if      (c == 0) gerarVetorAleatorio(vetor, N);
        else if (c == 1) gerarVetorOrdenado(vetor, N);
        else             gerarVetorInverso(vetor, N);
 
        printf("=== Cenario: %s ===\n\n", cenarios[c]);
 
        memcpy(buffer, vetor, N * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        insertionSort(buffer, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("insertionSort\nResultados:\nTempo: %f s\nComparacoes: %llu\nTrocas: %llu\n\n",
               m.tempo_segundos, m.comparacoes, m.trocas);
 
        memcpy(buffer, vetor, N * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        bubbleSort(buffer, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("bubbleSort\nResultados:\nTempo: %f s\nComparacoes: %llu\nTrocas: %llu\n\n",
               m.tempo_segundos, m.comparacoes, m.trocas);
 
        memcpy(buffer, vetor, N * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        selectionSort(buffer, N, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("selectionSort\nResultados:\nTempo: %f s\nComparacoes: %llu\nTrocas: %llu\n\n",
               m.tempo_segundos, m.comparacoes, m.trocas);
 
        printf("------------------------------------------------------------\n\n");
    }
 
    free(vetor);
    free(buffer);
    return 0;
}