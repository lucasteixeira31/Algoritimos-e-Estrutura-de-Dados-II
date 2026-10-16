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

import java.util.Scanner;

class CombinandoIntervalos {
    public static void ordenar(int[][] intervalos, int[][] auxiliar, int inicio, int fim) {
        if (inicio < fim) {
            int meio = inicio + (fim - inicio) / 2;
            ordenar(intervalos, auxiliar, inicio, meio);
            ordenar(intervalos, auxiliar, meio + 1, fim);

            int i = inicio;
            int j = meio + 1;
            int k = inicio;

            while (i <= meio && j <= fim) {
                if (intervalos[i][0] <= intervalos[j][0]) {
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

    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        // Cada caso comeca pela quantidade de intervalos; a leitura termina no EOF.
        while (entrada.hasNextInt()) {
            int n = entrada.nextInt();
            int[][] intervalos = new int[n][2];

            for (int i = 0; i < n; i++) {
                intervalos[i][0] = entrada.nextInt();
                intervalos[i][1] = entrada.nextInt();
            }

            // Ordenacao O(n log n) no pior caso pelo inicio dos intervalos.
            int[][] auxiliar = new int[n][];
            ordenar(intervalos, auxiliar, 0, n - 1);

            if (n > 0) {
                int inicio = intervalos[0][0];
                int fim = intervalos[0][1];

                for (int i = 1; i < n; i++) {
                    // Intervalos fechados tambem se unem quando as pontas sao iguais.
                    if (intervalos[i][0] <= fim) {
                        if (intervalos[i][1] > fim) {
                            fim = intervalos[i][1];
                        }
                    } else {
                        System.out.print("[" + inicio + ", " + fim + "] ");
                        inicio = intervalos[i][0];
                        fim = intervalos[i][1];
                    }
                }

                System.out.print("[" + inicio + ", " + fim + "]");
            }

            System.out.println();
        }

        entrada.close();
    }
}
