/*
 * Eu Posso Adivinhar a Estrutura de Dados
 *
 * Existe uma estrutura de dados do tipo sacola, suportando duas operacoes:
 *
 * 1 x: Jogue um elemento x na sacola.
 * 2 x: Tire um elemento da sacola; o elemento obtido deve ser x.
 *
 * Dada uma sequencia de operacoes que retornam valores, voce vai adivinhar
 * a estrutura de dados. E uma pilha (ultimo-dentro, primeiro-fora), uma
 * fila (primeiro-dentro, primeiro-fora), uma fila de prioridade (sempre
 * tire os elementos grandes por primeiro) ou qualquer outra coisa que
 * voce dificilmente consegue imaginar!
 *
 * Entrada
 *
 * Existem muitos casos de teste. Cada caso comeca com uma linha contendo
 * um unico inteiro n (1 <= n <= 1000). Cada uma das seguintes n linhas
 * contem um comando do tipo 1 ou 2, seguido de um numero inteiro x.
 * No comando do tipo 2, x indica o elemento obtido ao realizar a retirada.
 * O valor de x e sempre um inteiro positivo e nao maior do que 100.
 * O final da entrada e determinado pelo final do arquivo (EOF).
 * O tamanho do arquivo de entrada nao excede 1 MB.
 *
 * Saida
 *
 * Para cada caso de teste, mostre um dos seguintes:
 * stack: E definitivamente uma pilha.
 * queue: E definitivamente uma fila.
 * priority queue: E definitivamente uma fila de prioridade.
 * impossible: Nao pode ser uma pilha, fila ou fila de prioridade.
 * not sure: Pode ser mais de uma das tres estruturas mencionadas acima.
 */

import java.util.Scanner;

public class EuPossoAdivinharAEstruturaDeDados {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        while (entrada.hasNextInt()) {
            int n = entrada.nextInt();
            int[] pilha = new int[n];
            int[] fila = new int[n];
            int[] prioridade = new int[n];
            int topo = 0;
            int inicio = 0;
            int fim = 0;
            int tamanhoPrioridade = 0;
            boolean podePilha = true;
            boolean podeFila = true;
            boolean podePrioridade = true;

            for (int i = 0; i < n; i++) {
                int operacao = entrada.nextInt();
                int valor = entrada.nextInt();

                if (operacao == 1) {
                    if (podePilha) {
                        pilha[topo++] = valor;
                    }
                    if (podeFila) {
                        fila[fim++] = valor;
                    }
                    if (podePrioridade) {
                        prioridade[tamanhoPrioridade++] = valor;
                    }
                } else {
                    if (podePilha) {
                        if (topo == 0 || pilha[topo - 1] != valor) {
                            podePilha = false;
                        } else {
                            topo--;
                        }
                    }

                    if (podeFila) {
                        if (inicio == fim || fila[inicio] != valor) {
                            podeFila = false;
                        } else {
                            inicio++;
                        }
                    }

                    if (podePrioridade) {
                        if (tamanhoPrioridade == 0) {
                            podePrioridade = false;
                        } else {
                            // Busca manualmente o maior elemento da sacola.
                            int maior = 0;
                            for (int j = 1; j < tamanhoPrioridade; j++) {
                                if (prioridade[j] > prioridade[maior]) {
                                    maior = j;
                                }
                            }

                            if (prioridade[maior] != valor) {
                                podePrioridade = false;
                            } else {
                                // A ordem interna deste vetor nao importa.
                                prioridade[maior] = prioridade[--tamanhoPrioridade];
                            }
                        }
                    }
                }
            }

            int possibilidades = 0;
            if (podePilha) possibilidades++;
            if (podeFila) possibilidades++;
            if (podePrioridade) possibilidades++;

            if (possibilidades == 0) {
                System.out.println("impossible");
            } else if (possibilidades > 1) {
                System.out.println("not sure");
            } else if (podePilha) {
                System.out.println("stack");
            } else if (podeFila) {
                System.out.println("queue");
            } else {
                System.out.println("priority queue");
            }
        }

        entrada.close();
    }
}
