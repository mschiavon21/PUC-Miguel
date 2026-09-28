#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Celula {
    Veiculo elemento;
    struct Celula *prox;
} Celula;

typedef struct {
    Celula *primeiro;
    Celula *ultimo;
    int tamanho;
} Lista;

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

void inicializar(Lista *l) {
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->tamanho = 0;
}

void inserirInicio(Lista *l, Veiculo v) {
    Celula *nova = malloc(sizeof(Celula));
    nova->elemento = v;
    nova->prox = l->primeiro;

    l->primeiro = nova;

    if (l->tamanho == 0)
        l->ultimo = nova;

    l->tamanho++;
}

void inserirFim(Lista *l, Veiculo v) {
    Celula *nova = malloc(sizeof(Celula));
    nova->elemento = v;
    nova->prox = NULL;

    if (l->tamanho == 0) {
        l->primeiro = nova;
    } else {
        l->ultimo->prox = nova;
    }

    l->ultimo = nova;
    l->tamanho++;
}

void inserir(Lista *l, Veiculo v, int pos) {
    if (pos == 0) {
        inserirInicio(l, v);
        return;
    }

    if (pos == l->tamanho) {
        inserirFim(l, v);
        return;
    }

    Celula *atual = l->primeiro;

    for (int i = 0; i < pos - 1; i++)
        atual = atual->prox;

    Celula *nova = malloc(sizeof(Celula));
    nova->elemento = v;
    nova->prox = atual->prox;
    atual->prox = nova;

    l->tamanho++;
}

Veiculo removerInicio(Lista *l) {
    Celula *tmp = l->primeiro;
    Veiculo v = tmp->elemento;

    l->primeiro = tmp->prox;

    if (--l->tamanho == 0)
        l->ultimo = NULL;

    free(tmp);

    return v;
}

Veiculo removerFim(Lista *l) {
    if (l->tamanho == 1)
        return removerInicio(l);

    Celula *atual = l->primeiro;

    while (atual->prox != l->ultimo)
        atual = atual->prox;

    Veiculo v = l->ultimo->elemento;

    free(l->ultimo);

    l->ultimo = atual;
    l->ultimo->prox = NULL;

    l->tamanho--;

    return v;
}

Veiculo remover(Lista *l, int pos) {
    if (pos == 0)
        return removerInicio(l);

    if (pos == l->tamanho - 1)
        return removerFim(l);

    Celula *atual = l->primeiro;

    for (int i = 0; i < pos - 1; i++)
        atual = atual->prox;

    Celula *tmp = atual->prox;
    Veiculo v = tmp->elemento;

    atual->prox = tmp->prox;

    free(tmp);

    l->tamanho--;

    return v;
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

    Lista lista;
    inicializar(&lista);

    int id;

    while (scanf("%d", &id) == 1 && id != -1) {
        for (int i = 0; i < total; i++) {
            if (todos[i].id == id) {
                inserirFim(&lista, todos[i]);
                break;
            }
        }
    }

    int n;
    scanf("%d", &n);

    char comando[5];

    for (int i = 0; i < n; i++) {
        scanf("%s", comando);

        if (strcmp(comando, "II") == 0) {
            scanf("%d", &id);

            for (int j = 0; j < total; j++) {
                if (todos[j].id == id) {
                    inserirInicio(&lista, todos[j]);
                    break;
                }
            }

        } else if (strcmp(comando, "IF") == 0) {
            scanf("%d", &id);

            for (int j = 0; j < total; j++) {
                if (todos[j].id == id) {
                    inserirFim(&lista, todos[j]);
                    break;
                }
            }

        } else if (strcmp(comando, "I*") == 0) {
            int pos;
            scanf("%d %d", &pos, &id);

            for (int j = 0; j < total; j++) {
                if (todos[j].id == id) {
                    inserir(&lista, todos[j], pos);
                    break;
                }
            }

        } else if (strcmp(comando, "RI") == 0) {
            Veiculo v = removerInicio(&lista);
            printf("(R) %s %s\n", v.marca, v.modelo);

        } else if (strcmp(comando, "RF") == 0) {
            Veiculo v = removerFim(&lista);
            printf("(R) %s %s\n", v.marca, v.modelo);

        } else if (strcmp(comando, "R*") == 0) {
            int pos;
            scanf("%d", &pos);

            Veiculo v = remover(&lista, pos);
            printf("(R) %s %s\n", v.marca, v.modelo);
        }
    }

    Celula *atual = lista.primeiro;

    while (atual != NULL) {
        imprimir(atual->elemento);
        atual = atual->prox;
    }

    return 0;
}