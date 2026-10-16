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

//troca dois veiculos de posicao no vetor
void trocar(Veiculo veiculos[], int i, int j) {
    Veiculo tmp = veiculos[i];
    veiculos[i] = veiculos[j];
    veiculos[j] = tmp;
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

//ordena os veiculos por modelo usando selecao
void ordenarSelecao(Veiculo veiculos[], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < quantidade; j++) {
            if (compararModelo(veiculos[j].modelo, veiculos[menor].modelo) < 0) {
                menor = j;
            }
        }

        trocar(veiculos, i, menor);
    }
}

//metodo principal que le a entrada e guarda os veiculos encontrados
int main() {
    Veiculo veiculos[1000];
    Veiculo selecionados[1000];
    int quantidade = lerArquivo(veiculos);
    int quantidadeSelecionados = 0;
    int id;

    scanf("%d", &id);

    while (id != -1) {
        int posicao = pesquisar(veiculos, quantidade, id);

        if (posicao != -1) {
            selecionados[quantidadeSelecionados] = veiculos[posicao];
            quantidadeSelecionados++;
        }

        scanf("%d", &id);
    }

    ordenarSelecao(selecionados, quantidadeSelecionados);

    for (int i = 0; i < quantidadeSelecionados; i++) {
        imprimirVeiculo(selecionados[i]);
    }

    return 0;
}
