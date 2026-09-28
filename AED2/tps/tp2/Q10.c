#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int id, ano, cilindros;
    char marca[100], modelo[100];
    char categoria[100], combustivel[100];
    double cilindrada, consumoCidade, consumoEstrada, co2;
    char transmissao[100], tracao[100];
    int turbo;
    Data dataRegistro;
} Veiculo;

Veiculo ler(char *linha) {
    Veiculo v;
    char data[30];

    char *p = strtok(linha, ",");
    v.id = atoi(p);
    p = strtok(NULL, ","); strcpy(v.marca, p);
    p = strtok(NULL, ","); strcpy(v.modelo, p);
    p = strtok(NULL, ","); v.ano = atoi(p);
    p = strtok(NULL, ","); strcpy(v.categoria, p);
    p = strtok(NULL, ","); strcpy(v.combustivel, p);
    p = strtok(NULL, ","); v.cilindros = atoi(p);
    p = strtok(NULL, ","); v.cilindrada = atof(p);
    p = strtok(NULL, ","); strcpy(v.transmissao, p);
    p = strtok(NULL, ","); strcpy(v.tracao, p);
    p = strtok(NULL, ","); v.consumoCidade = atof(p);
    p = strtok(NULL, ","); v.consumoEstrada = atof(p);
    p = strtok(NULL, ","); v.co2 = atof(p);
    p = strtok(NULL, ","); v.turbo = strcmp(p, "true") == 0;
    p = strtok(NULL, ","); strcpy(data, p);

    sscanf(data, "%d-%d-%d",
           &v.dataRegistro.ano,
           &v.dataRegistro.mes,
           &v.dataRegistro.dia);

    return v;
}

void imprimir(Veiculo v) {
    printf("[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.1f ## %.1f ## %.1f ## %s ## %02d/%02d/%04d]\n",
           v.id, v.marca, v.modelo, v.ano, v.categoria,
           v.combustivel, v.cilindros, v.cilindrada,
           v.transmissao, v.tracao, v.consumoCidade,
           v.consumoEstrada, v.co2,
           v.turbo ? "true" : "false",
           v.dataRegistro.dia,
           v.dataRegistro.mes,
           v.dataRegistro.ano);
}

typedef struct {
    Veiculo dados[TAM];
    int inicio;
    int fim;
    int quantidade;
} Fila;

void inicializar(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

Veiculo remover(Fila *f) {
    Veiculo v = f->dados[f->inicio];

    f->inicio = (f->inicio + 1) % TAM;
    f->quantidade--;

    return v;
}

void inserir(Fila *f, Veiculo v) {
    if (f->quantidade == TAM) {
        Veiculo removido = remover(f);
        printf("(R) %s %s\n", removido.marca, removido.modelo);
    }

    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % TAM;
    f->quantidade++;
}

int main() {
    FILE *arq = fopen("/tmp/veiculos.csv", "r");
    if (!arq) return 1;

    Veiculo todos[10000];
    char linha[1000];
    int total = 0;

    fgets(linha, sizeof(linha), arq);

    while (fgets(linha, sizeof(linha), arq)) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha))
            todos[total++] = ler(linha);
    }

    fclose(arq);

    Fila fila;
    inicializar(&fila);

    int id;

    while (scanf("%d", &id) == 1 && id != -1) {
        for (int i = 0; i < total; i++) {
            if (todos[i].id == id) {
                inserir(&fila, todos[i]);
                break;
            }
        }
    }

    char comando;

    while (scanf(" %c", &comando) == 1) {
        if (comando == 'I') {
            scanf("%d", &id);

            for (int i = 0; i < total; i++) {
                if (todos[i].id == id) {
                    inserir(&fila, todos[i]);
                    break;
                }
            }

        } else if (comando == 'R') {
            if (fila.quantidade > 0) {
                Veiculo v = remover(&fila);
                printf("(R) %s %s\n", v.marca, v.modelo);
            }
        }
    }

    for (int i = 0; i < fila.quantidade; i++) {
        int pos = (fila.inicio + i) % TAM;
        imprimir(fila.dados[pos]);
    }

    return 0;
}