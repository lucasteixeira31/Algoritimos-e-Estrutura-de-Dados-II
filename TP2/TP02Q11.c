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
    int tamanho = strlen(linha);

    if (tamanho > 0 && linha[tamanho - 1] == '\n') {
        linha[tamanho - 1] = '\0';
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
    strcpy(veiculo.marca, campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo.modelo, campo);

    campo = strtok(NULL, ",");
    veiculo.ano = atoi(campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo.categoria, campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo.combustivel, campo);
    arrumarCombustivel(veiculo.combustivel);

    campo = strtok(NULL, ",");
    veiculo.cilindros = atoi(campo);

    campo = strtok(NULL, ",");
    veiculo.cilindrada = atof(campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo.transmissao, campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo.tracao, campo);

    campo = strtok(NULL, ",");
    veiculo.consumoCidade = atof(campo);

    campo = strtok(NULL, ",");
    veiculo.consumoEstrada = atof(campo);

    campo = strtok(NULL, ",");
    veiculo.co2 = atof(campo);

    campo = strtok(NULL, ",");
    strcpy(veiculo.turbo, campo);

    campo = strtok(NULL, ",");
    veiculo.dataRegistro = lerData(campo);

    return veiculo;
}

//le todos os veiculos do arquivo csv e guarda no vetor
int lerArquivo(Veiculo veiculos[]) {
    FILE *arquivo = fopen("/tmp/veiculos.csv", "r");
    char linha[500];
    int quantidade = 0;

    //pula o cabecalho do arquivo
    fgets(linha, 500, arquivo);

    while (fgets(linha, 500, arquivo) != NULL) {
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
    celula->veiculo = veiculo;
    celula->prox = NULL;

    return celula;
}

//inicia a lista com uma celula cabeca
void iniciarLista(Lista *lista) {
    lista->primeiro = novaCelula((Veiculo){0});
    lista->ultimo = lista->primeiro;
}

//insere um veiculo no inicio da lista
void inserirInicio(Lista *lista, Veiculo veiculo) {
    Celula *tmp = novaCelula(veiculo);
    tmp->prox = lista->primeiro->prox;
    lista->primeiro->prox = tmp;

    if (lista->primeiro == lista->ultimo) {
        lista->ultimo = tmp;
    }
}

//insere um veiculo no fim da lista
void inserirFim(Lista *lista, Veiculo veiculo) {
    lista->ultimo->prox = novaCelula(veiculo);
    lista->ultimo = lista->ultimo->prox;
}

//insere um veiculo em uma posicao especifica
void inserir(Lista *lista, Veiculo veiculo, int posicao) {
    Celula *i = lista->primeiro;

    for (int j = 0; j < posicao; j++) {
        i = i->prox;
    }

    Celula *tmp = novaCelula(veiculo);
    tmp->prox = i->prox;
    i->prox = tmp;

    if (tmp->prox == NULL) {
        lista->ultimo = tmp;
    }
}

//remove o primeiro veiculo da lista
Veiculo removerInicio(Lista *lista) {
    Celula *tmp = lista->primeiro->prox;
    Veiculo removido = tmp->veiculo;
    lista->primeiro->prox = tmp->prox;

    if (tmp == lista->ultimo) {
        lista->ultimo = lista->primeiro;
    }

    free(tmp);

    return removido;
}

//remove o ultimo veiculo da lista
Veiculo removerFim(Lista *lista) {
    Celula *i = lista->primeiro;

    while (i->prox != lista->ultimo) {
        i = i->prox;
    }

    Veiculo removido = lista->ultimo->veiculo;
    free(lista->ultimo);
    lista->ultimo = i;
    lista->ultimo->prox = NULL;

    return removido;
}

//remove um veiculo de uma posicao especifica
Veiculo remover(Lista *lista, int posicao) {
    Celula *i = lista->primeiro;

    for (int j = 0; j < posicao; j++) {
        i = i->prox;
    }

    Celula *tmp = i->prox;
    Veiculo removido = tmp->veiculo;
    i->prox = tmp->prox;

    if (tmp == lista->ultimo) {
        lista->ultimo = i;
    }

    free(tmp);

    return removido;
}

//imprime os dados principais do veiculo removido
void imprimirRemovido(Veiculo veiculo) {
    printf("(R)%s %s\n", veiculo.marca, veiculo.modelo);
}

//mostra todos os veiculos da lista do primeiro ao ultimo
void mostrar(Lista *lista) {
    for (Celula *i = lista->primeiro->prox; i != NULL; i = i->prox) {
        imprimirVeiculo(i->veiculo);
    }
}

//executa um comando de insercao ou remocao na lista
void executarComando(char linha[], Lista *lista, Veiculo veiculos[], int quantidade) {
    char comando[5];
    int posicao;
    int id;
    Veiculo removido;

    sscanf(linha, "%s", comando);

    if (strcmp(comando, "II") == 0) {
        sscanf(linha, "%s %d", comando, &id);
        inserirInicio(lista, veiculos[pesquisar(veiculos, quantidade, id)]);
    } else if (strcmp(comando, "IF") == 0) {
        sscanf(linha, "%s %d", comando, &id);
        inserirFim(lista, veiculos[pesquisar(veiculos, quantidade, id)]);
    } else if (strcmp(comando, "I*") == 0) {
        sscanf(linha, "%s %d %d", comando, &posicao, &id);
        inserir(lista, veiculos[pesquisar(veiculos, quantidade, id)], posicao);
    } else if (strcmp(comando, "RI") == 0) {
        removido = removerInicio(lista);
        imprimirRemovido(removido);
    } else if (strcmp(comando, "RF") == 0) {
        removido = removerFim(lista);
        imprimirRemovido(removido);
    } else if (strcmp(comando, "R*") == 0) {
        sscanf(linha, "%s %d", comando, &posicao);
        removido = remover(lista, posicao);
        imprimirRemovido(removido);
    }
}

//metodo principal que le a entrada e processa as operacoes da lista
int main() {
    Veiculo veiculos[1000];
    int quantidade = lerArquivo(veiculos);
    Lista lista;
    int id;
    int quantidadeComandos;
    char linha[100];

    iniciarLista(&lista);

    scanf("%d", &id);

    while (id != -1) {
        int posicao = pesquisar(veiculos, quantidade, id);

        if (posicao != -1) {
            inserirFim(&lista, veiculos[posicao]);
        }

        scanf("%d", &id);
    }

    scanf("%d", &quantidadeComandos);
    getchar();

    for (int i = 0; i < quantidadeComandos; i++) {
        fgets(linha, 100, stdin);
        removerQuebraLinha(linha);
        executarComando(linha, &lista, veiculos, quantidade);
    }

    mostrar(&lista);

    return 0;
}
