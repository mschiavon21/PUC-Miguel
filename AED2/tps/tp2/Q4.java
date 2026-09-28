import java.io.*;
import java.util.*;

public class Q4 {

    static class Data {
        int dia, mes, ano;

        Data(int dia, int mes, int ano) {
            this.dia = dia;
            this.mes = mes;
            this.ano = ano;
        }

        String format() {
            return String.format("%02d/%02d/%04d", dia, mes, ano);
        }
    }

    static class Veiculo {
        int id;
        String marca, modelo;
        int ano;
        String categoria, combustivel;
        int cilindros;
        double cilindrada;
        String transmissao, tracao;
        double consumoCidade, consumoEstrada, co2;
        boolean turbo;
        Data dataRegistro;

        Veiculo(String linha) {
            String[] p = linha.split(",");

            id = Integer.parseInt(p[0]);
            marca = p[1];
            modelo = p[2];
            ano = Integer.parseInt(p[3]);
            categoria = p[4];
            combustivel = p[5];
            cilindros = Integer.parseInt(p[6]);
            cilindrada = Double.parseDouble(p[7]);
            transmissao = p[8];
            tracao = p[9];
            consumoCidade = Double.parseDouble(p[10]);
            consumoEstrada = Double.parseDouble(p[11]);
            co2 = Double.parseDouble(p[12]);
            turbo = Boolean.parseBoolean(p[13]);

            String[] d = p[14].split("-");
            dataRegistro = new Data(
                    Integer.parseInt(d[2]),
                    Integer.parseInt(d[1]),
                    Integer.parseInt(d[0])
            );
        }

        String format() {
            return "[" + id + " ## " + marca + " ## " + modelo +
                    " ## " + ano + " ## " + categoria + " ## [" +
                    combustivel + "] ## " + cilindros + " ## " +
                    cilindrada + " ## " + transmissao + " ## " +
                    tracao + " ## " + consumoCidade + " ## " +
                    consumoEstrada + " ## " + co2 + " ## " +
                    turbo + " ## " + dataRegistro.format() + "]";
        }
    }

    static void inserir(Veiculo[] v, int n) {
        for (int i = 1; i < n; i++) {
            Veiculo tmp = v[i];
            int j = i - 1;

            while (j >= 0 && v[j].marca.compareTo(tmp.marca) > 0) {
                v[j + 1] = v[j];
                j--;
            }

            v[j + 1] = tmp;
        }
    }

    public static void main(String[] args) throws Exception {
        ArrayList<Veiculo> todos = new ArrayList<>();

        BufferedReader arq = new BufferedReader(
                new FileReader("/tmp/veiculos.csv"));

        arq.readLine();

        String linha;

        while ((linha = arq.readLine()) != null) {
            if (!linha.trim().isEmpty()) {
                todos.add(new Veiculo(linha));
            }
        }

        arq.close();

        ArrayList<Veiculo> selecionados = new ArrayList<>();

        BufferedReader entrada = new BufferedReader(
                new InputStreamReader(System.in));

        while ((linha = entrada.readLine()) != null) {
            int id = Integer.parseInt(linha);

            if (id == -1) break;

            for (Veiculo v : todos) {
                if (v.id == id) {
                    selecionados.add(v);
                    break;
                }
            }
        }

        Veiculo[] v = selecionados.toArray(new Veiculo[0]);

        inserir(v, v.length);

        for (Veiculo veiculo : v) {
            System.out.println(veiculo.format());
        }
    }
}