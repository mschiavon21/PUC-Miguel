#include "veiculos_c.h"
#define CAP 5

typedef struct {
    Veiculo dados[CAP];
    int inicio;
    int fim;
    int tamanho;
} Fila;

static void init(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

static Veiculo remover(Fila *f) {
    Veiculo v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % CAP;
    f->tamanho--;
    return v;
}

static void imprimirRemovido(Veiculo *v) {
    printf("(R) %s %s\n", v->marca, v->modelo);
}

static void inserir(Fila *f, Veiculo v) {
    if (f->tamanho == CAP) {
        Veiculo removido = remover(f);
        imprimirRemovido(&removido);
    }
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % CAP;
    f->tamanho++;
}

int main(void) {
    int nb = 0;
    Veiculo *base = lerCsv("/tmp/veiculos.csv", &nb);
    if (!base) return 1;

    Fila fila;
    init(&fila);

    int id;
    while (scanf("%d", &id) == 1 && id != -1) {
        Veiculo *v = buscar(base, nb, id);
        if (v) inserir(&fila, *v);
    }

    int n = 0;
    scanf("%d", &n);

    char linha[200];
    fgets(linha, sizeof(linha), stdin);

    for (int i = 0; i < n; i++) {
        fgets(linha, sizeof(linha), stdin);
        trim_newline(linha);
        char *op = strtok(linha, " ");

        if (strcmp(op, "I") == 0) {
            char *sid = strtok(NULL, " ");
            Veiculo *v = buscar(base, nb, atoi(sid));
            if (v) inserir(&fila, *v);
        } else if (strcmp(op, "R") == 0) {
            if (fila.tamanho > 0) {
                Veiculo removido = remover(&fila);
                imprimirRemovido(&removido);
            }
        }
    }

    for (int i = 0; i < fila.tamanho; i++) {
        int pos = (fila.inicio + i) % CAP;
        char buffer[1200];
        formatVeiculo(&fila.dados[pos], buffer);
        printf("%s\n", buffer);
    }

    free(base);
    return 0;
}
