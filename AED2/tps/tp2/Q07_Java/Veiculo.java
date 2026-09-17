public class Veiculo {
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

    public Veiculo(int id, String marca, String modelo, int ano, String categoria,
                   String[] combustivel, int cilindros, double cilindrada,
                   String transmissao, String tracao, double consumoCidade,
                   double consumoEstrada, double co2, boolean turbo, Data dataRegistro) {
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

    public static Veiculo parseVeiculo(String s) {
        String[] p = s.split(",");
        String[] combustiveis = p[5].split(";");
        return new Veiculo(
            Integer.parseInt(p[0]), p[1], p[2], Integer.parseInt(p[3]), p[4],
            combustiveis, Integer.parseInt(p[6]), Double.parseDouble(p[7]),
            p[8], p[9], Double.parseDouble(p[10]), Double.parseDouble(p[11]),
            Double.parseDouble(p[12]), Boolean.parseBoolean(p[13]), Data.parseData(p[14])
        );
    }

    public String format() {
        StringBuilder combustiveis = new StringBuilder();
        combustiveis.append("[");
        for (int i = 0; i < combustivel.length; i++) {
            if (i > 0) combustiveis.append(";");
            combustiveis.append(combustivel[i]);
        }
        combustiveis.append("]");
        return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano + " ## " +
               categoria + " ## " + combustiveis + " ## " + cilindros + " ## " +
               Double.toString(cilindrada) + " ## " + transmissao + " ## " + tracao + " ## " +
               Double.toString(consumoCidade) + " ## " + Double.toString(consumoEstrada) +
               " ## " + Double.toString(co2) + " ## " + turbo + " ## " + dataRegistro.format() + "]";
    }

    public int getId() { return id; }
    public String getMarca() { return marca; }
    public String getModelo() { return modelo; }
    public int getAno() { return ano; }
    public String getCategoria() { return categoria; }
    public String[] getCombustivel() { return combustivel; }
    public int getCilindros() { return cilindros; }
    public double getCilindrada() { return cilindrada; }
    public String getTransmissao() { return transmissao; }
    public String getTracao() { return tracao; }
    public double getConsumoCidade() { return consumoCidade; }
    public double getConsumoEstrada() { return consumoEstrada; }
    public double getCo2() { return co2; }
    public boolean isTurbo() { return turbo; }
    public Data getDataRegistro() { return dataRegistro; }

    public void setId(int id) { this.id = id; }
    public void setMarca(String marca) { this.marca = marca; }
    public void setModelo(String modelo) { this.modelo = modelo; }
    public void setAno(int ano) { this.ano = ano; }
    public void setCategoria(String categoria) { this.categoria = categoria; }
    public void setCombustivel(String[] combustivel) { this.combustivel = combustivel; }
    public void setCilindros(int cilindros) { this.cilindros = cilindros; }
    public void setCilindrada(double cilindrada) { this.cilindrada = cilindrada; }
    public void setTransmissao(String transmissao) { this.transmissao = transmissao; }
    public void setTracao(String tracao) { this.tracao = tracao; }
    public void setConsumoCidade(double consumoCidade) { this.consumoCidade = consumoCidade; }
    public void setConsumoEstrada(double consumoEstrada) { this.consumoEstrada = consumoEstrada; }
    public void setCo2(double co2) { this.co2 = co2; }
    public void setTurbo(boolean turbo) { this.turbo = turbo; }
    public void setDataRegistro(Data dataRegistro) { this.dataRegistro = dataRegistro; }
}
