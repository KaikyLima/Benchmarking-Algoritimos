#include "bubblesort.h"

void bubbleSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    int aux = 0;

    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;

        for (int j = 1; j < n - i; j++) {
            m->comparacoes++;
            if (vetor[j] < vetor[j - 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j - 1];
                vetor[j - 1] = aux;
                m->trocas++;
                trocou = 1;
            }
        }

        if (!trocou) break;
    }
}