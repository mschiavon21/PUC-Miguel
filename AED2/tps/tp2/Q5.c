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

    sscanf(s, "%d-%d-%d",
           &d.ano,
           &d.mes,
           &d.dia);

    return d;
}

void formatData(Data d, char *buffer)
{
    sprintf(buffer,
            "%02d/%02d/%04d",
            d.dia,
            d.mes,
            d.ano);
}

int separarCSV(char *linha, char campos[][1000])
{
    int quantidade = 0;
    int posicao = 0;
    bool dentroAspas = false;

    for (int i = 0; linha[i] != '\0'; i++)
    {
        char c = linha[i];

        if (c == '"')
        {
            dentroAspas = !dentroAspas;
        }
        else if (c == ',' && !dentroAspas)
        {
            campos[quantidade][posicao] = '\0';

            quantidade++;
            posicao = 0;
        }
        else
        {
            campos[quantidade][posicao++] = c;
        }
    }

    campos[quantidade][posicao] = '\0';
    quantidade++;

    return quantidade;
}

Veiculo parseVeiculo(char *linha)
{
    Veiculo v;

    char campos[20][1000];

    separarCSV(linha, campos);

    v.id = atoi(campos[0]);

    strcpy(v.marca, campos[1]);
    strcpy(v.modelo, campos[2]);

    v.ano = atoi(campos[3]);

    strcpy(v.categoria, campos[4]);

    v.numCombustiveis = 0;

    char combustiveis[500];

    strcpy(combustiveis, campos[5]);

    int pos = 0;

    for (int i = 0;
         combustiveis[i] != '\0';
         i++)
    {
        if (combustiveis[i] == ';')
        {
            v.combustivel[v.numCombustiveis][pos] = '\0';

            v.numCombustiveis++;

            pos = 0;
        }
        else
        {
            v.combustivel[v.numCombustiveis][pos++] =
                combustiveis[i];
        }
    }

    v.combustivel[v.numCombustiveis][pos] = '\0';

    v.numCombustiveis++;

    v.cilindros = atoi(campos[6]);

    v.cilindrada = atof(campos[7]);

    strcpy(v.transmissao, campos[8]);

    strcpy(v.tracao, campos[9]);

    v.consumoCidade = atof(campos[10]);

    v.consumoEstrada = atof(campos[11]);

    v.co2 = atof(campos[12]);

    v.turbo = strcmp(campos[13], "true") == 0;

    v.dataRegistro = parseData(campos[14]);

    return v;
}

void formatVeiculo(Veiculo v, char *buffer)
{
    char combStr[600] = "[";

    for (int i = 0;
         i < v.numCombustiveis;
         i++)
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

Veiculo *leitorCSV(char *caminhoArquivo,
                   int *numVeiculos)
{
    FILE *f = fopen(caminhoArquivo, "r");

    if (f == NULL)
    {
        return NULL;
    }

    char linha[2048];

    fgets(linha, sizeof(linha), f);

    Veiculo *veiculos =
        malloc(10000 * sizeof(Veiculo));

    int count = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        if (strlen(linha) > 3)
        {
            veiculos[count] =
                parseVeiculo(linha);

            count++;
        }
    }

    fclose(f);

    *numVeiculos = count;

    return veiculos;
}

int getMaiorCilindros(Veiculo *veiculo, int n)
{
    int maior = veiculo[0].cilindros;

    for (int i = 1; i < n; i++)
    {
        if (veiculo[i].cilindros > maior)
        {
            maior = veiculo[i].cilindros;
        }
    }

    return maior;
}

void countingSort(Veiculo *veiculo, int n)
{
    if (n <= 1)
    {
        return;
    }

    int maior =
        getMaiorCilindros(veiculo, n);

    int *count =
        calloc(maior + 1, sizeof(int));

    Veiculo *ordenado =
        malloc(n * sizeof(Veiculo));

    for (int i = 0; i < n; i++)
    {
        count[veiculo[i].cilindros]++;
    }

    for (int i = 1; i <= maior; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int cilindros =
            veiculo[i].cilindros;

        ordenado[count[cilindros] - 1] =
            veiculo[i];

        count[cilindros]--;
    }

    for (int i = 0; i < n; i++)
    {
        veiculo[i] = ordenado[i];
    }

    free(count);
    free(ordenado);
}

int main()
{
    int numVeiculos = 0;

    Veiculo *veiculos =
        leitorCSV(
            "/tmp/veiculos.csv",
            &numVeiculos
        );

    if (veiculos == NULL)
    {
        return 1;
    }

    Veiculo selecionados[1000];

    int numSelecionados = 0;

    int idBusca;

    while (scanf("%d", &idBusca) == 1)
    {
        if (idBusca == -1)
        {
            break;
        }

        for (int i = 0;
             i < numVeiculos;
             i++)
        {
            if (veiculos[i].id == idBusca)
            {
                selecionados[numSelecionados] =
                    veiculos[i];

                numSelecionados++;

                break;
            }
        }
    }

    countingSort(
        selecionados,
        numSelecionados
    );

    char bufferOut[2048];

    for (int i = 0;
         i < numSelecionados;
         i++)
    {
        formatVeiculo(
            selecionados[i],
            bufferOut
        );

        printf("%s\n", bufferOut);
    }

    free(veiculos);

    return 0;
}