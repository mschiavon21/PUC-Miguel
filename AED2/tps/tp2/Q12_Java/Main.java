import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws Exception {
        Veiculo[] base = LeitorCsv.ler("/tmp/veiculos.csv");
        Pilha pilha = new Pilha();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String linha;
        while ((linha = br.readLine()) != null) {
            int id = Integer.parseInt(linha);
            if (id == -1) break;
            Veiculo v = buscar(base, id);
            if (v != null) pilha.inserir(v);
        }
        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++) {
            String[] cmd = br.readLine().split(" ");
            if (cmd[0].equals("I")) {
                pilha.inserir(buscar(base, Integer.parseInt(cmd[1])));
            } else if (cmd[0].equals("R")) {
                Veiculo v = pilha.remover();
                System.out.println("(R) " + v.getMarca() + " " + v.getModelo());
            }
        }
        pilha.mostrar();
    }

    public static Veiculo buscar(Veiculo[] base, int id) {
        for (int i = 0; i < base.length; i++) if (base[i].getId() == id) return base[i];
        return null;
    }
}
