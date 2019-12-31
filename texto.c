#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 5000

/**
 * CAIXA_BAIXA (VOID)
 * Retorna arquivo com os caracteres em caixa baixa e sem pontuação, usando apenas espaços entre as palavras.
 *
 * FILE *entrada: ponteiro para o arquivo que será lido;
 * FILE *saida: ponteiro para o arquivo de saída;
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
            fprintf(saida,"%s\n", strlwr(palavra)); //converte palavras para caixa baixa
            palavra = strtok (NULL, separador);
        }
    }
    fclose (entrada);
    fclose (saida);
}

/**
 * LE_PARA_ABP (PTABP)
 * Retorna ABP contendo as palavras do arquivo lido, computando o número de comparações necessária para tal.
 *
 * FILE *entrada: ponteiro para o arquivo que será lido;
 * COMP_GER: Número de comparaçãoes executadas.
 */
PtABP* le_para_abp(FILE *entrada, int *comp_ger)
{
    PtABP *abp;
    abp = inicializa_abp();
    char *palavra, linha[LINHAS];

    while (fgets(linha,LINHAS,entrada)) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok(linha, "\n");
        while (palavra != NULL)
        {
            abp = insere_abp(abp, palavra, comp_ger);
            palavra = strtok (NULL, "\n");
        }
    }
    fclose(entrada);
    return abp;
}

/**
 * LE_OPERAÇOES (VOID)
 * Interpreta as operações solicitadas no arquivo de texto de entrada e chama a função de acordo, imprimindo no arquivo de saída o resultado destas operações, computando o número de comparações necessária para tal.
 *
 * OP: ponteiro para o arquivo que será lido;
 * RESULTADO: ponteiro para o arquivo de saída com o resultado das operações;
 * ABP: ABP onde serão efetuadas as operações;
 * COMP_GER: Número de comparaçãoes executadas.
 */
void le_operacoes(FILE *op, FILE *resultado, PtABP *print, PtABP *abp, int *comp_rel)
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
                contador_abp(&print, abp, f0, f1, comp_rel);
                imprime_abp(resultado, print, f0, f1);
            }
            aux = strtok(NULL, " ");
        }
    }
    fclose(op);
    fclose(resultado);
}

/**
 * RELATORIO_ABP (VOID)
 * Imprime relatório final concatenando as informações obtidas.
 *
 * SAIDA: Arquivo de saída com o relatório final.
 * RESULTADO: Arquivo com os resultados das operações.
 * ABP: ABP cujos resultados serão exibidos.
 * NODOS: Número de nodos da ABP.
 * ALTURA: Altura da ABP.
 * FB: Fator de Balanceamento da ABP.
 * MILISECONDS_GER: tempo de execução da ABP.
 * MILISECONDS_REL: Tempo de execução dos resultados.
 * COMP_GER: Número de comparaçãoes executadas na montagem da ABP.
 * COMP_REL: Número de comparaçãoes executadas no cômputo dos resultados.
 */
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
