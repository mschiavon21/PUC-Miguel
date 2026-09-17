#include <stdio.h>
#include <stdlib.h>

char cifrarChar(char c) {
    if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + 3) % 26;
    }

    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + 3) % 26;
    }

    return c;
}

void cifrarRec(const char *origem, char *destino, int i) {
    if (origem[i] == '\0') {
        destino[i] = '\0';
        return;
    }

    destino[i] = cifrarChar(origem[i]);
    cifrarRec(origem, destino, i + 1);
}

char *cifrar(const char *s) {
    int tamanho = 0;

    while (s[tamanho] != '\0') {
        tamanho++;
    }

    char *resultado = malloc((tamanho + 1) * sizeof(char));

    cifrarRec(s, resultado, 0);

    return resultado;
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
    int tamanho = lerLinha(linha, sizeof(linha));

    while (tamanho != -1) {
        if (tamanho == 3 &&
            linha[0] == 'F' &&
            linha[1] == 'I' &&
            linha[2] == 'M') {
            break;
        }

        char *cifrada = cifrar(linha);

        printf("%s\n", cifrada);

        free(cifrada);

        tamanho = lerLinha(linha, sizeof(linha));
    }

    return 0;
}
