#include <stdio.h>

int maiorSubstringSemRepeticao(const char *s) {
    int ultimaPosicao[256];
    int inicio = 0;
    int maior = 0;

    for (int i = 0; i < 256; i++) {
        ultimaPosicao[i] = -1;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        unsigned char c = s[i];

        if (ultimaPosicao[c] >= inicio) {
            inicio = ultimaPosicao[c] + 1;
        }

        ultimaPosicao[c] = i;

        int tamanho = i - inicio + 1;

        if (tamanho > maior) {
            maior = tamanho;
        }
    }

    return maior;
}

int main(void) {
    char linha[105];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        int i = 0;

        while (linha[i] != '\0' && linha[i] != '\n' && linha[i] != '\r') {
            i++;
        }

        linha[i] = '\0';

        printf("%d\n", maiorSubstringSemRepeticao(linha));
    }

    return 0;
}
