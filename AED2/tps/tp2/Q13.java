import java.io.*;
import java.util.*;

public class Q13 {

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
        Celula anterior;
        Celula proximo;

        Celula(Veiculo elemento) {
            this.elemento = elemento;
        }
    }

    static class Lista {
        Celula primeiro;
        Celula ultimo;
        int tamanho;

        void inserirInicio(Veiculo v) {
            Celula nova = new Celula(v);

            nova.proximo = primeiro;

            if (primeiro != null)
                primeiro.anterior = nova;
            else
                ultimo = nova;

            primeiro = nova;
            tamanho++;
        }

        void inserirFim(Veiculo v) {
            Celula nova = new Celula(v);

            nova.anterior = ultimo;

            if (ultimo != null)
                ultimo.proximo = nova;
            else
                primeiro = nova;

            ultimo = nova;
            tamanho++;
        }

        void inserir(Veiculo v, int posicao) {
            if (posicao == 0) {
                inserirInicio(v);
                return;
            }

            if (posicao == tamanho) {
                inserirFim(v);
                return;
            }

            Celula atual = primeiro;

            for (int i = 0; i < posicao; i++)
                atual = atual.proximo;

            Celula nova = new Celula(v);

            nova.anterior = atual.anterior;
            nova.proximo = atual;

            atual.anterior.proximo = nova;
            atual.anterior = nova;

            tamanho++;
        }

        Veiculo removerInicio() {
            Veiculo v = primeiro.elemento;

            primeiro = primeiro.proximo;

            if (primeiro != null)
                primeiro.anterior = null;
            else
                ultimo = null;

            tamanho--;

            return v;
        }

        Veiculo removerFim() {
            Veiculo v = ultimo.elemento;

            ultimo = ultimo.anterior;

            if (ultimo != null)
                ultimo.proximo = null;
            else
                primeiro = null;

            tamanho--;

            return v;
        }

        Veiculo remover(int posicao) {
            if (posicao == 0)
                return removerInicio();

            if (posicao == tamanho - 1)
                return removerFim();

            Celula atual = primeiro;

            for (int i = 0; i < posicao; i++)
                atual = atual.proximo;

            atual.anterior.proximo = atual.proximo;
            atual.proximo.anterior = atual.anterior;

            tamanho--;

            return atual.elemento;
        }

        void mostrar() {
            Celula atual = primeiro;

            while (atual != null) {
                System.out.println(atual.elemento.format());
                atual = atual.proximo;
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

        Lista lista = new Lista();

        BufferedReader entrada = new BufferedReader(
                new InputStreamReader(System.in));

        while ((linha = entrada.readLine()) != null) {
            int id = Integer.parseInt(linha);

            if (id == -1)
                break;

            for (Veiculo v : todos) {
                if (v.id == id) {
                    lista.inserirFim(v);
                    break;
                }
            }
        }

        int n = Integer.parseInt(entrada.readLine());

        for (int i = 0; i < n; i++) {
            String[] partes = entrada.readLine().split(" ");

            if (partes[0].equals("II")) {
                int id = Integer.parseInt(partes[1]);

                for (Veiculo v : todos) {
                    if (v.id == id) {
                        lista.inserirInicio(v);
                        break;
                    }
                }

            } else if (partes[0].equals("IF")) {
                int id = Integer.parseInt(partes[1]);

                for (Veiculo v : todos) {
                    if (v.id == id) {
                        lista.inserirFim(v);
                        break;
                    }
                }

            } else if (partes[0].equals("I*")) {
                int posicao = Integer.parseInt(partes[1]);
                int id = Integer.parseInt(partes[2]);

                for (Veiculo v : todos) {
                    if (v.id == id) {
                        lista.inserir(v, posicao);
                        break;
                    }
                }

            } else if (partes[0].equals("RI")) {
                Veiculo v = lista.removerInicio();
                System.out.println("(R) " + v.marca + " " + v.modelo);

            } else if (partes[0].equals("RF")) {
                Veiculo v = lista.removerFim();
                System.out.println("(R) " + v.marca + " " + v.modelo);

            } else if (partes[0].equals("R*")) {
                int posicao = Integer.parseInt(partes[1]);

                Veiculo v = lista.remover(posicao);
                System.out.println("(R) " + v.marca + " " + v.modelo);
            }
        }

        lista.mostrar();
    }
}