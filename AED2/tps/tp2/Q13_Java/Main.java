import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws Exception {
        Veiculo[] base = LeitorCsv.ler("/tmp/veiculos.csv");
        ListaDupla lista = new ListaDupla();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String linha;
        while ((linha = br.readLine()) != null) {
            int id = Integer.parseInt(linha);
            if (id == -1) break;
            Veiculo v = buscar(base, id);
            if (v != null) lista.inserirFim(v);
        }
        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++) {
            String[] cmd = br.readLine().split(" ");
            String op = cmd[0];
            if (op.equals("II")) lista.inserirInicio(buscar(base, Integer.parseInt(cmd[1])));
            else if (op.equals("IF")) lista.inserirFim(buscar(base, Integer.parseInt(cmd[1])));
            else if (op.equals("I*")) lista.inserir(buscar(base, Integer.parseInt(cmd[2])), Integer.parseInt(cmd[1]));
            else if (op.equals("RI")) { Veiculo v = lista.removerInicio(); System.out.println("(R) " + v.getMarca() + " " + v.getModelo()); }
            else if (op.equals("RF")) { Veiculo v = lista.removerFim(); System.out.println("(R) " + v.getMarca() + " " + v.getModelo()); }
            else if (op.equals("R*")) { Veiculo v = lista.remover(Integer.parseInt(cmd[1])); System.out.println("(R) " + v.getMarca() + " " + v.getModelo()); }
        }
        lista.mostrar();
    }

    public static Veiculo buscar(Veiculo[] base, int id) {
        for (int i = 0; i < base.length; i++) if (base[i].getId() == id) return base[i];
        return null;
    }
}
