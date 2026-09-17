public class Lista {
    private Veiculo[] array;
    private int n;

    public Lista() {
        array = new Veiculo[5000];
        n = 0;
    }

    public void inserirInicio(Veiculo v) {
        for (int i = n; i > 0; i--) array[i] = array[i - 1];
        array[0] = v;
        n++;
    }

    public void inserir(Veiculo v, int posicao) {
        for (int i = n; i > posicao; i--) array[i] = array[i - 1];
        array[posicao] = v;
        n++;
    }

    public void inserirFim(Veiculo v) {
        array[n++] = v;
    }

    public Veiculo removerInicio() {
        Veiculo resp = array[0];
        for (int i = 0; i < n - 1; i++) array[i] = array[i + 1];
        array[--n] = null;
        return resp;
    }

    public Veiculo remover(int posicao) {
        Veiculo resp = array[posicao];
        for (int i = posicao; i < n - 1; i++) array[i] = array[i + 1];
        array[--n] = null;
        return resp;
    }

    public Veiculo removerFim() {
        Veiculo resp = array[--n];
        array[n] = null;
        return resp;
    }

    public int tamanho() { return n; }
    public Veiculo get(int i) { return array[i]; }
}
