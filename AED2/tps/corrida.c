#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    int horas;
    int minutos;
    int segundos;
} Corredor;

int tempoTotal(Corredor c) {
    return 3600 * c.horas + 60 * c.minutos + c.segundos;
}

void insercao(Corredor v[], int n) {
    for (int i = 1; i < n; i++) {
        Corredor tmp = v[i];
        int j = i - 1;

        while (j >= 0 && tempoTotal(tmp) < tempoTotal(v[j])) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = tmp;
    }
}

void imprimir(Corredor v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %d %d %d\n",
               v[i].nome,
               v[i].horas,
               v[i].minutos,
               v[i].segundos);
    }
}

int main() {
    Corredor corredores[50];
    int n = 0;

    while (scanf("%49s %d %d %d",
                 corredores[n].nome,
                 &corredores[n].horas,
                 &corredores[n].minutos,
                 &corredores[n].segundos) == 4) {
        n++;
    }

    insercao(corredores, n);
    imprimir(corredores, n);

    return 0;
}