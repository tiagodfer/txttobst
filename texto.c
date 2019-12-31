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
 * LE_PARA_ARRAY
 * FILE *entrada: ponteiro para o arquivo que será lido;
 * char vetor[LINHAS][LINHAS]: array de strings de saída;
 * Retorna array de strings, cada array contendo uma palavra do arquivo lido.
 */

void le_para_array(FILE *entrada, char vetor[LINHAS][LINHAS])
{
    char *palavra, linha[LINHAS];
    int i = 0;

    while (fgets(linha,LINHAS,entrada)) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok (linha, " "); //tokeniza usando como delimitador o espaço em branco
        while (palavra != NULL)
        {
            strcpy(vetor[i], palavra); //copia palavras para o array de strings
            i++;
            palavra = strtok (NULL, " ");
        }
    }
    fclose (entrada);
}
