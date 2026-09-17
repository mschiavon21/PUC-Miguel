import java.util.Scanner;

public class Is {

    public static boolean somenteVogais(String s) {
        if (s.length() == 0) {
            return false;
        }

        for (int i = 0; i < s.length(); i++) {
            char c = Character.toLowerCase(s.charAt(i));

            if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
                return false;
            }
        }

        return true;
    }

    public static boolean somenteConsoantes(String s) {
        if (s.length() == 0) {
            return false;
        }

        for (int i = 0; i < s.length(); i++) {
            char c = Character.toLowerCase(s.charAt(i));

            if (c < 'a' || c > 'z') {
                return false;
            }

            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                return false;
            }
        }

        return true;
    }

    public static boolean ehInteiro(String s) {
        if (s.length() == 0) {
            return false;
        }

        int inicio = s.charAt(0) == '-' ? 1 : 0;

        if (inicio == s.length()) {
            return false;
        }

        for (int i = inicio; i < s.length(); i++) {
            if (s.charAt(i) < '0' || s.charAt(i) > '9') {
                return false;
            }
        }

        return true;
    }

    public static boolean ehReal(String s) {
        if (s.length() == 0) {
            return false;
        }

        int inicio = s.charAt(0) == '-' ? 1 : 0;
        int pontos = 0;
        int digitos = 0;

        if (inicio == s.length()) {
            return false;
        }

        for (int i = inicio; i < s.length(); i++) {
            char c = s.charAt(i);

            if (c == '.') {
                pontos++;
            } else if (c >= '0' && c <= '9') {
                digitos++;
            } else {
                return false;
            }
        }

        return pontos == 1 && digitos > 0
                && s.charAt(inicio) != '.'
                && s.charAt(s.length() - 1) != '.';
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();

            if (linha.equals("FIM")) {
                break;
            }

            System.out.println(
                (somenteVogais(linha) ? "SIM" : "NAO") + " " +
                (somenteConsoantes(linha) ? "SIM" : "NAO") + " " +
                (ehInteiro(linha) ? "SIM" : "NAO") + " " +
                (ehReal(linha) ? "SIM" : "NAO")
            );
        }

        scanner.close();
    }
}