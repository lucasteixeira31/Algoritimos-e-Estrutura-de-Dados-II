    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct Data {
        int dia;
        int mes;
        int ano;
    } Data;

    typedef struct Veiculo {
        int id;
        char marca[100];
        char modelo[100];
        int ano;
        char categoria[100];
        char combustivel[100];
        int cilindros;
        double cilindrada;
        char transmissao[100];
        char tracao[100];
        double consumoCidade;
        double consumoEstrada;
        double co2;
        char turbo[10];
        Data dataRegistro;
    } Veiculo;

    typedef struct Celula {
        Veiculo veiculo;
        struct Celula *prox;
    } Celula;

    typedef struct Lista {
        Celula *primeiro;
        Celula *ultimo;
    } Lista;

    //copia um campo textual do dataset sem usar strcpy
    void copiarCampo(char destino[], const char origem[]) {
        int i = 0;
        while (origem[i] != '\0') {
            destino[i] = origem[i];
            i++;
        }
        destino[i] = '\0';
    }

    //le uma linha de id e atribui zero quando ela nao representa um inteiro
    int lerId(int *id) {
        char linha[100];
        int resposta = fgets(linha, sizeof(linha), stdin) != NULL;
        *id = 0;
        if (resposta) {
            int valor;
            char extra;
            if (sscanf(linha, "%d %c", &valor, &extra) == 1) {
                *id = valor;
            }
        }
        return resposta;
    }

    //troca o ponto e virgula por virgula para imprimir combustiveis compostos
    void arrumarCombustivel(char combustivel[]) {
        for (int i = 0; combustivel[i] != '\0'; i++) {
            if (combustivel[i] == ';') {
                combustivel[i] = ',';
            }
        }
    }

    //remove a quebra de linha que fica no final da leitura
    void removerQuebraLinha(char linha[]) {
        int tamanho = 0;
        while (linha[tamanho] != '\0') {
            tamanho++;
        }

        while (tamanho > 0 && (linha[tamanho - 1] == '\n' || linha[tamanho - 1] == '\r')) {
            linha[--tamanho] = '\0';
        }
    }

    //separa a data do csv e cria uma variavel do tipo Data
    Data lerData(char linha[]) {
        Data data;

        sscanf(linha, "%d-%d-%d", &data.ano, &data.mes, &data.dia);

        return data;
    }

    //separa os campos da linha do csv e cria uma variavel do tipo Veiculo
    Veiculo lerVeiculo(char linha[]) {
        Veiculo veiculo;
        char *campo;

        removerQuebraLinha(linha);

        campo = strtok(linha, ",");
        veiculo.id = atoi(campo);

        campo = strtok(NULL, ",");
        copiarCampo(veiculo.marca, campo);

        campo = strtok(NULL, ",");
        copiarCampo(veiculo.modelo, campo);

        campo = strtok(NULL, ",");
        veiculo.ano = atoi(campo);

        campo = strtok(NULL, ",");
        copiarCampo(veiculo.categoria, campo);

        campo = strtok(NULL, ",");
        copiarCampo(veiculo.combustivel, campo);
        arrumarCombustivel(veiculo.combustivel);

        campo = strtok(NULL, ",");
        veiculo.cilindros = atoi(campo);

        campo = strtok(NULL, ",");
        veiculo.cilindrada = atof(campo);

        campo = strtok(NULL, ",");
        copiarCampo(veiculo.transmissao, campo);

        campo = strtok(NULL, ",");
        copiarCampo(veiculo.tracao, campo);

        campo = strtok(NULL, ",");
        veiculo.consumoCidade = atof(campo);

        campo = strtok(NULL, ",");
        veiculo.consumoEstrada = atof(campo);

        campo = strtok(NULL, ",");
        veiculo.co2 = atof(campo);

        campo = strtok(NULL, ",");
        copiarCampo(veiculo.turbo, campo);

        campo = strtok(NULL, ",");
        veiculo.dataRegistro = lerData(campo);

        return veiculo;
    }

    //le todos os veiculos do arquivo csv e guarda no vetor
    int lerArquivo(Veiculo veiculos[]) {
        FILE *arquivo = fopen("/tmp/veiculos.csv", "r");
        char linha[500];
        int quantidade = 0;

        if (arquivo == NULL) {
            fprintf(stderr, "Nao foi possivel abrir /tmp/veiculos.csv\n");
            exit(EXIT_FAILURE);
        }

        //pula o cabecalho do arquivo
        fgets(linha, 500, arquivo);

        while (fgets(linha, 500, arquivo) != NULL) {
            if (quantidade == 1000) {
                fclose(arquivo);
                fprintf(stderr, "Dataset maior que a capacidade do vetor\n");
                exit(EXIT_FAILURE);
            }
            veiculos[quantidade] = lerVeiculo(linha);
            quantidade++;
        }

        fclose(arquivo);

        return quantidade;
    }

    //procura o veiculo pelo id usando pesquisa sequencial
    int pesquisar(Veiculo veiculos[], int quantidade, int id) {
        int resposta = -1;

        for (int i = 0; i < quantidade; i++) {
            if (veiculos[i].id == id) {
                resposta = i;
                i = quantidade;
            }
        }

        return resposta;
    }

    //imprime o veiculo exatamente no formato pedido
    void imprimirVeiculo(Veiculo veiculo) {
        printf("[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1lf ## %s ## %s ## %.2lf ## %.2lf ## %.1lf ## %s ## %02d/%02d/%04d]\n",
                veiculo.id, veiculo.marca, veiculo.modelo, veiculo.ano,
                veiculo.categoria, veiculo.combustivel, veiculo.cilindros,
                veiculo.cilindrada, veiculo.transmissao, veiculo.tracao,
                veiculo.consumoCidade, veiculo.consumoEstrada, veiculo.co2,
                veiculo.turbo, veiculo.dataRegistro.dia, veiculo.dataRegistro.mes,
                veiculo.dataRegistro.ano);
    }

    //cria uma nova celula para a lista
    Celula *novaCelula(Veiculo veiculo) {
        Celula *celula = (Celula*) malloc(sizeof(Celula));
        if (celula == NULL) {
            exit(EXIT_FAILURE);
        }
        celula->veiculo = veiculo;
        celula->prox = NULL;

        return celula;
    }

    //inicia a lista com uma celula cabeca
    void iniciarLista(Lista *lista) {
        lista->primeiro = novaCelula((Veiculo){0});
        lista->ultimo = lista->primeiro;
    }

    //insere um veiculo no fim da lista
    void inserirFim(Lista *lista, Veiculo veiculo) {
        lista->ultimo->prox = novaCelula(veiculo);
        lista->ultimo = lista->ultimo->prox;
    }

    //transforma letra maiuscula em minuscula para comparar os modelos
    char paraMinusculo(char c) {
        if (c >= 'A' && c <= 'Z') {
            c = c + 32;
        }

        return c;
    }

    //compara duas strings sem diferenciar maiusculas e minusculas
    int compararModelo(char modelo1[], char modelo2[]) {
        int resposta = 0;
        int i = 0;

        while (resposta == 0 && modelo1[i] != '\0' && modelo2[i] != '\0') {
            char c1 = paraMinusculo(modelo1[i]);
            char c2 = paraMinusculo(modelo2[i]);

            if (c1 < c2) {
                resposta = -1;
            } else if (c1 > c2) {
                resposta = 1;
            }

            i++;
        }

        if (resposta == 0 && modelo1[i] == '\0' && modelo2[i] != '\0') {
            resposta = -1;
        } else if (resposta == 0 && modelo1[i] != '\0' && modelo2[i] == '\0') {
            resposta = 1;
        }

        return resposta;
    }

    //percorre as celulas e troca somente os registros usando selecao
    void ordenarSelecao(Lista *lista) {
        for (Celula *i = lista->primeiro->prox; i != NULL; i = i->prox) {
            Celula *menor = i;
            for (Celula *j = i->prox; j != NULL; j = j->prox) {
                if (compararModelo(j->veiculo.modelo, menor->veiculo.modelo) < 0) {
                    menor = j;
                }
            }
            Veiculo tmp = i->veiculo;
            i->veiculo = menor->veiculo;
            menor->veiculo = tmp;
        }
    }

    //confere ausencia de ciclos e se ultimo e realmente a ultima celula
    int validarLista(Lista *lista) {
        int resposta = lista->primeiro != NULL && lista->ultimo != NULL;
        if (resposta) {
            Celula *lento = lista->primeiro;
            Celula *rapido = lista->primeiro;
            while (resposta && rapido != NULL && rapido->prox != NULL) {
                lento = lento->prox;
                rapido = rapido->prox->prox;
                if (lento == rapido) {
                    resposta = 0;
                }
            }
            if (resposta) {
                Celula *i = lista->primeiro;
                while (i->prox != NULL) {
                    i = i->prox;
                }
                resposta = i == lista->ultimo;
            }
        }
        return resposta;
    }

    //mostra a lista na ordem das celulas
    void mostrar(Lista *lista) {
        for (Celula *i = lista->primeiro->prox; i != NULL; i = i->prox) {
            imprimirVeiculo(i->veiculo);
        }
    }

    //libera todos os nos, incluindo a cabeca
    void liberarLista(Lista *lista) {
        Celula *i = lista->primeiro;
        while (i != NULL) {
            Celula *tmp = i;
            i = i->prox;
            free(tmp);
        }
        lista->primeiro = lista->ultimo = NULL;
    }

    //seleciona por id e ordena a lista, sem comandos de insercao ou remocao
    int main(void) {
        Veiculo veiculos[1000];
        int quantidade = lerArquivo(veiculos);
        Lista lista;
        int id;
        iniciarLista(&lista);
        while (lerId(&id) && id != -1) {
            int posicao = pesquisar(veiculos, quantidade, id);
            if (posicao != -1) {
                inserirFim(&lista, veiculos[posicao]);
            }
        }
        if (!validarLista(&lista)) {
            liberarLista(&lista);
            return EXIT_FAILURE;
        }
        ordenarSelecao(&lista);
        if (!validarLista(&lista)) {
            liberarLista(&lista);
            return EXIT_FAILURE;
        }
        mostrar(&lista);
        liberarLista(&lista);
        return 0;
    }
