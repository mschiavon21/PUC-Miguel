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
        for (int i = 1; i < n; i++) {
            Veiculo tmp = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j].getMarca().compareTo(tmp.getMarca()) > 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = tmp;
        }
        for (int i = 0; i < n; i++) System.out.println(arr[i].format());
    }

    public static Veiculo buscar(Veiculo[] base, int id) {
        for (int i = 0; i < base.length; i++) if (base[i].getId() == id) return base[i];
        return null;
    }
}
