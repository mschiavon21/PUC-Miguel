#include <stdio.h>

int saoAnagramas(const char *a, const char *b) {
    int contagem[256] = {0};
    int i;

    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        contagem[(unsigned char)a[i]]++;
        contagem[(unsigned char)b[i]]--;
    }

    if (a[i] != '\0' || b[i] != '\0') {
        return 0;
    }

    for (i = 0; i < 256; i++) {
        if (contagem[i] != 0) {
            return 0;
        }
    }

    return 1;
}

void removerQuebraLinha(char *str) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int main(void) {
    char linhaA[105];
    char linhaB[105];

    while (fgets(linhaA, sizeof(linhaA), stdin) != NULL &&
           fgets(linhaB, sizeof(linhaB), stdin) != NULL) {

        removerQuebraLinha(linhaA);
        removerQuebraLinha(linhaB);

        printf("%s\n", saoAnagramas(linhaA, linhaB) ? "SIM" : "NAO");
    }

    return 0;
}
