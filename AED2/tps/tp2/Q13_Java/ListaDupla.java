public class ListaDupla {
    private No primeiro;
    private No ultimo;
    private int n;

    private static class No {
        Veiculo elemento;
        No ant;
        No prox;
        No(Veiculo elemento) { this.elemento = elemento; }
    }

    public void inserirInicio(Veiculo v) {
        No novo = new No(v);
        if (n == 0) primeiro = ultimo = novo;
        else { novo.prox = primeiro; primeiro.ant = novo; primeiro = novo; }
        n++;
    }

    public void inserirFim(Veiculo v) {
        No novo = new No(v);
        if (n == 0) primeiro = ultimo = novo;
        else { novo.ant = ultimo; ultimo.prox = novo; ultimo = novo; }
        n++;
    }

    public void inserir(Veiculo v, int pos) {
        if (pos == 0) { inserirInicio(v); return; }
        if (pos == n) { inserirFim(v); return; }
        No atual = getNode(pos);
        No novo = new No(v);
        novo.ant = atual.ant;
        novo.prox = atual;
        atual.ant.prox = novo;
        atual.ant = novo;
        n++;
    }

    public Veiculo removerInicio() {
        Veiculo v = primeiro.elemento;
        primeiro = primeiro.prox;
        if (primeiro == null) ultimo = null;
        else primeiro.ant = null;
        n--;
        return v;
    }

    public Veiculo removerFim() {
        Veiculo v = ultimo.elemento;
        ultimo = ultimo.ant;
        if (ultimo == null) primeiro = null;
        else ultimo.prox = null;
        n--;
        return v;
    }

    public Veiculo remover(int pos) {
        if (pos == 0) return removerInicio();
        if (pos == n - 1) return removerFim();
        No atual = getNode(pos);
        atual.ant.prox = atual.prox;
        atual.prox.ant = atual.ant;
        n--;
        return atual.elemento;
    }

    private No getNode(int pos) {
        if (pos < n / 2) {
            No i = primeiro;
            for (int j = 0; j < pos; j++) i = i.prox;
            return i;
        }
        No i = ultimo;
        for (int j = n - 1; j > pos; j--) i = i.ant;
        return i;
    }

    public void mostrar() {
        for (No i = primeiro; i != null; i = i.prox) System.out.println(i.elemento.format());
    }
}
