#include <stdio.h>

typedef struct {
    unsigned long long comparacoes;
    unsigned long long trocas;
    double tempo_segundos;
} Metricas;

void bubbleSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    int aux = 0;

    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;

        for (int j=0; j < n-1; j++){
            m->comparacoes++;
            if(vetor[j] < vetor[j -1]){
                aux = vetor[j];
                vetor[j] = vetor[j-1];
                vetor[j-1] = aux;

                m->trocas++;
                trocou = 1;
            }
        }
    }

}
