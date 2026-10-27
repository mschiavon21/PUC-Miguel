import java.io.*;
import java.util.*;

public class HeapSort {
    /** Data: imutavel depois de criada, por isso sem metodos set. */
    static class Data {
        private int ano;
        private int mes;
        private int dia;

        public Data(int ano, int mes, int dia) {
            this.ano = ano;
            this.mes = mes;
            this.dia = dia;
        }

        public int getAno() { return ano; }
        public int getMes() { return mes; }
        public int getDia() { return dia; }

        public static Data parseData(String s) {
            s = s.trim();
            if (s.isEmpty()) return new Data(0, 0, 0);
            String[] p = s.split("-");
            return new Data(Integer.parseInt(p[0]), Integer.parseInt(p[1]), Integer.parseInt(p[2]));
        }

        public String format() {
            return String.format("%02d/%02d/%04d", dia, mes, ano);
        }
    }

    /** Veiculo: os dados vem do CSV e nao mudam, por isso apenas get (sem set). */
    static class Veiculo {
        private int id;
        private String marca;
        private String modelo;
        private int ano;
        private String categoria;
        private String[] combustivel;
        private int cilindros;
        private double cilindrada;
        private String transmissao;
        private String tracao;
        private double consumoCidade;
        private double consumoEstrada;
        private double co2;
        private boolean turbo;
        private Data dataRegistro;

        public Veiculo(int id, String marca, String modelo, int ano, String categoria, String[] combustivel,
                       int cilindros, double cilindrada, String transmissao, String tracao,
                       double consumoCidade, double consumoEstrada, double co2, boolean turbo, Data dataRegistro) {
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

        public int getId() { return id; }
        public String getMarca() { return marca; }
        public String getModelo() { return modelo; }
        public int getAno() { return ano; }
        public String getCategoria() { return categoria; }
        public String[] getCombustivel() { return combustivel.clone(); }
        public int getCilindros() { return cilindros; }
        public double getCilindrada() { return cilindrada; }
        public String getTransmissao() { return transmissao; }
        public String getTracao() { return tracao; }
        public double getConsumoCidade() { return consumoCidade; }
        public double getConsumoEstrada() { return consumoEstrada; }
        public double getCo2() { return co2; }
        public boolean isTurbo() { return turbo; }
        public Data getDataRegistro() { return dataRegistro; }

        private static int toInt(String s) {
            s = s.trim();
            return s.isEmpty() ? 0 : Integer.parseInt(s);
        }

        private static double toDouble(String s) {
            s = s.trim();
            return s.isEmpty() ? 0.0 : Double.parseDouble(s);
        }

        /** Divide uma linha CSV respeitando campos entre aspas. */
        private static String[] dividirCsv(String s) {
            ArrayList<String> campos = new ArrayList<>();
            StringBuilder sb = new StringBuilder();
            boolean aspas = false;
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (c == '"') {
                    if (aspas && i + 1 < s.length() && s.charAt(i + 1) == '"') { sb.append('"'); i++; }
                    else aspas = !aspas;
                } else if (c == ',' && !aspas) {
                    campos.add(sb.toString());
                    sb.setLength(0);
                } else {
                    sb.append(c);
                }
            }
            campos.add(sb.toString());
            while (campos.size() < 15) campos.add("");
            return campos.toArray(new String[0]);
        }

        public static Veiculo parseVeiculo(String s) {
            String[] c = dividirCsv(s);
            String comb = c[5].trim();
            String[] combustivel = comb.isEmpty() ? new String[0] : comb.split(";");
            String t = c[13].trim();
            boolean turbo = t.equals("true") || t.equals("True") || t.equals("TRUE");
            return new Veiculo(toInt(c[0]), c[1], c[2], toInt(c[3]), c[4], combustivel,
                    toInt(c[6]), toDouble(c[7]), c[8], c[9],
                    toDouble(c[10]), toDouble(c[11]), toDouble(c[12]), turbo, Data.parseData(c[14]));
        }

        public String format() {
            StringBuilder comb = new StringBuilder();
            for (int i = 0; i < combustivel.length; i++) {
                if (i > 0) comb.append(", ");
                comb.append(combustivel[i]);
            }
            return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano + " ## " + categoria
                    + " ## [" + comb + "] ## " + cilindros + " ## " + String.format("%.1f", cilindrada)
                    + " ## " + transmissao + " ## " + tracao
                    + " ## " + String.format("%.2f", consumoCidade) + " ## " + String.format("%.2f", consumoEstrada)
                    + " ## " + String.format("%.2f", co2) + " ## " + turbo + " ## " + dataRegistro.format() + "]";
        }
    }

    static class LeitorCsv {
        public static Veiculo[] ler(String caminhoArquivo) throws IOException {
            ArrayList<Veiculo> lista = new ArrayList<>();
            BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo));
            String linha;
            boolean primeira = true;
            while ((linha = br.readLine()) != null) {
                if (linha.trim().isEmpty()) continue;
                if (primeira) {
                    primeira = false;
                    if (!Character.isDigit(linha.trim().charAt(0))) continue; // cabecalho
                }
                lista.add(Veiculo.parseVeiculo(linha));
            }
            br.close();
            return lista.toArray(new Veiculo[0]);
        }
    }

    static class Util {
        /** Pesquisa sequencial por id. */
        static Veiculo buscar(Veiculo[] todos, int id) {
            for (int i = 0; i < todos.length; i++) {
                if (todos[i].getId() == id) return todos[i];
            }
            return null;
        }

        /** Le ids da entrada padrao ate -1 e devolve os veiculos correspondentes. */
        static ArrayList<Veiculo> lerSelecionados(BufferedReader br, Veiculo[] todos) throws IOException {
            ArrayList<Veiculo> sel = new ArrayList<>();
            String linha;
            while ((linha = br.readLine()) != null) {
                linha = linha.trim();
                if (linha.isEmpty()) continue;
                int id = Integer.parseInt(linha);
                if (id == -1) break;
                Veiculo v = buscar(todos, id);
                if (v != null) sel.add(v);
            }
            return sel;
        }

        static void imprimirRemovido(Veiculo v) {
            System.out.println("(R) " + v.getMarca() + " " + v.getModelo());
        }
    }

    /** CO2; empate: transmissao. */
    static int cmp(Veiculo a, Veiculo b) {
        int c = Double.compare(a.getCo2(), b.getCo2());
        if (c != 0) return c;
        return a.getTransmissao().compareTo(b.getTransmissao());
    }

    static void swap(Veiculo[] a, int i, int j) {
        Veiculo t = a[i]; a[i] = a[j]; a[j] = t;
    }

    static void reconstruir(Veiculo[] a, int pai, int tam) {
        while (true) {
            int maior = pai, f1 = 2 * pai + 1, f2 = 2 * pai + 2;
            if (f1 < tam && cmp(a[f1], a[maior]) > 0) maior = f1;
            if (f2 < tam && cmp(a[f2], a[maior]) > 0) maior = f2;
            if (maior == pai) return;
            swap(a, pai, maior);
            pai = maior;
        }
    }

    static void heapsort(Veiculo[] a) {
        int n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--) reconstruir(a, i, n);
        for (int tam = n - 1; tam > 0; tam--) {
            swap(a, 0, tam);
            reconstruir(a, 0, tam);
        }
    }

    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        Veiculo[] todos = LeitorCsv.ler("/tmp/veiculos.csv");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Veiculo[] a = Util.lerSelecionados(br, todos).toArray(new Veiculo[0]);
        heapsort(a);
        for (Veiculo v : a) System.out.println(v.format());
    }
}
