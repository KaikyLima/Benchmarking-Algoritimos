#include "shellsort.h"

void shellSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {

            int chave = vetor[i];
            int j = i - gap;

            while (j >= 0) {
                m->comparacoes++;
                if (vetor[j] > chave) {

                    vetor[j + gap] = vetor[j];
                    m->trocas++; 
                    j -= gap;

                } else {
                    break;
                }
            }
            
            vetor[j + gap] = chave;
        }
    }
}