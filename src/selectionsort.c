#include "selectionsort.h"

void selectionSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;

    for (int i = 0; i < n - 1; i++) {
        int indice_min = i;

        for (int j = i + 1; j < n; j++) {
            m->comparacoes++;
            if (vetor[j] < vetor[indice_min]) {
                indice_min = j;
            }
        }

        if (indice_min != i) {
            int aux = vetor[i];
            vetor[i] = vetor[indice_min];
            vetor[indice_min] = aux;
            m->trocas++;
        }
    }
}