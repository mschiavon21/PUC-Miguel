#ifndef VEICULOS_C_H
#define VEICULOS_C_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Data {
    int ano, mes, dia;
} Data;

typedef struct Veiculo {
    int id;
    char marca[100];
    char modelo[150];
    int ano;
    char categoria[100];
    char combustivel[10][50];
    int qtdCombustivel;
    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    bool turbo;
    Data dataRegistro;
} Veiculo;

void trim_newline(char *s);
Data parseData(const char *s);
void formatData(Data d, char *buffer);
Veiculo parseVeiculo(char *linha);
void formatVeiculo(const Veiculo *v, char *buffer);
Veiculo *lerCsv(const char *caminhoArquivo, int *n);
Veiculo *buscar(Veiculo *base, int n, int id);

#endif
