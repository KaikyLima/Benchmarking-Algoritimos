#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "src/metricas.h"
#include "src/bubblesort.h"
#include "src/insertionsort.h"
#include "src/selectionsort.h"
#include "src/quicksort.h"
#include "src/heapsort.h"
#include "src/shellsort.h"

void gerarVetorAleatorio(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = rand() % 100000;
}

void gerarVetorOrdenado(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = i;
}

void gerarVetorInverso(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = n - i;
}

void gerarVetorQuaseOrdenado(int *v, int n) {
    gerarVetorOrdenado(v, n); 
    
    int total_trocas = (int)(n * 0.005); 
    
    for (int i = 0; i < total_trocas; i++) {
        int idx = rand() % (n - 1); 
        
        int temp = v[idx];
        v[idx] = v[idx + 1];
        v[idx + 1] = temp;
    }
}

int main() {
    int N1 = 30000;
    int *vetor  = (int *)malloc(50000 * sizeof(int));
    int *buffer = (int *)malloc(50000 * sizeof(int));
    if (vetor == NULL || buffer == NULL) return 1;
 
    srand(42);
    struct timespec inicio, fim;
    Metricas m;
 
    const char *cenarios[] = { "Aleatorio", "Ordenado (Melhor Caso)", "Inverso (Pior Caso)" };

    printf("PROBLEMA 1\n\n");
 
    // PROBLEMA 1 
    for (int c = 0; c < 3; c++) {
 
        if      (c == 0) gerarVetorAleatorio(vetor, N1);
        else if (c == 1) gerarVetorOrdenado(vetor, N1);
        else             gerarVetorInverso(vetor, N1);
 
        printf("=== Cenario: %s ===\n\n", cenarios[c]);
 
        memcpy(buffer, vetor, N1 * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        insertionSort(buffer, N1, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("Insertion Sort\n    Tempo: %fs\n    Comparacoes: %llu\n    Trocas: %llu\n\n",
               m.tempo_segundos, m.comparacoes, m.trocas);
 
        memcpy(buffer, vetor, N1 * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        bubbleSort(buffer, N1, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("Bubble Sort\n    Tempo: %fs\n    Comparacoes: %llu\n    Trocas: %llu\n\n",
               m.tempo_segundos, m.comparacoes, m.trocas);
 
        memcpy(buffer, vetor, N1 * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        selectionSort(buffer, N1, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("Selection Sort\n    Tempo: %fs\n    Comparacoes: %llu\n    Trocas: %llu\n\n",
               m.tempo_segundos, m.comparacoes, m.trocas);

        if (c != 2){
            printf("------------------------------------------------------------\n\n");
        }else{
            printf("------------------------------------------------------------");
        }
        

    }


    // PROBLEMA 2
    printf("\n------------------------------------------------------------\n\n");
    printf("PROBLEMA 2\n\n"); 

    int N2 = 5000; 
    
    double tempos_quick[10];
    double tempos_heap[10];
    double soma_quick = 0.0, soma_heap = 0.0;

    for (int i = 0; i < 10; i++) {
        
        gerarVetorOrdenado(vetor, N2);
        memcpy(buffer, vetor, N2 * sizeof(int));
        
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        quickSort(buffer, N2, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        
        tempos_quick[i] = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        soma_quick += tempos_quick[i];

        gerarVetorOrdenado(vetor, N2);
        memcpy(buffer, vetor, N2 * sizeof(int));
        
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        heapSort(buffer, N2, &m);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        
        tempos_heap[i] = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        soma_heap += tempos_heap[i];
    }


    double media_quick = soma_quick / 10.0;
    double media_heap = soma_heap / 10.0;

    double variancia_quick = 0.0, variancia_heap = 0.0;
    for (int i = 0; i < 10; i++) {
        variancia_quick += pow(tempos_quick[i] - media_quick, 2);
        variancia_heap += pow(tempos_heap[i] - media_heap, 2);
    }

    double dp_quick = sqrt(variancia_quick / 9.0);
    double dp_heap = sqrt(variancia_heap / 9.0);

    printf("RESULTADOS \n\n");
    printf("QuickSort:\n");
    printf("    Tempo Médio: %f s\n", media_quick);
    printf("    Desvio Padrão: %f s\n\n", dp_quick);

    printf("HeapSort:\n");
    printf("    Tempo Médio: %f s\n", media_heap);
    printf("    Desvio Padrão: %f s\n\n", dp_heap);
    
    printf("------------------------------------------------------------\n");
    printf("------------------------------------------------------------\n\n");



    // PROBLEMA 3
    printf("PROBLEMA 3\n\n");

    int N3 = 50000;
    gerarVetorQuaseOrdenado(vetor, N3);

    memcpy(buffer, vetor, N3 * sizeof(int));
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    insertionSort(buffer, N3, &m);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Insertion Sort \nResultados:\n  Tempo: %fs\n  Comparacoes: %llu\n  Trocas: %llu\n\n",
           m.tempo_segundos, m.comparacoes, m.trocas);


    memcpy(buffer, vetor, N3 * sizeof(int));
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    shellSort(buffer, N3, &m);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Shell Sort \nResultados:\n  Tempo: %fs\n  Comparacoes: %llu\n  Trocas: %llu\n\n",
           m.tempo_segundos, m.comparacoes, m.trocas);

    printf("------------------------------------------------------------\n\n");
    printf("------------------------------------------------------------\n\n");
 
    free(vetor);
    free(buffer);
    return 0;
}