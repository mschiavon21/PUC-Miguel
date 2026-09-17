import java.util.Scanner;

public class SomaDigitos {

    public static int somaDigitos(int numero) {
        if (numero < 0) {
            numero = -numero;
        }

        if (numero < 10) {
            return numero;
        }

        return numero % 10 + somaDigitos(numero / 10);
    }

    private static int paraInteiro(String texto) {
        if (texto.isEmpty()) {
            return 0;
        }

        int sinal = 1;
        int inicio = 0;

        if (texto.charAt(0) == '-') {
            sinal = -1;
            inicio = 1;
        }

        if (inicio == texto.length()) {
            return 0;
        }

        int numero = 0;

        for (int i = inicio; i < texto.length(); i++) {
            char c = texto.charAt(i);

            if (c < '0' || c > '9') {
                return 0;
            }

            numero = numero * 10 + (c - '0');
        }

        return numero * sinal;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();
            System.out.println(somaDigitos(paraInteiro(linha)));
        }

        scanner.close();
    }
}

