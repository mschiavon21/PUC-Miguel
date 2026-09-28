#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int ano;
    int mes;
    int dia;
} Data;

typedef struct
{
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

Data parseData(char *s)
{
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

void formatData(Data d, char *buffer)
{
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

Veiculo parseVeiculo(char *s)
{
    Veiculo v;

    v.id = atoi(strtok(s, ",\r\n"));
    strcpy(v.marca, strtok(NULL, ",\r\n"));
    strcpy(v.modelo, strtok(NULL, ",\r\n"));
    v.ano = atoi(strtok(NULL, ",\r\n"));
    strcpy(v.categoria, strtok(NULL, ",\r\n"));

    char *combToken = strtok(NULL, ",\r\n");

    v.numCombustiveis = 0;
    int pos = 0;

    for (int i = 0; combToken[i] != '\0'; i++)
    {
        if (combToken[i] == ';')
        {
            v.combustivel[v.numCombustiveis][pos] = '\0';
            v.numCombustiveis++;
            pos = 0;
        }
        else
        {
            v.combustivel[v.numCombustiveis][pos++] = combToken[i];
        }
    }

    v.combustivel[v.numCombustiveis][pos] = '\0';
    v.numCombustiveis++;

    v.cilindros = atoi(strtok(NULL, ",\r\n"));
    v.cilindrada = atof(strtok(NULL, ",\r\n"));
    strcpy(v.transmissao, strtok(NULL, ",\r\n"));
    strcpy(v.tracao, strtok(NULL, ",\r\n"));
    v.consumoCidade = atof(strtok(NULL, ",\r\n"));
    v.consumoEstrada = atof(strtok(NULL, ",\r\n"));
    v.co2 = atof(strtok(NULL, ",\r\n"));

    char *turboToken = strtok(NULL, ",\r\n");
    v.turbo = (strcmp(turboToken, "true") == 0);

    char *dataToken = strtok(NULL, ",\r\n");
    v.dataRegistro = parseData(dataToken);

    return v;
}

void formatVeiculo(Veiculo v, char *buffer)
{
    char combStr[600] = "[";

    for (int i = 0; i < v.numCombustiveis; i++)
    {
        strcat(combStr, v.combustivel[i]);

        if (i < v.numCombustiveis - 1)
        {
            strcat(combStr, ",");
        }
    }

    strcat(combStr, "]");

    char dataStr[30];
    formatData(v.dataRegistro, dataStr);

    sprintf(buffer,
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
            dataStr);
}

Veiculo *leitorCSV(char *caminhoArquivo, int *numVeiculos)
{
    FILE *f = fopen(caminhoArquivo, "r");

    if (!f)
    {
        return NULL;
    }

    char linha[1024];

    fgets(linha, sizeof(linha), f);

    Veiculo *veiculos = malloc(10000 * sizeof(Veiculo));

    if (!veiculos)
    {
        fclose(f);
        return NULL;
    }

    int count = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        if (strlen(linha) > 3)
        {
            veiculos[count++] = parseVeiculo(linha);
        }
    }

    fclose(f);

    *numVeiculos = count;

    return veiculos;
}

int getMaiorAno(Veiculo *veiculo, int n)
{
    if (n <= 0)
    {
        return 0;
    }

    int maior = veiculo[0].ano;

    for (int i = 1; i < n; i++)
    {
        if (veiculo[i].ano > maior)
        {
            maior = veiculo[i].ano;
        }
    }

    return maior;
}

void countingSort(Veiculo *veiculo, int n, int exp)
{
    int count[10] = {0};

    Veiculo *saida = malloc(n * sizeof(Veiculo));

    if (!saida)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int digito = (veiculo[i].ano / exp) % 10;
        count[digito]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int digito = (veiculo[i].ano / exp) % 10;
        count[digito]--;
        saida[count[digito]] = veiculo[i];
    }

    for (int i = 0; i < n; i++)
    {
        veiculo[i] = saida[i];
    }

    free(saida);
}

void radixSort(Veiculo *veiculo, int n)
{
    if (n <= 1)
    {
        return;
    }

    int maior = getMaiorAno(veiculo, n);

    for (int exp = 1; maior / exp > 0; exp *= 10)
    {
        countingSort(veiculo, n, exp);
    }
}

int main()
{
    int numVeiculos = 0;

    Veiculo *veiculos = leitorCSV("/tmp/veiculos.csv", &numVeiculos);

    if (!veiculos)
    {
        return 1;
    }

    static Veiculo selecionados[1000];
    int numSelecionados = 0;
    int idBusca;

    while (scanf("%d", &idBusca) == 1 && idBusca != -1)
    {
        for (int i = 0; i < numVeiculos; i++)
        {
            if (veiculos[i].id == idBusca)
            {
                if (numSelecionados < 1000)
                {
                    selecionados[numSelecionados] = veiculos[i];
                    numSelecionados++;
                }

                break;
            }
        }
    }

    radixSort(selecionados, numSelecionados);

    char bufferOut[2048];

    for (int i = 0; i < numSelecionados; i++)
    {
        formatVeiculo(selecionados[i], bufferOut);
        printf("%s\n", bufferOut);
    }

    free(veiculos);

    return 0;
}