#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 500

/**
 * CAIXA_BAIXA
 * FILE *entrada: ponteiro para o arquivo que será lido;
 * FILE *saida: ponteiro para o arquivo de saída;
 * Retorna arquivo com os caracteres em caixa baixa e sem pontuação, usando apenas espaços entre as palavras.
 */

void caixa_baixa(FILE *entrada, FILE *saida)
{
    char *palavra, linha[LINHAS];
    char separador[]= {" ,.&*%\?!;/'@-\"$#=><()][}{:\n\t"};

    while (fgets(linha,LINHAS,entrada)) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok (linha, separador); //tokeniza usando como delimitador os caracteres em "separador"
        while (palavra != NULL)
        {
            fprintf(saida,"%s ", strlwr(palavra)); //converte palavras para caixa baixa
            palavra = strtok (NULL, separador);
        }
    }
    fclose (entrada);
    fclose (saida);
}

/**
 * LE_PARA_ABP
 * FILE *entrada: ponteiro para o arquivo que será lido;
 * Retorna: ABP contendo as palavras do arquivo lido.
 */

PtABP* le_para_abp(FILE *entrada)
{
    PtABP *abp;
    abp = inicializa_abp();
    char *palavra, linha[LINHAS];

    while (fgets(linha,LINHAS,entrada)) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok(linha, " ");
        while (palavra != NULL)
        {
            abp = insere_abp(abp, palavra);
            palavra = strtok (NULL, " ");
        }
    }
    return abp;
}
