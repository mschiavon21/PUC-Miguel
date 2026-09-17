import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws Exception {
        Veiculo[] base = LeitorCsv.ler("/tmp/veiculos.csv");
        Lista lista = new Lista();
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
            Veiculo v;
            if (op.equals("II")) {
                v = buscar(base, Integer.parseInt(cmd[1]));
                lista.inserirInicio(v);
            } else if (op.equals("IF")) {
                v = buscar(base, Integer.parseInt(cmd[1]));
                lista.inserirFim(v);
            } else if (op.equals("I*")) {
                int pos = Integer.parseInt(cmd[1]);
                v = buscar(base, Integer.parseInt(cmd[2]));
                lista.inserir(v, pos);
            } else if (op.equals("RI")) {
                v = lista.removerInicio();
                System.out.println("(R) " + v.getMarca() + " " + v.getModelo());
            } else if (op.equals("RF")) {
                v = lista.removerFim();
                System.out.println("(R) " + v.getMarca() + " " + v.getModelo());
            } else if (op.equals("R*")) {
                v = lista.remover(Integer.parseInt(cmd[1]));
                System.out.println("(R) " + v.getMarca() + " " + v.getModelo());
            }
        }

        for (int i = 0; i < lista.tamanho(); i++) System.out.println(lista.get(i).format());
    }

    public static Veiculo buscar(Veiculo[] base, int id) {
        for (int i = 0; i < base.length; i++) if (base[i].getId() == id) return base[i];
        return null;
    }
}
