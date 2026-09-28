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
    char combStr[300] = "[";

    for (int i = 0; i < v.numCombustiveis; i++)
    {
        strcat(combStr, v.combustivel[i]);

        if (i < v.numCombustiveis - 1)
        {
            strcat(combStr, ", ");
        }
    }

    strcat(combStr, "]");

    char dataStr[30];
    formatData(v.dataRegistro, dataStr);

    sprintf(buffer,
            "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.1f ## %.1f ## %.1f ## %s ## %s]",
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

int compare(char *ch1, char *ch2)
{
    int i = 0;

    while (ch1[i] != '\0' && ch2[i] != '\0')
    {
        char c1 = ch1[i];
        char c2 = ch2[i];

        if (c1 >= 'A' && c1 <= 'Z')
        {
            c1 += 32;
        }

        if (c2 >= 'A' && c2 <= 'Z')
        {
            c2 += 32;
        }

        if (c1 != c2)
        {
            return c1 - c2;
        }

        i++;
    }

    char c1 = ch1[i];
    char c2 = ch2[i];

    if (c1 >= 'A' && c1 <= 'Z')
    {
        c1 += 32;
    }

    if (c2 >= 'A' && c2 <= 'Z')
    {
        c2 += 32;
    }

    return c1 - c2;
}

void selectionSort(Veiculo *veiculos, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;

        for (int j = i + 1; j < n; j++)
        {
            int comp = compare(veiculos[j].modelo, veiculos[menor].modelo);

            if (comp < 0 ||
                (comp == 0 && veiculos[j].id < veiculos[menor].id))
            {
                menor = j;
            }
        }

        if (menor != i)
        {
            Veiculo temp = veiculos[i];
            veiculos[i] = veiculos[menor];
            veiculos[menor] = temp;
        }
    }
}

int binarySearch(Veiculo *veiculos, int n, char *searchModel)
{
    int esq = 0;
    int dir = n - 1;

    while (esq <= dir)
    {
        int meio = (esq + dir) / 2;
        int comp = compare(searchModel, veiculos[meio].modelo);

        if (comp == 0)
        {
            return true;
        }
        else if (comp < 0)
        {
            dir = meio - 1;
        }
        else
        {
            esq = meio + 1;
        }
    }

    return false;
}

void tiraQuebraLinha(char *linha)
{
    int len = 0;

    while (linha[len] != '\0')
    {
        len++;
    }

    if (len > 0 && linha[len - 1] == '\n')
    {
        linha[len - 1] = '\0';
    }

    if (len > 1 && linha[len - 2] == '\r')
    {
        linha[len - 2] = '\0';
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

    Veiculo selecionados[1000];
    int numSelecionados = 0;

    int idBusca;
    char linha[1000];

    while (fgets(linha, sizeof(linha), stdin) != NULL)
    {
        tiraQuebraLinha(linha);

        if (atoi(linha) == -1)
        {
            break;
        }

        idBusca = atoi(linha);

        for (int i = 0; i < numVeiculos; i++)
        {
            if (veiculos[i].id == idBusca)
            {
                selecionados[numSelecionados] = veiculos[i];
                numSelecionados++;
                break;
            }
        }
    }

    selectionSort(selecionados, numSelecionados);

    while (fgets(linha, sizeof(linha), stdin) != NULL)
    {
        tiraQuebraLinha(linha);

        if (compare(linha, "FIM") == 0)
        {
            break;
        }

        if (binarySearch(selecionados, numSelecionados, linha))
        {
            printf("SIM\n");
        }
        else
        {
            printf("NAO\n");
        }
    }

    free(veiculos);

    return 0;
}