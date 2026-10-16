import java.util.Scanner;

public class ManutencaoDoCardapio {
    private static class Celula {
        String prato;
        Celula proxima;

        Celula(String prato) {
            this.prato = prato;
        }
    }

    private static class Lista {
        private Celula inicio;
        private int tamanho;

        // Internamente, os indices comecam em zero.
        void inserir(String prato, int posicao) {
            if (posicao < 0 || posicao > tamanho) {
                throw new IllegalArgumentException("Posicao invalida");
            }

            Celula nova = new Celula(prato);
            if (posicao == 0) {
                nova.proxima = inicio;
                inicio = nova;
            } else {
                Celula anterior = inicio;
                for (int i = 0; i < posicao - 1; i++) {
                    anterior = anterior.proxima;
                }
                nova.proxima = anterior.proxima;
                anterior.proxima = nova;
            }
            tamanho++;
        }

        void remover(int posicao) {
            if (posicao < 0 || posicao >= tamanho) {
                throw new IllegalArgumentException("Posicao invalida");
            }

            if (posicao == 0) {
                inicio = inicio.proxima;
            } else {
                Celula anterior = inicio;
                for (int i = 0; i < posicao - 1; i++) {
                    anterior = anterior.proxima;
                }
                anterior.proxima = anterior.proxima.proxima;
            }
            tamanho--;
        }

        void mostrar() {
            if (tamanho == 0) {
                System.out.println("VAZIO");
            } else {
                for (Celula atual = inicio; atual != null; atual = atual.proxima) {
                    System.out.println(atual.prato);
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        // Cada bloco representa um novo cardapio. A entrada termina em EOF.
        while (entrada.hasNextInt()) {
            int operacoes = entrada.nextInt();
            Lista cardapio = new Lista();

            for (int i = 0; i < operacoes; i++) {
                String comando = entrada.next();
                if (comando.equals("II")) {
                    cardapio.inserir(entrada.nextLine().trim(), 0);
                } else if (comando.equals("IF")) {
                    cardapio.inserir(entrada.nextLine().trim(), cardapio.tamanho);
                } else if (comando.equals("I*")) {
                    int posicao = entrada.nextInt();
                    // Os comandos da entrada usam posicoes a partir de 1.
                    cardapio.inserir(entrada.nextLine().trim(), posicao - 1);
                } else if (comando.equals("R*")) {
                    cardapio.remover(entrada.nextInt() - 1);
                }
            }

            cardapio.mostrar();
        }

        entrada.close();
    }
}
