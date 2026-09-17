#include "veiculos_c.h"

void trim_newline(char *s) {
    int n = (int)strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) s[--n] = '\0';
}

Data parseData(const char *s) {
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

void formatData(Data d, char *buffer) {
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

Veiculo parseVeiculo(char *linha) {
    Veiculo v;
    char *p[15];
    int i = 0;
    char *tok = strtok(linha, ",");
    while (tok != NULL && i < 15) {
        p[i++] = tok;
        tok = strtok(NULL, ",");
    }

    v.id = atoi(p[0]);
    strcpy(v.marca, p[1]);
    strcpy(v.modelo, p[2]);
    v.ano = atoi(p[3]);
    strcpy(v.categoria, p[4]);

    v.qtdCombustivel = 0;
    tok = strtok(p[5], ";");
    while (tok != NULL && v.qtdCombustivel < 10) {
        strcpy(v.combustivel[v.qtdCombustivel++], tok);
        tok = strtok(NULL, ";");
    }

    v.cilindros = atoi(p[6]);
    v.cilindrada = atof(p[7]);
    strcpy(v.transmissao, p[8]);
    strcpy(v.tracao, p[9]);
    v.consumoCidade = atof(p[10]);
    v.consumoEstrada = atof(p[11]);
    v.co2 = atof(p[12]);
    v.turbo = (strcmp(p[13], "true") == 0 || strcmp(p[13], "TRUE") == 0);
    v.dataRegistro = parseData(p[14]);
    return v;
}

void formatVeiculo(const Veiculo *v, char *buffer) {
    char data[32];
    formatData(v->dataRegistro, data);
    char combust[600] = "[";
    for (int i = 0; i < v->qtdCombustivel; i++) {
        if (i > 0) strcat(combust, ";");
        strcat(combust, v->combustivel[i]);
    }
    strcat(combust, "]");
    sprintf(buffer,
        "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %g ## %s ## %s ## %g ## %g ## %g ## %s ## %s]",
        v->id, v->marca, v->modelo, v->ano, v->categoria, combust, v->cilindros,
        v->cilindrada, v->transmissao, v->tracao, v->consumoCidade, v->consumoEstrada,
        v->co2, v->turbo ? "true" : "false", data);
}

Veiculo *lerCsv(const char *caminhoArquivo, int *n) {
    FILE *fp = fopen(caminhoArquivo, "r");
    if (!fp) return NULL;
    int cap = 1024;
    Veiculo *arr = malloc((size_t)cap * sizeof(Veiculo));
    *n = 0;
    char linha[4096];
    while (fgets(linha, sizeof(linha), fp)) {
        trim_newline(linha);
        if (linha[0] == '\0' || linha[0] == 'i' || linha[0] == 'I') continue;
        if (*n >= cap) {
            cap *= 2;
            arr = realloc(arr, (size_t)cap * sizeof(Veiculo));
        }
        arr[*n] = parseVeiculo(linha);
        (*n)++;
    }
    fclose(fp);
    return arr;
}

Veiculo *buscar(Veiculo *base, int n, int id) {
    for (int i = 0; i < n; i++) if (base[i].id == id) return &base[i];
    return NULL;
}
