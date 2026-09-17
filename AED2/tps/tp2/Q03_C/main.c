#include "veiculos_c.h"
int main(void) {
    int nbase = 0, n = 0;
    Veiculo *base = lerCsv("/tmp/veiculos.csv", &nbase);
    if (!base) return 1;
    Veiculo *arr = malloc((size_t)nbase * sizeof(Veiculo));
    int id;
    while (scanf("%d", &id) == 1 && id != -1) {
        Veiculo *v = buscar(base, nbase, id);
        if (v) arr[n++] = *v;
    }
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) if (strcmp(arr[j].modelo, arr[menor].modelo) < 0) menor = j;
        if (menor != i) { Veiculo tmp = arr[i]; arr[i] = arr[menor]; arr[menor] = tmp; }
    }
    char buffer[1200];
    for (int i = 0; i < n; i++) { formatVeiculo(&arr[i], buffer); printf("%s\n", buffer); }
    free(arr); free(base); return 0;
}
