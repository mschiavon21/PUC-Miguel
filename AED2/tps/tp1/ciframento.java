import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ciframento {

    public static String cifra(String texto) {
        String resultado = "";

        for (int i = 0; i < texto.length(); i++) {
            char c = texto.charAt(i);

            if (c >= 'a' && c <= 'z') {
                c = (char) ('a' + (c - 'a' + 3) % 26);
            } else if (c >= 'A' && c <= 'Z') {
                c = (char) ('A' + (c - 'A' + 3) % 26);
            }

            resultado += c;
        }

        return resultado;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String linha;

        while ((linha = br.readLine()) != null) {
            System.out.println(cifra(linha));
        }
    }
}