#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

typedef struct {
    int id;
    char marca[1000];
    char modelo[1000];
    int ano;
    char categoria[100];
    char combustivel[10][50];
    int numCombustiveis;
    int cilindros;
    double cilindrada;
    char transmissao[1000];
    char tracao[1000];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    bool turbo;
    Data dataRegistro;
} Veiculo;

char* proximoCampo(char** resto) {
    if (*resto == NULL) {
        return NULL;
    }

    char* inicio = *resto;
    char* p = inicio;
    bool dentroAspas = false;

    while (*p != '\0') {

        if (*p == '"') {
            dentroAspas = !dentroAspas;
        }
        else if (*p == ',' && !dentroAspas) {
            *p = '\0';
            *resto = p + 1;
            return inicio;
        }
        else if ((*p == '\n' || *p == '\r') && !dentroAspas) {
            *p = '\0';
            *resto = NULL;
            return inicio;
        }

        p++;
    }

    *resto = NULL;

    return inicio;
}

Data parseData(char* s) {
    Data d;

    sscanf(s,
           "%d-%d-%d",
           &d.ano,
           &d.mes,
           &d.dia);

    return d;
}

void formatData(Data d, char* buffer) {
    sprintf(buffer,
            "%02d/%02d/%04d",
            d.dia,
            d.mes,
            d.ano);
}

void removerAspas(char* s) {
    int tamanho = strlen(s);

    if (tamanho >= 2 &&
        s[0] == '"' &&
        s[tamanho - 1] == '"') {

        memmove(s,
                s + 1,
                tamanho - 2);

        s[tamanho - 2] = '\0';
    }
}

Veiculo parseVeiculo(char* s) {

    Veiculo v;

    char* resto = s;
    char* campo;

    campo = proximoCampo(&resto);
    v.id = atoi(campo);

    campo = proximoCampo(&resto);
    removerAspas(campo);
    strcpy(v.marca, campo);

    campo = proximoCampo(&resto);
    removerAspas(campo);
    strcpy(v.modelo, campo);

    campo = proximoCampo(&resto);
    v.ano = atoi(campo);

    campo = proximoCampo(&resto);
    removerAspas(campo);
    strcpy(v.categoria, campo);

    campo = proximoCampo(&resto);
    removerAspas(campo);

    v.numCombustiveis = 0;

    int pos = 0;

    for (int i = 0;
         campo[i] != '\0';
         i++) {

        if (campo[i] == ';') {

            v.combustivel[v.numCombustiveis][pos] =
                '\0';

            v.numCombustiveis++;

            pos = 0;
        }
        else {

            v.combustivel[v.numCombustiveis][pos++] =
                campo[i];
        }
    }

    v.combustivel[v.numCombustiveis][pos] =
        '\0';

    v.numCombustiveis++;

    campo = proximoCampo(&resto);
    v.cilindros = atoi(campo);

    campo = proximoCampo(&resto);
    v.cilindrada = atof(campo);

    campo = proximoCampo(&resto);
    removerAspas(campo);
    strcpy(v.transmissao, campo);

    campo = proximoCampo(&resto);
    removerAspas(campo);
    strcpy(v.tracao, campo);

    campo = proximoCampo(&resto);
    v.consumoCidade = atof(campo);

    campo = proximoCampo(&resto);
    v.consumoEstrada = atof(campo);

    campo = proximoCampo(&resto);
    v.co2 = atof(campo);

    campo = proximoCampo(&resto);
    v.turbo = (strcmp(campo, "true") == 0);

    campo = proximoCampo(&resto);
    v.dataRegistro = parseData(campo);

    return v;
}

void formatVeiculo(Veiculo v, char* buffer) {

    char combStr[600] = "[";

    for (int i = 0;
         i < v.numCombustiveis;
         i++) {

        strcat(combStr,
               v.combustivel[i]);

        if (i < v.numCombustiveis - 1) {
            strcat(combStr, ",");
        }
    }

    strcat(combStr, "]");

    char dataStr[30];

    formatData(v.dataRegistro,
               dataStr);

    sprintf(
        buffer,
        "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
        v.id,
        v.marca,
        v.modelo,
        v.ano,
        v.categoria,
        combStr,
        v.cilindros,
        v.cilindrada,
        v.transmissao,
        v.tracao,
        v.consumoCidade,
        v.consumoEstrada,
        v.co2,
        v.turbo ? "true" : "false",
        dataStr
    );
}

Veiculo* leitorCSV(char* caminhoArquivo,
                   int* numVeiculos) {

    FILE* f =
        fopen(caminhoArquivo, "r");

    if (f == NULL) {
        return NULL;
    }

    char linha[2048];

    fgets(linha,
          sizeof(linha),
          f);

    Veiculo* veiculos =
        malloc(10000 * sizeof(Veiculo));

    int count = 0;

    while (fgets(linha,
                  sizeof(linha),
                  f)) {

        if (strlen(linha) > 3) {

            veiculos[count] =
                parseVeiculo(linha);

            count++;
        }
    }

    fclose(f);

    *numVeiculos = count;

    return veiculos;
}

int compare(char* ch1, char* ch2) {

    int i = 0;

    while (ch1[i] != '\0' &&
           ch2[i] != '\0') {

        if (ch1[i] != ch2[i]) {
            return ch1[i] - ch2[i];
        }

        i++;
    }

    return ch1[i] - ch2[i];
}

void selectionSort(Veiculo* veiculos,
                   int n) {

    for (int i = 0;
         i < n - 1;
         i++) {

        int menor = i;

        for (int j = i + 1;
             j < n;
             j++) {

            if (compare(
                    veiculos[j].modelo,
                    veiculos[menor].modelo) < 0) {

                menor = j;
            }
        }

        if (menor != i) {

            Veiculo temp =
                veiculos[i];

            veiculos[i] =
                veiculos[menor];

            veiculos[menor] =
                temp;
        }
    }
}

int main() {

    int numVeiculos = 0;

    Veiculo* veiculos =
        leitorCSV(
            "/tmp/veiculos.csv",
            &numVeiculos
        );

    if (veiculos == NULL) {
        return 1;
    }

    static Veiculo selecionados[1000];

    int numSelecionados = 0;

    int idBusca;

    while (scanf("%d", &idBusca) == 1 &&
           idBusca != -1) {

        for (int i = 0;
             i < numVeiculos;
             i++) {

            if (veiculos[i].id == idBusca) {

                selecionados[numSelecionados++] =
                    veiculos[i];

                break;
            }
        }
    }

    selectionSort(
        selecionados,
        numSelecionados
    );

    char bufferOut[2048];

    for (int i = 0;
         i < numSelecionados;
         i++) {

        formatVeiculo(
            selecionados[i],
            bufferOut
        );

        printf("%s\n",
               bufferOut);
    }

    free(veiculos);

    return 0;
}