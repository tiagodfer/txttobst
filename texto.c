#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 5000

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

PtABP* le_para_abp(FILE *entrada, int *comp_ger)
{
    PtABP *abp;
    abp = inicializa_abp();
    char *palavra, linha[LINHAS];

    while (fgets(linha,LINHAS,entrada)) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok(linha, " ");
        while (palavra != NULL)
        {
            abp = insere_abp(abp, palavra, comp_ger);
            palavra = strtok (NULL, " ");
        }
    }
    fclose(entrada);
    return abp;
}

void le_operacoes(FILE *op, FILE *resultado, PtABP *abp, int *comp_rel)
{
    char *aux, *palavra, linha[LINHAS];
    int f0, f1;

    while (fgets(linha,LINHAS,op))
    {
        aux = strtok(linha, " ");
        while (aux != NULL)
        {
            if(strcmp(aux, "F") == 0 || strcmp(aux, "f") == 0)
            {
                palavra = strtok(NULL, "\n");
                frequencia_abp(resultado, abp, palavra, comp_rel);
            }
            else if(strcmp(aux, "C") == 0 || strcmp(aux, "c") == 0)
            {
                f0 = atoi(strtok(NULL, " "));
                f1 = atoi(strtok(NULL, "\n"));
                contador_abp(resultado, abp, f0, f1, comp_rel);
            }
            aux = strtok(NULL, " ");
        }
    }
    fclose(op);
    fclose(resultado);
}

void relatorio_abp(FILE *saida, FILE *resultado, PtABP *abp, int nodos, int altura, int fb, double miliseconds_ger, double miliseconds_rel, int comp_ger, int comp_rel)
{
    char aux;

    fprintf(saida, "**********ESTATÍSTICAS DA GERAÇÃO DA ÁRVORE ABP *************\n");
    fprintf(saida, "Número de Nodos: %i\n", nodos);
    fprintf(saida, "Altura: %i\n", altura);
    fprintf(saida, "Fator de Balanceamento: %i\n", fb);
    fprintf(saida, "Tempo: %f s\n", miliseconds_ger);
    fprintf(saida, "Comparações: %i\n", comp_ger);
    while((aux = fgetc(resultado)) != EOF)
        fputc(aux, saida);
    fprintf(saida, "\n");
    fprintf(saida, "Tempo: %f s\n", miliseconds_rel);
    fprintf(saida, "Comparações: %i\n", comp_rel);
    fclose(saida);
    fclose(resultado);
}
