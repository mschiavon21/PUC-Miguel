#include "veiculos_c.h"
int main(void) {
    int n = 0;
    Veiculo *base = lerCsv("/tmp/veiculos.csv", &n);
    if (!base) return 1;
    int id;
    char buffer[1200];
    while (scanf("%d", &id) == 1 && id != -1) {
        Veiculo *v = buscar(base, n, id);
        if (v) { formatVeiculo(v, buffer); printf("%s\n", buffer); }
    }
    free(base);
    return 0;
}
