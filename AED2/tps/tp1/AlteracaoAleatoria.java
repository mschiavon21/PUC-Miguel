import java.util.Random;
import java.util.Scanner;

public class AlteracaoAleatoria {

    private static final Random gerador = new Random();

    public static String alterar(String s) {
        char letra1 = (char) ('a' + gerador.nextInt(26));
        char letra2 = (char) ('a' + gerador.nextInt(26));

        StringBuilder resultado = new StringBuilder();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            if (c == letra1) {
                resultado.append(letra2);
            } else {
                resultado.append(c);
            }
        }

        return resultado.toString();
    }

    public static void main(String[] args) {
        gerador.setSeed(4);

        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();

            if (linha.equals("FIM")) {
                break;
            }

            System.out.println(alterar(linha));
        }

        scanner.close();
    }
}
