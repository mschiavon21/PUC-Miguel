#include <stdio.h>

int ehVogal(char c) {
    if (c >= 'A' && c <= 'Z') {
        c += 'a' - 'A';
    }

    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int ehLetra(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int somenteVogaisRec(const char *s, int i) {
    if (s[i] == '\0') {
        return i > 0;
    }

    if (!ehVogal(s[i])) {
        return 0;
    }

    return somenteVogaisRec(s, i + 1);
}

int somenteConsoantesRec(const char *s, int i) {
    if (s[i] == '\0') {
        return i > 0;
    }

    if (!ehLetra(s[i]) || ehVogal(s[i])) {
        return 0;
    }

    return somenteConsoantesRec(s, i + 1);
}

int somenteDigitosRec(const char *s, int i) {
    if (s[i] == '\0') {
        return 1;
    }

    if (s[i] < '0' || s[i] > '9') {
        return 0;
    }

    return somenteDigitosRec(s, i + 1);
}

int contarPontosRec(const char *s, int i) {
    if (s[i] == '\0') {
        return 0;
    }

    return (s[i] == '.') + contarPontosRec(s, i + 1);
}

int somenteDigitosOuPontoRec(const char *s, int i) {
    if (s[i] == '\0') {
        return 1;
    }

    if ((s[i] < '0' || s[i] > '9') && s[i] != '.') {
        return 0;
    }

    return somenteDigitosOuPontoRec(s, i + 1);
}

int ehInteiro(const char *s) {
    if (s[0] == '\0') {
        return 0;
    }

    int inicio = s[0] == '-' ? 1 : 0;

    if (s[inicio] == '\0') {
        return 0;
    }

    return somenteDigitosRec(s, inicio);
}

int ehReal(const char *s) {
    if (s[0] == '\0') {
        return 0;
    }

    int inicio = s[0] == '-' ? 1 : 0;

    if (s[inicio] == '\0') {
        return 0;
    }

    if (!somenteDigitosOuPontoRec(s, inicio)) {
        return 0;
    }

    if (contarPontosRec(s, inicio) != 1) {
        return 0;
    }

    int fim = 0;

    while (s[fim] != '\0') {
        fim++;
    }

    return s[inicio] != '.' && s[fim - 1] != '.';
}

int lerLinha(char *buffer, int tamanhoMax) {
    int i = 0;
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i < tamanhoMax - 1) {
            buffer[i++] = (char)c;
        }
    }

    buffer[i] = '\0';

    return (c == EOF && i == 0) ? -1 : i;
}

int main(void) {
    char linha[105];
    int tam = lerLinha(linha, sizeof(linha));

    while (tam != -1) {
        if (tam == 3 && linha[0] == 'F' &&
            linha[1] == 'I' && linha[2] == 'M') {
            break;
        }

        printf("%s %s %s %s\n",
               somenteVogaisRec(linha, 0) ? "SIM" : "NAO",
               somenteConsoantesRec(linha, 0) ? "SIM" : "NAO",
               ehInteiro(linha) ? "SIM" : "NAO",
               ehReal(linha) ? "SIM" : "NAO");

        tam = lerLinha(linha, sizeof(linha));
    }

    return 0;
}
