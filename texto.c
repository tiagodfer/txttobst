#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 5000

/**
 * CAIXA_BAIXA_ABP (VOID)
 * Retorna ABP com os caracteres em caixa baixa e sem pontua��o, incrementando contador de compara��es.
 *
 * ENTRADA: ponteiro para o arquivo que ser� lido;
 * ABP: ponteiro duplo para a ABP de sa�da;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void caixa_baixa_abp(FILE *entrada, PtABP **abp, int *comp)
{
    char *palavra, linha[LINHAS];
    char separador[]= {" ,.&*%\?!;/'@-\"$#=><()][}{:\n\t"};

    while (fgets(linha,LINHAS,entrada)) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok (linha, separador); //tokeniza usando como delimitador os caracteres em "separador"
        while (palavra != NULL)
        {
            *abp = insere_abp(*abp, strlwr(palavra), comp); //converte palavras para caixa baixa
            palavra = strtok (NULL, separador);
        }
    }
    fclose (entrada);
}

/**
 * LE_OPERA�OES (VOID)
 * Interpreta as opera��es solicitadas no arquivo de texto de entrada e chama a fun��o de acordo, imprimindo no arquivo de sa�da o resultado destas opera��es, incrementando contador de compara��es.
 *
 * OP: ponteiro para o arquivo que ser� lido;
 * RESULTADO: ponteiro para o arquivo de sa�da com o resultado das opera��es;
 * ABP0: ponteiro para a ABP que ir� receber as palavras ordenadas por frequ�ncia;
 * ABP1: ponteiro para a ABP resultante da leitura do texto;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void le_operacoes(FILE *op, FILE *resultado, PtABP *abp0, PtABP *abp1, int *comp)
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
                frequencia_abp(resultado, abp1, palavra, comp);
            }
            else if(strcmp(aux, "C") == 0 || strcmp(aux, "c") == 0)
            {
                f0 = atoi(strtok(NULL, " "));
                f1 = atoi(strtok(NULL, "\n"));
                contador_abp(&abp0, abp1, f0, f1, comp);
                imprime_abp(resultado, abp0, f0, f1, comp);
                abp0 = destroi_abp(abp0, comp);
            }
            aux = strtok(NULL, " ");
        }
    }
    fclose(op);
    fclose(resultado);
}

/**
 * RELATORIO_ABP (VOID)
 * Imprime relat�rio final concatenando as informa��es obtidas.
 *
 * SAIDA: ponteiro para o arquivo de sa�da com o relat�rio final.
 * RESULTADO: ponteiro para o arquivo com os resultados das opera��es.
 * ABP: ponteiro para a ABP cujos resultados ser�o exibidos.
 * NODOS: n�mero de nodos da ABP.
 * ALTURA: altura da ABP.
 * FB: fator de balanceamento da ABP.
 * MILISECONDS_GER: tempo de execu��o da ABP.
 * MILISECONDS_REL: tempo de execu��o dos resultados.
 * COMP_GER: n�mero de compara��oes realizadas na montagem da ABP oriunda do texto.
 * COMP_REL: n�mero de compara��oes executadas no c�mputo dos resultados.
 */
void relatorio_abp(FILE *saida, FILE *resultado, PtABP *abp, int nodos, int altura, int fb, double miliseconds_ger, double miliseconds_rel, int comp_ger, int comp_rel)
{
    char aux;

    fprintf(saida, "**********ESTAT�STICAS DA GERA��O DA �RVORE ABP *************\n");
    fprintf(saida, "N�mero de Nodos: %i\n", nodos);
    fprintf(saida, "Altura: %i\n", altura);
    fprintf(saida, "Fator de Balanceamento: %i\n", fb);
    fprintf(saida, "Tempo: %f s\n", miliseconds_ger);
    fprintf(saida, "Compara��es: %i\n", comp_ger);
    while((aux = fgetc(resultado)) != EOF)
        fputc(aux, saida);
    fprintf(saida, "\n");
    fprintf(saida, "Tempo: %f s\n", miliseconds_rel);
    fprintf(saida, "Compara��es: %i\n", comp_rel);
    fclose(saida);
    fclose(resultado);
}
