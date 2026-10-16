/*
 * Ordenando a Lista de Crianças do Papai Noel
 *
 * Papai Noel está nos preparativos finais para a entrega dos presentes
 * para as crianças do mundo todo pois o natal está chegando mais uma vez.
 * Olhando suas novas listas de crianças que irão ganhar presentes neste
 * ano ele percebeu que o duende estagiário (que havia ficado responsável
 * por fazer as listas) não havia colocado os nomes em ordem alfabética.
 *
 * Como o Papai Noel é um homem muito organizado ele deseja que cada lista
 * de crianças possua, no seu final, o total de crianças que foram bem
 * comportadas neste ano e um total das que não foram. Assim ele pode
 * comparar a quantidade de crianças que se comportam este ano com as dos
 * anos anteriores.
 *
 * Para ajudar o bom velhinho, seu dever é criar um programa que leia todos
 * os nomes da lista e imprima os mesmos nomes em ordem alfabética. No final
 * da lista, você deve imprimir o total de crianças que foram e não foram
 * comportadas neste ano.
 *
 * Entrada
 * O primeiro valor N (0 <= N <= 100) indica quantos nomes tem na lista.
 * As N linhas seguintes contêm um caractere especial correspondente ao
 * comportamento da criança: + indica bom comportamento e - indica mau
 * comportamento. Após o caractere, segue o nome com no máximo 20 caracteres.
 *
 * Saída
 * Para cada lista, imprima os nomes em ordem alfabética. Após os nomes,
 * mostre o total de crianças que se comportaram bem ou mal durante o ano.
 */

#include <stdio.h>

typedef struct {
    char nome[21];
} Crianca;

int compararNomes(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && a[i] == b[i]) {
        i++;
    }
    return (unsigned char)a[i] - (unsigned char)b[i];
}

void ordenar(Crianca criancas[], int n) {
    // Selection sort implementado manualmente.
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (compararNomes(criancas[j].nome, criancas[menor].nome) < 0) {
                menor = j;
            }
        }
        if (menor != i) {
            Crianca temporaria = criancas[i];
            criancas[i] = criancas[menor];
            criancas[menor] = temporaria;
        }
    }
}

int main(void) {
    int n;

    while (scanf("%d", &n) == 1) {
        Crianca criancas[100];
        int comportadas = 0;
        int naoComportadas = 0;

        for (int i = 0; i < n; i++) {
            char comportamento;
            if (scanf(" %c %20[^\r\n]", &comportamento, criancas[i].nome) != 2) {
                return 1;
            }

            if (comportamento == '+') {
                comportadas++;
            } else {
                naoComportadas++;
            }
        }

        ordenar(criancas, n);

        for (int i = 0; i < n; i++) {
            printf("%s\n", criancas[i].nome);
        }
        printf("Se comportaram: %d | Nao se comportaram: %d\n",
               comportadas, naoComportadas);
    }

    return 0;
}
