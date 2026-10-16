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

    //formata os numeros reais com a quantidade de casas decimais da saida
    public String formatarDouble(double numero, int casas) {
        int multiplicador = 1;

        for (int i = 0; i < casas; i++) {
            multiplicador = multiplicador * 10;
        }

        int valor = (int) (numero * multiplicador + 0.5);
        int inteiro = valor / multiplicador;
        int decimal = valor % multiplicador;
        String resposta = inteiro + ".";

        for (int i = 1; i < casas; i++) {
            if (decimal < multiplicador / 10) {
                resposta += "0";
                multiplicador = multiplicador / 10;
            }
        }

        resposta += decimal;

        return resposta;
    }
}

public class TP02Q07 {

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
    public static int lerArquivo(Veiculo[] veiculos) {
        int quantidade = 0;

        Arq.openRead("/tmp/veiculos.csv");

        //pula o cabecalho do arquivo
        String linha = Arq.readLine();

        while (Arq.hasNext() == true) {
            linha = Arq.readLine();
            veiculos[quantidade] = lerVeiculo(linha);
            quantidade++;
        }

        Arq.close();

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

    //ordena um balde por cilindrada usando insercao
    public static void ordenarInsercao(Veiculo[] veiculos, int quantidade) {
        for (int i = 1; i < quantidade; i++) {
            Veiculo tmp = veiculos[i];
            int j = i - 1;

            while (j >= 0 && veiculos[j].getCilindrada() > tmp.getCilindrada()) {
                veiculos[j + 1] = veiculos[j];
                j--;
            }

            veiculos[j + 1] = tmp;
        }
    }

    //descobre em qual balde o veiculo deve ficar
    public static int calcularBalde(Veiculo veiculo) {
        int balde = (int) ((veiculo.getCilindrada() / 8.1) * 10);

        if (balde >= 10) {
            balde = 9;
        }

        return balde;
    }

    //ordena os veiculos por cilindrada usando bucketsort
    public static void bucketsort(Veiculo[] veiculos, int quantidade) {
        Veiculo[][] baldes = new Veiculo[10][1000];
        int[] quantidadeBaldes = new int[10];

        for (int i = 0; i < quantidade; i++) {
            int balde = calcularBalde(veiculos[i]);
            baldes[balde][quantidadeBaldes[balde]] = veiculos[i];
            quantidadeBaldes[balde]++;
        }

        for (int i = 0; i < 10; i++) {
            ordenarInsercao(baldes[i], quantidadeBaldes[i]);
        }

        int posicao = 0;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < quantidadeBaldes[i]; j++) {
                veiculos[posicao] = baldes[i][j];
                posicao++;
            }
        }
    }

    //le os ids da entrada padrao e guarda os veiculos encontrados
    public static void main(String[] args) {
        Veiculo[] veiculos = new Veiculo[10000];
        Veiculo[] selecionados = new Veiculo[10000];
        int quantidadeArquivo = lerArquivo(veiculos);
        int quantidadeSelecionados = 0;
        Scanner entrada = new Scanner(System.in);
        String linha = entrada.nextLine();

        while (linha.equals("-1") == false) {
            int id = Integer.parseInt(linha);
            Veiculo veiculo = pesquisar(veiculos, quantidadeArquivo, id);

            if (veiculo != null) {
                selecionados[quantidadeSelecionados] = veiculo;
                quantidadeSelecionados++;
            }

            linha = entrada.nextLine();
        }

        bucketsort(selecionados, quantidadeSelecionados);

        for (int i = 0; i < quantidadeSelecionados; i++) {
            System.out.println(selecionados[i].format());
        }
    }
}
