
import java.util.Scanner;

public class ValidacaoSenha {

    public static boolean senhaValida(String s) {
        boolean maiuscula = false;
        boolean minuscula = false;
        boolean digito = false;
        boolean especial = false;

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            if (c >= 'A' && c <= 'Z') {
                maiuscula = true;
            } else if (c >= 'a' && c <= 'z') {
                minuscula = true;
            } else if (c >= '0' && c <= '9') {
                digito = true;
            } else if (c != ' ') {
                especial = true;
            }
        }

        return s.length() >= 8 && maiuscula && minuscula && digito && especial;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();

            if (linha.equals("FIM")) {
                break;
            }

            System.out.println(senhaValida(linha) ? "SIM" : "NAO");
        }

        scanner.close();
    }
}

