public class Pilha {
    private No topo;

    private static class No {
        Veiculo elemento;
        No prox;
        No(Veiculo elemento, No prox) { this.elemento = elemento; this.prox = prox; }
    }

    public void inserir(Veiculo v) { topo = new No(v, topo); }

    public Veiculo remover() {
        if (topo == null) throw new RuntimeException("Erro");
        Veiculo v = topo.elemento;
        topo = topo.prox;
        return v;
    }

    public void mostrar() {
        for (No i = topo; i != null; i = i.prox) System.out.println(i.elemento.format());
    }
}
