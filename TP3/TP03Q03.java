import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Scanner;

class Data {
    private int dia;
    private int mes;
    private int ano;

    public Data() {
        this.dia = 0;
        this.mes = 0;
        this.ano = 0;
    }

    public Data(int dia, int mes, int ano) {
        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
    }

    //retorna o dia armazenado na data
    public int getDia() {
        return dia;
    }

    //retorna o mes armazenado na data
    public int getMes() {
        return mes;
    }

    //retorna o ano armazenado na data
    public int getAno() {
        return ano;
    }

    //monta a data no formato pedido pelo enunciado
    public String format() {
        return completarZero(dia) + "/" + completarZero(mes) + "/" + ano;
    }

    //adiciona zero a esquerda em dias e meses menores que 10
    public String completarZero(int numero) {
        String resposta = "";

        if (numero < 10) {
            resposta = "0" + numero;
        } else {
            resposta = "" + numero;
        }

        return resposta;
    }
}

class Veiculo {
    private int id;
    private String marca;
    private String modelo;
    private int ano;
    private String categoria;
    private String combustivel;
    private int cilindros;
    private double cilindrada;
    private String transmissao;
    private String tracao;
    private double consumoCidade;
    private double consumoEstrada;
    private double co2;
    private boolean turbo;
    private Data dataRegistro;

    public Veiculo() {
        this.id = 0;
        this.marca = "";
        this.modelo = "";
        this.ano = 0;
        this.categoria = "";
        this.combustivel = "";
        this.cilindros = 0;
        this.cilindrada = 0.0;
        this.transmissao = "";
        this.tracao = "";
        this.consumoCidade = 0.0;
        this.consumoEstrada = 0.0;
        this.co2 = 0.0;
        this.turbo = false;
        this.dataRegistro = new Data();
    }

    public Veiculo(int id, String marca, String modelo, int ano, String categoria,
            String combustivel, int cilindros, double cilindrada, String transmissao,
            String tracao, double consumoCidade, double consumoEstrada, double co2,
            boolean turbo, Data dataRegistro) {
        this.id = id;
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.categoria = categoria;
        this.combustivel = combustivel;
        this.cilindros = cilindros;
        this.cilindrada = cilindrada;
        this.transmissao = transmissao;
        this.tracao = tracao;
        this.consumoCidade = consumoCidade;
        this.consumoEstrada = consumoEstrada;
        this.co2 = co2;
        this.turbo = turbo;
        this.dataRegistro = dataRegistro;
    }

    //retorna o identificador usado nas pesquisas
    public int getId() {
        return id;
    }

    //retorna a marca do veiculo
    public String getMarca() {
        return marca;
    }

    //retorna o modelo do veiculo
    public String getModelo() {
        return modelo;
    }

    //retorna o ano do veiculo
    public int getAno() {
        return ano;
    }

    //retorna a categoria do veiculo
    public String getCategoria() {
        return categoria;
    }

    //retorna o combustivel do veiculo
    public String getCombustivel() {
        return combustivel;
    }

    //retorna a quantidade de cilindros do veiculo
    public int getCilindros() {
        return cilindros;
    }

    //retorna a cilindrada do veiculo
    public double getCilindrada() {
        return cilindrada;
    }

    //retorna a transmissao do veiculo
    public String getTransmissao() {
        return transmissao;
    }

    //retorna o tipo de tracao do veiculo
    public String getTracao() {
        return tracao;
    }

    //retorna o consumo do veiculo na cidade
    public double getConsumoCidade() {
        return consumoCidade;
    }

    //retorna o consumo do veiculo na estrada
    public double getConsumoEstrada() {
        return consumoEstrada;
    }

    //retorna a emissao de co2 do veiculo
    public double getCo2() {
        return co2;
    }

    //retorna se o veiculo possui turbo
    public boolean getTurbo() {
        return turbo;
    }

    //retorna a data de registro do veiculo
    public Data getDataRegistro() {
        return dataRegistro;
    }

    //monta a saida do veiculo exatamente no formato pedido
    public String format() {
        String resposta = "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano
                + " ## " + categoria + " ## [" + combustivel + "] ## " + cilindros
                + " ## " + formatarDouble(cilindrada, 1) + " ## " + transmissao
                + " ## " + tracao + " ## " + formatarDouble(consumoCidade, 2)
                + " ## " + formatarDouble(consumoEstrada, 2) + " ## "
                + formatarDouble(co2, 1) + " ## " + turbo + " ## "
                + dataRegistro.format() + "]";

        return resposta;
    }

    //formata o decimal com primitivos e String, sem depender da configuracao regional
    public String formatarDouble(double numero, int casas) {
        String texto = "" + numero;
        boolean negativo = texto.charAt(0) == '-';
        int inicio = negativo ? 1 : 0;
        String digitos = "";
        int posicaoDecimal = 0;
        boolean ponto = false;
        int i = inicio;
        while (i < texto.length() && texto.charAt(i) != 'E' && texto.charAt(i) != 'e') {
            char c = texto.charAt(i);
            if (c == '.') {
                ponto = true;
            } else {
                digitos += c;
                if (!ponto) {
                    posicaoDecimal++;
                }
            }
            i++;
        }
        if (i < texto.length()) {
            i++;
            int sinal = 1;
            if (texto.charAt(i) == '-' || texto.charAt(i) == '+') {
                sinal = texto.charAt(i) == '-' ? -1 : 1;
                i++;
            }
            int expoente = 0;
            while (i < texto.length()) {
                expoente = expoente * 10 + texto.charAt(i++) - '0';
            }
            posicaoDecimal += sinal * expoente;
        }
        int limite = posicaoDecimal + casas;
        long valor = 0;
        for (i = 0; i < limite; i++) {
            int digito = i < digitos.length() ? digitos.charAt(i) - '0' : 0;
            valor = valor * 10 + digito;
        }
        if (limite >= 0 && limite < digitos.length() && digitos.charAt(limite) >= '5') {
            valor++;
        }
        long fator = 1;
        for (i = 0; i < casas; i++) {
            fator *= 10;
        }
        String resposta = (negativo ? "-" : "") + (valor / fator);
        if (casas > 0) {
            resposta += ".";
            long decimal = valor % fator;
            for (long divisor = fator / 10; divisor > 0; divisor /= 10) {
                resposta += decimal / divisor;
                decimal %= divisor;
            }
        }
        return resposta;
    }
}

public class TP03Q03 {

    //valida sinal, digitos e limite de int; entradas invalidas recebem zero
    public static int lerInteiro(String linha) {
        int i = 0;
        int sinal = 1;
        long valor = 0;
        boolean valido = linha.length() > 0;
        if (valido && (linha.charAt(0) == '-' || linha.charAt(0) == '+')) {
            sinal = linha.charAt(0) == '-' ? -1 : 1;
            i++;
        }
        valido = valido && i < linha.length();
        long limite = sinal < 0 ? 2147483648L : 2147483647L;
        while (valido && i < linha.length()) {
            char c = linha.charAt(i++);
            if (c < '0' || c > '9') {
                valido = false;
            } else if (valor > (limite - (c - '0')) / 10) {
                valido = false;
            } else {
                valor = valor * 10 + c - '0';
            }
        }
        return valido ? (int) (sinal * valor) : 0;
    }

    //troca o ponto e virgula por virgula para imprimir combustiveis compostos
    public static String arrumarCombustivel(String combustivel) {
        String resposta = "";

        for (int i = 0; i < combustivel.length(); i++) {
            if (combustivel.charAt(i) == ';') {
                resposta += ",";
            } else {
                resposta += combustivel.charAt(i);
            }
        }

        return resposta;
    }

    //separa a data do csv e cria um objeto da classe Data
    public static Data lerData(String linha) {
        String[] partes = linha.split("-");

        int ano = Integer.parseInt(partes[0]);
        int mes = Integer.parseInt(partes[1]);
        int dia = Integer.parseInt(partes[2]);

        return new Data(dia, mes, ano);
    }

    //separa os campos da linha do csv e cria um objeto da classe Veiculo
    public static Veiculo lerVeiculo(String linha) {
        String[] partes = linha.split(",");

        int id = Integer.parseInt(partes[0]);
        String marca = partes[1];
        String modelo = partes[2];
        int ano = Integer.parseInt(partes[3]);
        String categoria = partes[4];
        String combustivel = arrumarCombustivel(partes[5]);
        int cilindros = Integer.parseInt(partes[6]);
        double cilindrada = Double.parseDouble(partes[7]);
        String transmissao = partes[8];
        String tracao = partes[9];
        double consumoCidade = Double.parseDouble(partes[10]);
        double consumoEstrada = Double.parseDouble(partes[11]);
        double co2 = Double.parseDouble(partes[12]);
        boolean turbo = Boolean.parseBoolean(partes[13]);
        Data dataRegistro = lerData(partes[14]);

        return new Veiculo(id, marca, modelo, ano, categoria, combustivel, cilindros,
                cilindrada, transmissao, tracao, consumoCidade, consumoEstrada, co2,
                turbo, dataRegistro);
    }

    //le todos os veiculos do arquivo csv e guarda no vetor
    public static int lerArquivo(Veiculo[] veiculos) throws Exception {
        int quantidade = 0;

        BufferedReader arquivo = new BufferedReader(new FileReader("/tmp/veiculos.csv"));

        //pula o cabecalho do arquivo
        String linha = arquivo.readLine();

        while ((linha = arquivo.readLine()) != null) {
            if (linha.length() > 0) {
                if (quantidade == veiculos.length) {
                    arquivo.close();
                    return -1;
                }
                veiculos[quantidade] = lerVeiculo(linha);
                quantidade++;
            }
        }

        arquivo.close();

        return quantidade;
    }

    //procura o veiculo pelo id usando pesquisa sequencial
    public static Veiculo pesquisar(Veiculo[] veiculos, int quantidade, int id) {
        Veiculo resposta = null;

        for (int i = 0; i < quantidade; i++) {
            if (veiculos[i].getId() == id) {
                resposta = veiculos[i];
                i = quantidade;
            }
        }

        return resposta;
    }

    //compara a emissao de co2 e depois o tipo de transmissao
    public static int comparar(Veiculo primeiro, Veiculo segundo) {
        int resposta = 0;
        if (primeiro.getCo2() < segundo.getCo2()) {
            resposta = -1;
        } else if (primeiro.getCo2() > segundo.getCo2()) {
            resposta = 1;
        } else {
            resposta = primeiro.getTransmissao().compareTo(segundo.getTransmissao());
        }
        return resposta;
    }

    //troca duas referencias dentro do heap
    public static void trocar(Veiculo[] veiculos, int i, int j) {
        Veiculo tmp = veiculos[i];
        veiculos[i] = veiculos[j];
        veiculos[j] = tmp;
    }

    //faz o ultimo elemento subir ate restabelecer o heap maximo
    public static void construir(Veiculo[] heap, int tamHeap) {
        for (int i = tamHeap; i > 1 && comparar(heap[i], heap[i / 2]) > 0; i /= 2) {
            trocar(heap, i, i / 2);
        }
    }

    //escolhe o maior filho considerando os dois criterios
    public static int getMaiorFilho(Veiculo[] heap, int i, int tamHeap) {
        int filho = 2 * i;
        if (filho < tamHeap && comparar(heap[filho], heap[filho + 1]) < 0) {
            filho++;
        }
        return filho;
    }

    //faz a raiz descer apos a retirada do maior elemento
    public static void reconstruir(Veiculo[] heap, int tamHeap) {
        int i = 1;
        while (i <= tamHeap / 2) {
            int filho = getMaiorFilho(heap, i, tamHeap);
            if (comparar(heap[i], heap[filho]) < 0) {
                trocar(heap, i, filho);
                i = filho;
            } else {
                i = tamHeap;
            }
        }
    }

    //usa indices a partir de um, como no heapsort do professor
    public static void ordenar(Veiculo[] veiculos, int quantidade) {
        Veiculo[] heap = new Veiculo[quantidade + 1];
        for (int i = 0; i < quantidade; i++) {
            heap[i + 1] = veiculos[i];
        }
        for (int tamHeap = 2; tamHeap <= quantidade; tamHeap++) {
            construir(heap, tamHeap);
        }
        int tamHeap = quantidade;
        while (tamHeap > 1) {
            trocar(heap, 1, tamHeap--);
            reconstruir(heap, tamHeap);
        }
        for (int i = 0; i < quantidade; i++) {
            veiculos[i] = heap[i + 1];
        }
    }

    //le os ids ate -1 ou fim do arquivo e imprime os registros ordenados
    public static void main(String[] args) throws Exception {
        Veiculo[] veiculos = new Veiculo[10000];
        Veiculo[] selecionados = new Veiculo[1000];
        int quantidadeArquivo = lerArquivo(veiculos);
        if (quantidadeArquivo < 0) {
            return;
        }
        int quantidadeSelecionados = 0;
        Scanner entrada = new Scanner(System.in);

        while (entrada.hasNextLine()) {
            int id = lerInteiro(entrada.nextLine());
            if (id == -1) {
                break;
            }
            Veiculo veiculo = pesquisar(veiculos, quantidadeArquivo, id);
            if (veiculo != null) {
                if (quantidadeSelecionados == selecionados.length) {
                    Veiculo[] tmp = new Veiculo[selecionados.length * 2];
                    for (int i = 0; i < quantidadeSelecionados; i++) {
                        tmp[i] = selecionados[i];
                    }
                    selecionados = tmp;
                }
                selecionados[quantidadeSelecionados++] = veiculo;
            }
        }

        ordenar(selecionados, quantidadeSelecionados);
        for (int i = 0; i < quantidadeSelecionados; i++) {
            System.out.println(selecionados[i].format());
        }
        entrada.close();
    }
}
