#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *inverter(const char *s) {
    int tamanho = strlen(s);
    char *resultado = malloc((tamanho + 1) * sizeof(char));

    for (int i = 0; i < tamanho; i++) {
        resultado[i] = s[tamanho - 1 - i];
    }

    resultado[tamanho] = '\0';

    return resultado;
}

int main(void) {
    char linha[105];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0';

        if (strcmp(linha, "FIM") == 0) {
            break;
        }

        char *invertida = inverter(linha);

        printf("%s\n", invertida);

        free(invertida);
    }

    return 0;
}
