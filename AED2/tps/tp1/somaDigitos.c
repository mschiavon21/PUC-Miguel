```c
#include <stdio.h>

int somaDigitos(int numero) {
    int soma = 0;

    if (numero < 0) {
        numero = -numero;
    }

    while (numero > 0) {
        soma += numero % 10;
        numero /= 10;
    }

    return soma;
}

int paraInteiro(const char *texto) {
    int numero = 0;
    int sinal = 1;
    int i = 0;

    if (texto[0] == '-') {
        sinal = -1;
        i = 1;
    }

    while (texto[i] != '\0') {
        if (texto[i] < '0' || texto[i] > '9') {
            return 0;
        }

        numero = numero * 10 + (texto[i] - '0');
        i++;
    }

    return numero * sinal;
}

int main(void) {
    char linha[105];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        int i = 0;

        while (linha[i] != '\0' && linha[i] != '\n' && linha[i] != '\r') {
            i++;
        }

        linha[i] = '\0';

        printf("%d\n", somaDigitos(paraInteiro(linha)));
    }

    return 0;
}
```

