#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/metricas.h"
#include "src/bubblesort.h"
#include "src/insertionsort.h"

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
    int N = 30000; // Exemplo de tamanho
    int *vetor = (int *)malloc(N * sizeof(int));
    if (vetor == NULL) return 1;

    srand(42); // Semente fixa para garantir que todos testem os mesmos dados
    gerarVetorAleatorio(vetor, N);
    struct timespec inicio, fim;
    Metricas m;

    // Medição de tempo de CPU de alta resolução
    printf("insertionSort\n");
    gerarVetorAleatorio(vetor, N);
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    insertionSort(vetor, N, &m);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Resultados:\nTempo: %f s\nComparacoes: %llu\nTrocas: %llu\n", m.tempo_segundos, m.comparacoes, m.trocas);

    printf("\n\n");

    printf("bubbleSort\n");
    gerarVetorAleatorio(vetor, N); 
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    bubbleSort(vetor, N, &m);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Resultados:\nTempo: %f s\nComparacoes: %llu\nTrocas: %llu\n", m.tempo_segundos, m.comparacoes, m.trocas);

    free(vetor);

    return 0;
}