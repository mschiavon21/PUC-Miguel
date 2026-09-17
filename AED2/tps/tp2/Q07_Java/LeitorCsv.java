import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

public class LeitorCsv {
    public static Veiculo[] ler(String caminhoArquivo) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo));
        ArrayList<Veiculo> lista = new ArrayList<Veiculo>();
        String linha;
        while ((linha = br.readLine()) != null) {
            if (linha.length() == 0 || linha.charAt(0) == 'i' || linha.charAt(0) == 'I') continue;
            lista.add(Veiculo.parseVeiculo(linha));
        }
        br.close();
        return lista.toArray(new Veiculo[lista.size()]);
    }
}
