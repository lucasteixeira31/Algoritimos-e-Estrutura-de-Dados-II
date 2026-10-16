/*
 * Dada uma sequencia de intervalos, o objetivo e combinar todos os
 * intervalos que se sobrepoem. Os intervalos a serem considerados sao
 * fechados. Sendo assim, dois intervalos se sobrepoem quando um deles
 * comeca antes do outro terminar.
 *
 * Por exemplo, dada uma sequencia [1, 3], [2, 6], [10, 15], [8, 10], a
 * saida deve ser [1, 6], [8, 15]. Isto porque o inicio 2 no intervalo
 * [2, 6] e menor que o final 3 no intervalo [1, 3]. De maneira semelhante,
 * o inicio 10 no intervalo [10, 15] e igual ao final 10 no intervalo [8, 10].
 *
 * A entrada e composta por varios casos de teste. Cada caso de teste
 * comeca com um inteiro indicando a quantidade de intervalos. Nas linhas
 * seguintes, cada linha e composta por um par de inteiros, indicando o
 * inicio e o fim de um intervalo.
 *
 * Restricao: a solucao deve ter complexidade, no pior caso, O(n log n).
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inicio;
    int fim;
} Intervalo;

void ordenar(Intervalo intervalos[], Intervalo auxiliar[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        ordenar(intervalos, auxiliar, inicio, meio);
        ordenar(intervalos, auxiliar, meio + 1, fim);

        int i = inicio;
        int j = meio + 1;
        int k = inicio;

        while (i <= meio && j <= fim) {
            if (intervalos[i].inicio <= intervalos[j].inicio) {
                auxiliar[k++] = intervalos[i++];
            } else {
                auxiliar[k++] = intervalos[j++];
            }
        }

        while (i <= meio) {
            auxiliar[k++] = intervalos[i++];
        }
        while (j <= fim) {
            auxiliar[k++] = intervalos[j++];
        }
        for (k = inicio; k <= fim; k++) {
            intervalos[k] = auxiliar[k];
        }
    }
}

int main(void) {
    int n;

    // Cada caso comeca com n; a leitura termina no EOF.
    while (scanf("%d", &n) == 1) {
        if (n < 0) return 1;
        if (n == 0) {
            printf("\n");
            continue;
        }

        Intervalo *intervalos = malloc((size_t)n * sizeof(Intervalo));
        Intervalo *auxiliar = malloc((size_t)n * sizeof(Intervalo));

        if (intervalos == NULL || auxiliar == NULL) {
            free(intervalos);
            free(auxiliar);
            return 1;
        }

        for (int i = 0; i < n; i++) {
            if (scanf("%d %d", &intervalos[i].inicio, &intervalos[i].fim) != 2) {
                free(intervalos);
                free(auxiliar);
                return 1;
            }
        }

        // Merge Sort: O(n log n) no pior caso.
        ordenar(intervalos, auxiliar, 0, n - 1);

        int inicio = intervalos[0].inicio;
        int fim = intervalos[0].fim;

        for (int i = 1; i < n; i++) {
            // Pontas iguais tambem se sobrepoem em intervalos fechados.
            if (intervalos[i].inicio <= fim) {
                if (intervalos[i].fim > fim) {
                    fim = intervalos[i].fim;
                }
            } else {
                printf("[%d, %d] ", inicio, fim);
                inicio = intervalos[i].inicio;
                fim = intervalos[i].fim;
            }
        }

        printf("[%d, %d]\n", inicio, fim);
        free(intervalos);
        free(auxiliar);
    }

    return 0;
}
