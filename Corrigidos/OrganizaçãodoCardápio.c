// C - Organizacao do Cardapio
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float preco;
    char nome[100];
} Preco;

int compararNomes(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0' && a[i] == b[i]) {
        i++;
    }

    return (unsigned char)a[i] - (unsigned char)b[i];
}

void ordenar(Preco valor[], int n) {
    // Selection Sort: seleciona o menor elemento a cada passagem.
    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            if (valor[j].preco < valor[menor].preco ||
                (valor[j].preco == valor[menor].preco &&
                 compararNomes(valor[j].nome, valor[menor].nome) < 0)) {
                menor = j;
            }
        }

        if (menor != i) {
            Preco tmp = valor[i];
            valor[i] = valor[menor];
            valor[menor] = tmp;
        }
    }
}

int main(void) {
    int n = 0;
    int capacidade = 16;
    Preco *valor = malloc(capacidade * sizeof(Preco));
    Preco prato;

    if (valor == NULL) return 1;

    // EOF e o fim da entrada, nao uma palavra a ser comparada.
    while (scanf("%f %99[^\n]", &prato.preco, prato.nome) == 2) {
        for (int i = 0; prato.nome[i] != '\0'; i++) {
            if (prato.nome[i] == '\r') {
                prato.nome[i] = '\0';
                break;
            }
        }

        if (n == capacidade) {
            capacidade *= 2;
            Preco *novo = realloc(valor, capacidade * sizeof(Preco));
            if (novo == NULL) {
                free(valor);
                return 1;
            }
            valor = novo;
        }

        valor[n++] = prato;
    }

    ordenar(valor, n);

    for (int i = 0; i < n; i++) {
        printf("%.2f %s\n", valor[i].preco, valor[i].nome);
    }

    free(valor);
    return 0;
}
