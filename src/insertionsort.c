#include "insertionsort.h"

void insertionSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    // EXEMPLO DE IMPLEMENTAÇÃO E INSTRUMENTAÇÃO:
    for (int i = 1; i < n; i++) {
        int chave = vetor[i];
        int j = i - 1;
        // Cada entrada no laço testa a condição (j >= 0 e vetor[j] > chave)
        while (j >= 0) {
            m->comparacoes++; // Conta a comparação feita no 'if' conceitual do while
            if (vetor[j] > chave) {
                vetor[j + 1] = vetor[j];
                m->trocas++; // Conta o deslocamento/escrita
                j--;
            } else {
                break;
            }
        }
        // Se saiu do laço porque j < 0, a última comparação falhou e já foi contada.
        // Se saiu pelo 'break', também já foi contada.
        vetor[j + 1] = chave;
    }
}