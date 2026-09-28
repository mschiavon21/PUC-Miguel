import java.io.*;

public class Q7 {

    static class Data {
        private int dia;
        private int mes;
        private int ano;

        public Data(int dia, int mes, int ano) {
            this.dia = dia;
            this.mes = mes;
            this.ano = ano;
        }

        public String format() {
            return String.format("%02d/%02d/%04d", dia, mes, ano);
        }
    }

    static class Veiculo {
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

        public Veiculo(String linha) {
            String[] partes = linha.split(",", -1);

            id = Integer.parseInt(partes[0]);
            marca = partes[1];
            modelo = partes[2];
            ano = Integer.parseInt(partes[3]);
            categoria = partes[4];
            combustivel = partes[5];
            cilindros = Integer.parseInt(partes[6]);
            cilindrada = Double.parseDouble(partes[7]);
            transmissao = partes[8];
            tracao = partes[9];
            consumoCidade = Double.parseDouble(partes[10]);
            consumoEstrada = Double.parseDouble(partes[11]);
            co2 = Double.parseDouble(partes[12]);
            turbo = Boolean.parseBoolean(partes[13]);

            String[] data = partes[14].split("-");

            dataRegistro = new Data(
                    Integer.parseInt(data[2]),
                    Integer.parseInt(data[1]),
                    Integer.parseInt(data[0])
            );
        }

        public int getId() {
            return id;
        }

        public double getCilindrada() {
            return cilindrada;
        }

        public String format() {
            return "[" + id +
                    " ## " + marca +
                    " ## " + modelo +
                    " ## " + ano +
                    " ## " + categoria +
                    " ## [" + combustivel + "]" +
                    " ## " + cilindros +
                    " ## " + cilindrada +
                    " ## " + transmissao +
                    " ## " + tracao +
                    " ## " + consumoCidade +
                    " ## " + consumoEstrada +
                    " ## " + co2 +
                    " ## " + turbo +
                    " ## " + dataRegistro.format() +
                    "]";
        }

        public String getMarca() {
            return marca;
        }

        public String getModelo() {
            return modelo;
        }
    }

    static class Balde {
        private Veiculo[] elementos;
        private int tamanho;

        public Balde() {
            elementos = new Veiculo[10000];
            tamanho = 0;
        }

        public void inserirOrdenado(Veiculo veiculo) {
            int i = tamanho - 1;

            while (i >= 0 &&
                   elementos[i].getCilindrada() > veiculo.getCilindrada()) {

                elementos[i + 1] = elementos[i];
                i--;
            }

            elementos[i + 1] = veiculo;
            tamanho++;
        }

        public int getTamanho() {
            return tamanho;
        }

        public Veiculo get(int posicao) {
            return elementos[posicao];
        }
    }

    static int calcularBalde(Veiculo veiculo) {
        double normalizado = veiculo.getCilindrada() / 8.1;

        int balde = (int)(normalizado * 10.0);

        if (balde < 0) {
            balde = 0;
        }

        if (balde >= 10) {
            balde = 9;
        }

        return balde;
    }

    public static void main(String[] args) throws Exception {

        Veiculo[] veiculos = new Veiculo[10000];

        int total = 0;

        BufferedReader arquivo = new BufferedReader(
                new FileReader("/tmp/veiculos.csv")
        );

        arquivo.readLine();

        String linha;

        while ((linha = arquivo.readLine()) != null) {

            if (linha.length() > 0) {
                veiculos[total] = new Veiculo(linha);
                total++;
            }
        }

        arquivo.close();

        Veiculo[] selecionados = new Veiculo[10000];

        int quantidade = 0;

        BufferedReader entrada = new BufferedReader(
                new InputStreamReader(System.in)
        );

        while ((linha = entrada.readLine()) != null) {

            int id = Integer.parseInt(linha);

            if (id == -1) {
                break;
            }

            for (int i = 0; i < total; i++) {

                if (veiculos[i].getId() == id) {
                    selecionados[quantidade] = veiculos[i];
                    quantidade++;
                    break;
                }
            }
        }

        Balde[] baldes = new Balde[10];

        for (int i = 0; i < 10; i++) {
            baldes[i] = new Balde();
        }

        for (int i = 0; i < quantidade; i++) {
            int numeroBalde = calcularBalde(selecionados[i]);

            baldes[numeroBalde].inserirOrdenado(selecionados[i]);
        }

        int posicao = 0;

        for (int i = 0; i < 10; i++) {

            for (int j = 0; j < baldes[i].getTamanho(); j++) {

                selecionados[posicao] = baldes[i].get(j);
                posicao++;
            }
        }

        for (int i = 0; i < quantidade; i++) {
            System.out.println(selecionados[i].format());
        }
    }
}