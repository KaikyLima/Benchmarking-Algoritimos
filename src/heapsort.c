#include "heapsort.h"


static void heapify(int *vetor, int n, int i, Metricas *m) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita  = 2 * i + 2;

    if (esquerda < n) {
        m->comparacoes++;
        if (vetor[esquerda] > vetor[maior]) {
            maior = esquerda;
        }
    }

    if (direita < n) {
        m->comparacoes++;
        if (vetor[direita] > vetor[maior]) {
            maior = direita;
        }
    }

    if (maior != i) {
        int aux      = vetor[i];
        vetor[i]     = vetor[maior];
        vetor[maior] = aux;
        m->trocas++;

        heapify(vetor, n, maior, m);
    }
}

void heapSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas      = 0;

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vetor, n, i, m);
    }


    for (int i = n - 1; i > 0; i--) {
        int aux    = vetor[0];
        vetor[0]   = vetor[i];
        vetor[i]   = aux;
        m->trocas++;

        heapify(vetor, i, 0, m);
    }
}