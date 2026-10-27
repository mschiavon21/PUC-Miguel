#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COMB 8
#define TAM_COMB 32
#define TAM_CAMPO 256
#define TAM_BUF 1024

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

typedef struct {
    int id;
    char marca[64];
    char modelo[128];
    int ano;
    char categoria[64];
    char combustivel[MAX_COMB][TAM_COMB];
    int nCombustivel; /* quantidade de combustiveis preenchidos */
    int cilindros;
    double cilindrada;
    char transmissao[32];
    char tracao[32];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    bool turbo;
    Data dataRegistro;
} Veiculo;

/* ---------- DataFunctions ---------- */
Data parseData(char* s) {
    Data d = {0, 0, 0};
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

void formatData(Data d, char* buffer) {
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

/* ---------- VeiculoFunctions ---------- */
static void copiar(char* dst, const char* src, size_t tam) {
    strncpy(dst, src, tam - 1);
    dst[tam - 1] = '\0';
}

/* Divide uma linha CSV respeitando campos entre aspas. Retorna a quantidade de campos. */
static int dividirCsv(const char* s, char campos[][TAM_CAMPO], int max) {
    int n = 0, k = 0;
    bool aspas = false;
    for (const char* p = s;; p++) {
        char c = *p;
        if (c == '"') {
            if (aspas && *(p + 1) == '"') {
                if (k < TAM_CAMPO - 1) campos[n][k++] = '"';
                p++;
            } else {
                aspas = !aspas;
            }
        } else if ((c == ',' && !aspas) || c == '\0') {
            campos[n][k] = '\0';
            n++;
            k = 0;
            if (c == '\0' || n >= max) break;
        } else if (k < TAM_CAMPO - 1) {
            campos[n][k++] = c;
        }
    }
    return n;
}

Veiculo* parseVeiculo(char* s) {
    char campos[16][TAM_CAMPO];
    int nc = dividirCsv(s, campos, 16);
    for (int i = nc; i < 16; i++) campos[i][0] = '\0';

    Veiculo* v = (Veiculo*) calloc(1, sizeof(Veiculo));
    v->id = atoi(campos[0]);
    copiar(v->marca, campos[1], sizeof v->marca);
    copiar(v->modelo, campos[2], sizeof v->modelo);
    v->ano = atoi(campos[3]);
    copiar(v->categoria, campos[4], sizeof v->categoria);

    char tmp[TAM_CAMPO];
    copiar(tmp, campos[5], sizeof tmp);
    v->nCombustivel = 0;
    for (char* t = strtok(tmp, ";"); t != NULL && v->nCombustivel < MAX_COMB; t = strtok(NULL, ";")) {
        copiar(v->combustivel[v->nCombustivel++], t, TAM_COMB);
    }

    v->cilindros = atoi(campos[6]);
    v->cilindrada = atof(campos[7]);
    copiar(v->transmissao, campos[8], sizeof v->transmissao);
    copiar(v->tracao, campos[9], sizeof v->tracao);
    v->consumoCidade = atof(campos[10]);
    v->consumoEstrada = atof(campos[11]);
    v->co2 = atof(campos[12]);
    v->turbo = strcmp(campos[13], "true") == 0 || strcmp(campos[13], "True") == 0 || strcmp(campos[13], "TRUE") == 0;
    v->dataRegistro = parseData(campos[14]);
    return v;
}

void formatVeiculo(Veiculo v, char* buffer) {
    char data[16];
    formatData(v.dataRegistro, data);

    char comb[MAX_COMB * (TAM_COMB + 2)];
    int pos = 0;
    comb[0] = '\0';
    for (int i = 0; i < v.nCombustivel; i++) {
        pos += sprintf(comb + pos, "%s%s", i > 0 ? ", " : "", v.combustivel[i]);
    }

    sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.2f ## %s ## %s]",
            v.id, v.marca, v.modelo, v.ano, v.categoria, comb, v.cilindros, v.cilindrada,
            v.transmissao, v.tracao, v.consumoCidade, v.consumoEstrada, v.co2,
            v.turbo ? "true" : "false", data);
}

/* ---------- LeitorCsvFunctions ---------- */
Veiculo* lerCsv(char* caminhoArquivo, int* n) {
    *n = 0;
    FILE* f = fopen(caminhoArquivo, "r");
    if (f == NULL) {
        fprintf(stderr, "Erro ao abrir %s\n", caminhoArquivo);
        return NULL;
    }
    int cap = 1024;
    Veiculo* arr = (Veiculo*) malloc(cap * sizeof(Veiculo));
    char linha[4096];
    bool primeira = true;
    while (fgets(linha, sizeof linha, f) != NULL) {
        size_t len = strlen(linha);
        while (len > 0 && (linha[len - 1] == '\n' || linha[len - 1] == '\r')) linha[--len] = '\0';
        if (len == 0) continue;
        if (primeira) {
            primeira = false;
            if (linha[0] < '0' || linha[0] > '9') continue; /* cabecalho */
        }
        Veiculo* v = parseVeiculo(linha);
        if (*n == cap) {
            cap *= 2;
            arr = (Veiculo*) realloc(arr, cap * sizeof(Veiculo));
        }
        arr[(*n)++] = *v;
        free(v);
    }
    fclose(f);
    return arr;
}

/* ---------- Utilitarios ---------- */
/* Pesquisa sequencial por id. */
Veiculo* buscar(Veiculo* todos, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (todos[i].id == id) return &todos[i];
    }
    return NULL;
}

/* Le ids da entrada padrao ate -1; devolve um arranjo de ponteiros para os veiculos encontrados. */
int lerSelecionados(Veiculo* todos, int nTodos, Veiculo*** saida) {
    int cap = 64, n = 0;
    Veiculo** arr = (Veiculo**) malloc(cap * sizeof(Veiculo*));
    char linha[512];
    while (fgets(linha, sizeof linha, stdin) != NULL) {
        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') continue;
        int id = atoi(linha);
        if (id == -1) break;
        Veiculo* v = buscar(todos, nTodos, id);
        if (v != NULL) {
            if (n == cap) {
                cap *= 2;
                arr = (Veiculo**) realloc(arr, cap * sizeof(Veiculo*));
            }
            arr[n++] = v;
        }
    }
    *saida = arr;
    return n;
}

void imprimir(Veiculo* v) {
    char buf[TAM_BUF];
    formatVeiculo(*v, buf);
    puts(buf);
}

void imprimirRemovido(Veiculo* v) {
    printf("(R) %s %s\n", v->marca, v->modelo);
}

/* Lista simplesmente encadeada de ponteiros para Veiculo. */
typedef struct Celula {
    Veiculo* elemento;
    struct Celula* prox;
} Celula;

typedef struct {
    Celula* primeiro;
    Celula* ultimo;
    int n;
} Lista;

void inserirFim(Lista* l, Veiculo* v) {
    Celula* c = (Celula*) malloc(sizeof(Celula));
    c->elemento = v;
    c->prox = NULL;
    if (l->n == 0) l->primeiro = c; else l->ultimo->prox = c;
    l->ultimo = c;
    l->n++;
}

/* Selecao por modelo: troca os ponteiros guardados nas celulas. */
void selecao(Lista* l) {
    for (Celula* i = l->primeiro; i != NULL && i->prox != NULL; i = i->prox) {
        Celula* menor = i;
        for (Celula* j = i->prox; j != NULL; j = j->prox) {
            if (strcmp(j->elemento->modelo, menor->elemento->modelo) < 0) menor = j;
        }
        Veiculo* tmp = i->elemento;
        i->elemento = menor->elemento;
        menor->elemento = tmp;
    }
}

void liberar(Lista* l) {
    while (l->primeiro != NULL) {
        Celula* c = l->primeiro;
        l->primeiro = c->prox;
        free(c);
    }
}

int main(void) {
    int nTodos;
    Veiculo* todos = lerCsv("/tmp/veiculos.csv", &nTodos);
    Veiculo** sel;
    int n = lerSelecionados(todos, nTodos, &sel);

    Lista lista = {NULL, NULL, 0};
    for (int i = 0; i < n; i++) inserirFim(&lista, sel[i]);
    selecao(&lista);
    for (Celula* i = lista.primeiro; i != NULL; i = i->prox) imprimir(i->elemento);

    liberar(&lista);
    free(sel);
    free(todos);
    return 0;
}
