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

//compara o consumo na estrada e usa a marca para desempatar
int comparar(Veiculo primeiro, Veiculo segundo) {
    int resposta = 0;
    if (primeiro.consumoEstrada < segundo.consumoEstrada) {
        resposta = -1;
    } else if (primeiro.consumoEstrada > segundo.consumoEstrada) {
        resposta = 1;
    } else {
        resposta = strcmp(primeiro.marca, segundo.marca);
    }
    return resposta;
}

//troca dois registros do vetor
void trocar(Veiculo veiculos[], int i, int j) {
    Veiculo tmp = veiculos[i];
    veiculos[i] = veiculos[j];
    veiculos[j] = tmp;
}

//ordena os tres candidatos e devolve o valor mediano como pivo
Veiculo escolherPivo(Veiculo veiculos[], int esq, int dir) {
    int meio = esq + (dir - esq) / 2;
    if (comparar(veiculos[esq], veiculos[meio]) > 0) {
        trocar(veiculos, esq, meio);
    }
    if (comparar(veiculos[esq], veiculos[dir]) > 0) {
        trocar(veiculos, esq, dir);
    }
    if (comparar(veiculos[meio], veiculos[dir]) > 0) {
        trocar(veiculos, meio, dir);
    }
    return veiculos[meio];
}

//particiona como no exemplo do professor e ordena os dois intervalos menores
void quicksortRec(Veiculo veiculos[], int esq, int dir) {
    if (esq < dir) {
        int i = esq;
        int j = dir;
        Veiculo pivo = escolherPivo(veiculos, esq, dir);
        while (i <= j) {
            while (comparar(veiculos[i], pivo) < 0) {
                i++;
            }
            while (comparar(veiculos[j], pivo) > 0) {
                j--;
            }
            if (i <= j) {
                trocar(veiculos, i, j);
                i++;
                j--;
            }
        }
        if (esq < j) {
            quicksortRec(veiculos, esq, j);
        }
        if (i < dir) {
            quicksortRec(veiculos, i, dir);
        }
    }
}

//inicia a ordenacao, inclusive quando nao ha registros selecionados
void ordenar(Veiculo veiculos[], int quantidade) {
    quicksortRec(veiculos, 0, quantidade - 1);
}

//le os ids ate -1 ou EOF, preservando todas as repeticoes
int main(void) {
    Veiculo veiculos[1000];
    int quantidade = lerArquivo(veiculos);
    int capacidade = 1000;
    Veiculo *selecionados = malloc((size_t) capacidade * sizeof(Veiculo));
    int quantidadeSelecionados = 0;
    int id;
    if (selecionados == NULL) {
        return EXIT_FAILURE;
    }
    while (lerId(&id) && id != -1) {
        int posicao = pesquisar(veiculos, quantidade, id);
        if (posicao != -1) {
            if (quantidadeSelecionados == capacidade) {
                capacidade *= 2;
                Veiculo *tmp = realloc(selecionados, (size_t) capacidade * sizeof(Veiculo));
                if (tmp == NULL) {
                    free(selecionados);
                    return EXIT_FAILURE;
                }
                selecionados = tmp;
            }
            selecionados[quantidadeSelecionados++] = veiculos[posicao];
        }
    }
    ordenar(selecionados, quantidadeSelecionados);
    for (int i = 0; i < quantidadeSelecionados; i++) {
        imprimirVeiculo(selecionados[i]);
    }
    free(selecionados);
    return 0;
}
