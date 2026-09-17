import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws Exception {
        Veiculo[] base = LeitorCsv.ler("/tmp/veiculos.csv");
        Veiculo[] arr = new Veiculo[base.length];
        int n = 0;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String linha;

        while ((linha = br.readLine()) != null) {
            int id = Integer.parseInt(linha);
            if (id == -1) break;
            Veiculo v = buscar(base, id);
            if (v != null) arr[n++] = v;
        }

        Veiculo[][] baldes = new Veiculo[10][n == 0 ? 1 : n];
        int[] tamanhos = new int[10];

        for (int i = 0; i < n; i++) {
            double normalizado = arr[i].getCilindrada() / 8.1;
            int indice = (int)(normalizado * 10.0);
            if (indice < 0) indice = 0;
            if (indice >= 10) indice = 9;

            int pos = tamanhos[indice];
            while (pos > 0 && baldes[indice][pos - 1].getCilindrada() > arr[i].getCilindrada()) {
                baldes[indice][pos] = baldes[indice][pos - 1];
                pos--;
            }
            baldes[indice][pos] = arr[i];
            tamanhos[indice]++;
        }

        int k = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < tamanhos[i]; j++) arr[k++] = baldes[i][j];
        }

        for (int i = 0; i < n; i++) System.out.println(arr[i].format());
    }

    public static Veiculo buscar(Veiculo[] base, int id) {
        for (int i = 0; i < base.length; i++) if (base[i].getId() == id) return base[i];
        return null;
    }
}
