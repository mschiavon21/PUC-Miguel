#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[100];
    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    int turbo;
    Data dataRegistro;
} Veiculo;

void formatarData(Data data, char *saida) {
    sprintf(
        saida,
        "%02d/%02d/%04d",
        data.dia,
        data.mes,
        data.ano
    );
}

void formatarVeiculo(Veiculo v) {
    char data[20];

    formatarData(v.dataRegistro, data);

    printf(
        "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.1f ## %.1f ## %.1f ## %s ## %s]\n",
        v.id,
        v.marca,
        v.modelo,
        v.ano,
        v.categoria,
        v.combustivel,
        v.cilindros,
        v.cilindrada,
        v.transmissao,
        v.tracao,
        v.consumoCidade,
        v.consumoEstrada,
        v.co2,
        v.turbo ? "true" : "false",
        data
    );
}

Veiculo lerVeiculo(char *linha) {
    Veiculo v;
    char data[20];

    char *campo = strtok(linha, ",");

    v.id = atoi(campo);

    campo = strtok(NULL, ",");
    strcpy(v.marca, campo);

    campo = strtok(NULL, ",");
    strcpy(v.modelo, campo);

    campo = strtok(NULL, ",");
    v.ano = atoi(campo);

    campo = strtok(NULL, ",");
    strcpy(v.categoria, campo);

    campo = strtok(NULL, ",");
    strcpy(v.combustivel, campo);

    campo = strtok(NULL, ",");
    v.cilindros = atoi(campo);

    campo = strtok(NULL, ",");
    v.cilindrada = atof(campo);

    campo = strtok(NULL, ",");
    strcpy(v.transmissao, campo);

    campo = strtok(NULL, ",");
    strcpy(v.tracao, campo);

    campo = strtok(NULL, ",");
    v.consumoCidade = atof(campo);

    campo = strtok(NULL, ",");
    v.consumoEstrada = atof(campo);

    campo = strtok(NULL, ",");
    v.co2 = atof(campo);

    campo = strtok(NULL, ",");
    v.turbo = strcmp(campo, "true") == 0;

    campo = strtok(NULL, ",");
    strcpy(data, campo);

    sscanf(
        data,
        "%d-%d-%d",
        &v.dataRegistro.ano,
        &v.dataRegistro.mes,
        &v.dataRegistro.dia
    );

    return v;
}

int buscarPorId(Veiculo veiculos[], int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (veiculos[i].id == id) {
            return i;
        }
    }

    return -1;
}

int main() {
    FILE *arquivo;
    char linha[1000];

    Veiculo veiculos[10000];
    int quantidade = 0;

    arquivo = fopen("/tmp/veiculos.csv", "r");

    if (arquivo == NULL) {
        return 1;
    }

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) > 0) {
            veiculos[quantidade] = lerVeiculo(linha);
            quantidade++;
        }
    }

    fclose(arquivo);

    int id;

    while (scanf("%d", &id) == 1) {

        if (id == -1) {
            break;
        }

        int posicao = buscarPorId(
            veiculos,
            quantidade,
            id
        );

        if (posicao != -1) {
            formatarVeiculo(veiculos[posicao]);
        }
    }

    return 0;
}