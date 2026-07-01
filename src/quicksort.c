#include "quicksort.h"


static int particionar(int *vetor, int inicio, int fim, Metricas *m) {
    int pivo = vetor[fim];
    int i    = inicio - 1; 

    for (int j = inicio; j < fim; j++) {
        m->comparacoes++;
        if (vetor[j] <= pivo) {
            i++;
            int aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            m->trocas++;
        }
    }

    if (i + 1 != fim) {
        int aux = vetor[i + 1];
        vetor[i + 1] = vetor[fim];
        vetor[fim] = aux;
        m->trocas++;
    }

    return i + 1;
}

static void quickSortRec(int *vetor, int inicio, int fim, Metricas *m) {
    if (inicio < fim) {
        int pivo_pos = particionar(vetor, inicio, fim, m);
        quickSortRec(vetor, inicio, pivo_pos - 1, m);
        quickSortRec(vetor, pivo_pos + 1, fim,    m);
    }
}

void quickSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;

    quickSortRec(vetor, 0, n - 1, m);
}