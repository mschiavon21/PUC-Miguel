import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws Exception {
        Veiculo[] base = LeitorCsv.ler("/tmp/veiculos.csv");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String linha;
        while ((linha = br.readLine()) != null) {
            int id = Integer.parseInt(linha);
            if (id == -1) break;
            Veiculo encontrado = buscar(base, id);
            if (encontrado != null) System.out.println(encontrado.format());
        }
    }

    public static Veiculo buscar(Veiculo[] base, int id) {
        for (int i = 0; i < base.length; i++) {
            if (base[i].getId() == id) return base[i];
        }
        return null;
    }
}
