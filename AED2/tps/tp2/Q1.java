import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

class Data {
    private int dia;
    private int mes;
    private int ano;

    public Data() {
        this.dia = 1;
        this.mes = 1;
        this.ano = 2000;
    }

    public Data(int dia, int mes, int ano) {
        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
    }

    public int getDia() {
        return dia;
    }

    public int getMes() {
        return mes;
    }

    public int getAno() {
        return ano;
    }

    public String format() {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
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

    public Veiculo(int id, String marca, String modelo, int ano,
                   String categoria, String combustivel, int cilindros,
                   double cilindrada, String transmissao, String tracao,
                   double consumoCidade, double consumoEstrada,
                   double co2, boolean turbo, Data dataRegistro) {

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

    public int getId() {
        return id;
    }

    public String getMarca() {
        return marca;
    }

    public String getModelo() {
        return modelo;
    }

    public int getAno() {
        return ano;
    }

    public String getCategoria() {
        return categoria;
    }

    public String getCombustivel() {
        return combustivel;
    }

    public int getCilindros() {
        return cilindros;
    }

    public double getCilindrada() {
        return cilindrada;
    }

    public String getTransmissao() {
        return transmissao;
    }

    public String getTracao() {
        return tracao;
    }

    public double getConsumoCidade() {
        return consumoCidade;
    }

    public double getConsumoEstrada() {
        return consumoEstrada;
    }

    public double getCo2() {
        return co2;
    }

    public boolean getTurbo() {
        return turbo;
    }

    public Data getDataRegistro() {
        return dataRegistro;
    }

    public String format() {
        return "[" +
                id + " ## " +
                marca + " ## " +
                modelo + " ## " +
                ano + " ## " +
                categoria + " ## [" +
                combustivel + "] ## " +
                cilindros + " ## " +
                cilindrada + " ## " +
                transmissao + " ## " +
                tracao + " ## " +
                consumoCidade + " ## " +
                consumoEstrada + " ## " +
                co2 + " ## " +
                turbo + " ## " +
                dataRegistro.format() +
                "]";
    }
}

public class Q1 {

    public static Veiculo lerVeiculo(String linha) {
        String[] partes = linha.split(",");

        int id = Integer.parseInt(partes[0]);
        String marca = partes[1];
        String modelo = partes[2];
        int ano = Integer.parseInt(partes[3]);
        String categoria = partes[4];
        String combustivel = partes[5];
        int cilindros = Integer.parseInt(partes[6]);
        double cilindrada = Double.parseDouble(partes[7]);
        String transmissao = partes[8];
        String tracao = partes[9];
        double consumoCidade = Double.parseDouble(partes[10]);
        double consumoEstrada = Double.parseDouble(partes[11]);
        double co2 = Double.parseDouble(partes[12]);
        boolean turbo = Boolean.parseBoolean(partes[13]);

        String[] data = partes[14].split("-");

        int anoData = Integer.parseInt(data[0]);
        int mesData = Integer.parseInt(data[1]);
        int diaData = Integer.parseInt(data[2]);

        Data dataRegistro = new Data(diaData, mesData, anoData);

        return new Veiculo(
                id,
                marca,
                modelo,
                ano,
                categoria,
                combustivel,
                cilindros,
                cilindrada,
                transmissao,
                tracao,
                consumoCidade,
                consumoEstrada,
                co2,
                turbo,
                dataRegistro
        );
    }

    public static Veiculo buscarPorId(ArrayList<Veiculo> veiculos, int id) {
        for (int i = 0; i < veiculos.size(); i++) {
            if (veiculos.get(i).getId() == id) {
                return veiculos.get(i);
            }
        }

        return null;
    }

    public static void main(String[] args) throws Exception {

        ArrayList<Veiculo> veiculos = new ArrayList<>();

        BufferedReader arquivo = new BufferedReader(
                new FileReader("/tmp/veiculos.csv")
        );

        String linha = arquivo.readLine();

        while ((linha = arquivo.readLine()) != null) {
            if (!linha.trim().isEmpty()) {
                veiculos.add(lerVeiculo(linha));
            }
        }

        arquivo.close();

        BufferedReader entrada = new BufferedReader(
                new InputStreamReader(System.in)
        );

        String linhaEntrada;

        while ((linhaEntrada = entrada.readLine()) != null) {

            int id = Integer.parseInt(linhaEntrada);

            if (id == -1) {
                break;
            }

            Veiculo veiculo = buscarPorId(veiculos, id);

            if (veiculo != null) {
                System.out.println(veiculo.format());
            }
        }
    }
}