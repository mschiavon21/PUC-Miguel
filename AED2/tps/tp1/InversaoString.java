import java.util.Scanner;

public class InversaoString {

    private static String inverterRec(String s, int i) {
        if (i == s.length()) {
            return "";
        }

        return inverterRec(s, i + 1) + s.charAt(i);
    }

    public static String inverter(String s) {
        return inverterRec(s, 0);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();

            if (linha.equals("FIM")) {
                break;
            }

            System.out.println(inverter(linha));
        }

        scanner.close();
    }
}
