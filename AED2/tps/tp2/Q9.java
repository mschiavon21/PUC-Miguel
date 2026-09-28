import java.io.*;

public class Q9 {

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
            return String.format(
                    "%02d/%02d/%04d",
                    dia,
                    mes,
                    ano
            );
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

        public String getMarca() {
            return marca;
        }

        public String getModelo() {
            return modelo;
        }

        public String format() {

            return "[" +
                    id +
                    " ## " +
                    marca +
                    " ## " +
                    modelo +
                    " ## " +
                    ano +
                    " ## " +
                    categoria +
                    " ## [" +
                    combustivel +
                    "] ## " +
                    cilindros +
                    " ## " +
                    cilindrada +
                    " ## " +
                    transmissao +
                    " ## " +
                    tracao +
                    " ## " +
                    consumoCidade +
                    " ## " +
                    consumoEstrada +
                    " ## " +
                    co2 +
                    " ## " +
                    turbo +
                    " ## " +
                    dataRegistro.format() +
                    "]";
        }
    }

    static class Lista {

        private Veiculo[] array;
        private int n;

        public Lista(int tamanho) {
            array = new Veiculo[tamanho];
            n = 0;
        }

        public void inserirInicio(Veiculo veiculo) {

            for (int i = n; i > 0; i--) {
                array[i] = array[i - 1];
            }

            array[0] = veiculo;
            n++;
        }

        public void inserir(Veiculo veiculo, int posicao) {

            for (int i = n; i > posicao; i--) {
                array[i] = array[i - 1];
            }

            array[posicao] = veiculo;
            n++;
        }

        public void inserirFim(Veiculo veiculo) {

            array[n] = veiculo;
            n++;
        }

        public Veiculo removerInicio() {

            Veiculo removido = array[0];

            for (int i = 0; i < n - 1; i++) {
                array[i] = array[i + 1];
            }

            n--;

            return removido;
        }

        public Veiculo remover(int posicao) {

            Veiculo removido = array[posicao];

            for (int i = posicao; i < n - 1; i++) {
                array[i] = array[i + 1];
            }

            n--;

            return removido;
        }

        public Veiculo removerFim() {

            n--;

            return array[n];
        }

        public void mostrar() {

            for (int i = 0; i < n; i++) {
                System.out.println(
                        array[i].format()
                );
            }
        }
    }

    static Veiculo procurar(
            Veiculo[] veiculos,
            int total,
            int id) {

        for (int i = 0; i < total; i++) {

            if (veiculos[i].getId() == id) {
                return veiculos[i];
            }
        }

        return null;
    }

    public static void main(String[] args)
            throws Exception {

        Veiculo[] veiculos =
                new Veiculo[10000];

        int total = 0;

        BufferedReader arquivo =
                new BufferedReader(
                        new FileReader(
                                "/tmp/veiculos.csv"
                        )
                );

        arquivo.readLine();

        String linha;

        while ((linha =
                arquivo.readLine()) != null) {

            linha = linha.trim();

            if (!linha.isEmpty()) {

                veiculos[total] =
                        new Veiculo(linha);

                total++;
            }
        }

        arquivo.close();

        Lista lista = new Lista(10000);

        BufferedReader entrada =
                new BufferedReader(
                        new InputStreamReader(
                                System.in
                        )
                );

        /*
         * PRIMEIRA PARTE:
         * IDs até -1.
         */

        while ((linha =
                entrada.readLine()) != null) {

            int id = Integer.parseInt(
                    linha.trim()
            );

            if (id == -1) {
                break;
            }

            Veiculo veiculo =
                    procurar(
                            veiculos,
                            total,
                            id
                    );

            if (veiculo != null) {
                lista.inserirFim(veiculo);
            }
        }

        /*
         * SEGUNDA PARTE:
         * quantidade de comandos.
         */

        linha = entrada.readLine();

        if (linha == null) {
            lista.mostrar();
            return;
        }

        int quantidade =
                Integer.parseInt(
                        linha.trim()
                );

        for (int i = 0;
             i < quantidade;
             i++) {

            linha =
                    entrada.readLine();

            String[] partes =
                    linha.split(" ");

            String comando =
                    partes[0];

            if (comando.equals("II")) {

                int id =
                        Integer.parseInt(
                                partes[1]
                        );

                Veiculo veiculo =
                        procurar(
                                veiculos,
                                total,
                                id
                        );

                lista.inserirInicio(
                        veiculo
                );

            } else if (comando.equals("I*")) {

                int posicao =
                        Integer.parseInt(
                                partes[1]
                        );

                int id =
                        Integer.parseInt(
                                partes[2]
                        );

                Veiculo veiculo =
                        procurar(
                                veiculos,
                                total,
                                id
                        );

                lista.inserir(
                        veiculo,
                        posicao
                );

            } else if (comando.equals("IF")) {

                int id =
                        Integer.parseInt(
                                partes[1]
                        );

                Veiculo veiculo =
                        procurar(
                                veiculos,
                                total,
                                id
                        );

                lista.inserirFim(
                        veiculo
                );

            } else if (comando.equals("RI")) {

                Veiculo removido =
                        lista.removerInicio();

                System.out.println(
                        "(R) " +
                        removido.getMarca() +
                        " " +
                        removido.getModelo()
                );

            } else if (comando.equals("R*")) {

                int posicao =
                        Integer.parseInt(
                                partes[1]
                        );

                Veiculo removido =
                        lista.remover(
                                posicao
                        );

                System.out.println(
                        "(R) " +
                        removido.getMarca() +
                        " " +
                        removido.getModelo()
                );

            } else if (comando.equals("RF")) {

                Veiculo removido =
                        lista.removerFim();

                System.out.println(
                        "(R) " +
                        removido.getMarca() +
                        " " +
                        removido.getModelo()
                );
            }
        }

        lista.mostrar();
    }
}