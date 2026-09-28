import java.io.*;
import java.util.*;

public class Q12 {

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
        int id, ano, cilindros;
        String marca, modelo, categoria, combustivel;
        double cilindrada, consumoCidade, consumoEstrada, co2;
        String transmissao, tracao;
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

    static class Celula {
        Veiculo elemento;
        Celula prox;

        Celula(Veiculo elemento) {
            this.elemento = elemento;
            this.prox = null;
        }
    }

    static class Pilha {
        Celula topo;

        void inserir(Veiculo v) {
            Celula nova = new Celula(v);
            nova.prox = topo;
            topo = nova;
        }

        Veiculo remover() {
            Veiculo v = topo.elemento;
            topo = topo.prox;
            return v;
        }

        void mostrar() {
            Celula atual = topo;

            while (atual != null) {
                System.out.println(atual.elemento.format());
                atual = atual.prox;
            }
        }
    }

    public static void main(String[] args) throws Exception {
        ArrayList<Veiculo> todos = new ArrayList<>();

        BufferedReader arq = new BufferedReader(
                new FileReader("/tmp/veiculos.csv"));

        arq.readLine();

        String linha;

        while ((linha = arq.readLine()) != null) {
            if (!linha.trim().isEmpty())
                todos.add(new Veiculo(linha));
        }

        arq.close();

        Pilha pilha = new Pilha();

        BufferedReader entrada = new BufferedReader(
                new InputStreamReader(System.in));

        while ((linha = entrada.readLine()) != null) {
            int id = Integer.parseInt(linha);

            if (id == -1)
                break;

            for (Veiculo v : todos) {
                if (v.id == id) {
                    pilha.inserir(v);
                    break;
                }
            }
        }

        int n = Integer.parseInt(entrada.readLine());

        for (int i = 0; i < n; i++) {
            String[] partes = entrada.readLine().split(" ");

            if (partes[0].equals("I")) {
                int id = Integer.parseInt(partes[1]);

                for (Veiculo v : todos) {
                    if (v.id == id) {
                        pilha.inserir(v);
                        break;
                    }
                }

            } else if (partes[0].equals("R")) {
                Veiculo v = pilha.remover();
                System.out.println("(R) " + v.marca + " " + v.modelo);
            }
        }

        pilha.mostrar();
    }
}