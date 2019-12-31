#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 5000

/**
 * INICIALIZA_ABP (PTABP)
 * Inicializa ABP com NULL.
 */
PtABP* inicializa_abp()
{
    return NULL;
}

/**
 * VAZIA_ABP (INT)
 * Verifica se ABP é vazia.
 *
 * ABP: ABP a ser verificada.
 */
int vazia_abp(PtABP *abp)
{
    if(!abp)
        return 1;
    else
        return 0;
}

/**
 * INSERE_ABP (PTABP)
 * Insere nodo na ABP, computando o número de comparações necessária para tal.
 *
 * ABP: ABP que está recebendo o novo nodo;
 * P: Nodo a ser inserido;
 * COMP_GER: Número de comparações executadas.
 */
PtABP* insere_abp(PtABP *abp, char p[], int *comp_ger)
{
    (*comp_ger)++;
    if(vazia_abp(abp))
    {
        abp = (PtABP*) malloc(sizeof(PtABP));
        strcpy(abp->palavra, p);
        abp->esquerda = NULL;
        abp->direita = NULL;
        abp->frequencia = 1;
    }
    else if(strcmp(abp->palavra, p) == 0)
        abp->frequencia++;
    else if(strcmp(abp->palavra, p) < 0)
        abp->direita = insere_abp(abp->direita, p, comp_ger);
    else
        abp->esquerda = insere_abp(abp->esquerda, p, comp_ger);
    return abp;
}

PtABP* insere_abp_freq(PtABP *print, PtABP *abp, int *comp_rel)
{
    (*comp_rel)++;
    if(vazia_abp(print))
    {
        print = (PtABP*) malloc(sizeof(PtABP));
        strcpy(print->palavra, abp->palavra);
        print->frequencia = abp->frequencia;
        print->esquerda = NULL;
        print->direita = NULL;
    }
    else if(print->frequencia < abp->frequencia)
        print->direita = insere_abp_freq(print->direita, abp, comp_rel);
    else
        print->esquerda = insere_abp_freq(print->esquerda, abp, comp_rel);
    return print;
}

/**
 * CONTA_ABP (INT)
 * Conta número de nodos da ABP.
 *
 * ABP: ABP cujos nodos serão contados.
 */
int conta_abp(PtABP *abp)
{
    if(vazia_abp(abp))
        return 0;
    else
    {
        return 1 + conta_abp(abp->esquerda) + conta_abp(abp->direita);
    }
}

/**
 * AUX_FREQUENCIA_ABP (INT)
 * Conta número de ocorrências de uma palavra dentro da ABP, computando o número de comparações necessária para tal.
 *
 * ABP: ABP com a palavra a ser buscada;
 * P: Palavra buscada cujas ocorrências serão devolvidas;
 * COMP_REL: Número de comparaçãoes executadas.
 */
int aux_frequencia_abp(PtABP *abp, char p[], int *comp_rel)
{
    if (vazia_abp(abp))
        return 0;
    else if(strcmp(abp->palavra, p) == 0)
    {
        (*comp_rel)++;
        return abp->frequencia;
    }
    else if(strcmp(abp->palavra, p) > 0)
    {
        (*comp_rel)++;
        return aux_frequencia_abp(abp->esquerda, p, comp_rel);
    }
    else
        return aux_frequencia_abp(abp->direita, p, comp_rel);
}

/**
 * FREQUENCIA_ABP  (VOID)
 * Imprime no arquivo saida a frequência de ocorrência palavra solicitada, computando o número de comparações necessária para tal.
 *
 * SAIDA: Arquivo de saída;
 * ABP: ABP onde a palavra será pesquisada;
 * P: Palavra pesquisada;
 * COMP_REL: Número de comparaçãoes executadas.
 */
void frequencia_abp(FILE *saida, PtABP *abp, char p[], int *comp_rel)
{
    fprintf(saida, "*************************************************************\n");
    fprintf(saida, "F %s\n%s: %i\n", p, p, aux_frequencia_abp(abp, p, comp_rel));
}

/**
 * CONTADOR_ABP  (VOID)
 * Controla a chamada da função AUX_CONTADOR_ABP, chamando uma vez para cada frequência da série solicitada.
 *
 * SAIDA: Arquivo de saída;
 * ABP: ABP onde as palavras serão pesquisadas;
 * F0: Frequência inicial das palavras buscadas;
 * F1: Frequência final das palavras buscadas;
 * COMP_REL: Número de comparaçãoes executadas.
 */
void contador_abp(PtABP **print, PtABP *abp, int f0, int f1, int *comp_rel)
{
    if(!(vazia_abp(abp)))
    {
        (*comp_rel)++;
        (*comp_rel)++;
        contador_abp(print, abp->esquerda, f0, f1, comp_rel);
        if(abp->frequencia >= f0 && abp->frequencia <= f1)
            *print = insere_abp_freq(*print, abp, comp_rel);
        contador_abp(print, abp->direita, f0, f1, comp_rel);
    }
}

/**
 * ALTURA_ABP (INT)
 * Calcula a altura da ABP.
 *
 * ABP: ABP cuja altura será calculada.
 */
int altura_abp(PtABP *abp)
{
    int altura_esquerda = 0;
    int altura_direita = 0;

    if (vazia_abp(abp))
        return 0;
    else
    {
        altura_esquerda = altura_abp(abp->esquerda);
        altura_direita = altura_abp(abp->direita);
        if (altura_esquerda > altura_direita)
            return (1 + altura_esquerda);
        else
            return (1 + altura_direita);
    }
}

/**
 * FATOR_BALANCEAMENTO_NODO (INT)
 * Retorna o FB do nodo.
 *
 * ABP: Nodo cuja altura será calculada.
 */
int fator_balanceamento_nodo(PtABP *abp)
{
    return (altura_abp(abp->esquerda) - altura_abp(abp->direita));
}

/**
 * FATOR_BALANCEAMENTO_ABP (INT)
 * Retorna o FB da ABP.
 *
 * ABP: ABP cuja altura será calculada.
 */
int fator_balanceamento_abp(PtABP *abp)
{
    int fator = fator_balanceamento_nodo(abp);

    if(vazia_abp(abp))
        return 0;
    else
    {
        if (abp->esquerda)
        {
            if (abs(fator) <= abs(fator_balanceamento_nodo(abp->esquerda)))
                fator = fator_balanceamento_nodo(abp->esquerda);
        }
        if (abp->direita)
        {
            if (abs(fator) <= abs(fator_balanceamento_nodo(abp->direita)))
            fator = fator_balanceamento_nodo(abp->direita);
        }
        return fator;
    }
}

void aux_imprime_abp(FILE *resultado, PtABP *print)
{
    if(!(vazia_abp(print)))
    {
        aux_imprime_abp(resultado, print->direita);
        fprintf(resultado, "%s: %i\n", print->palavra, print->frequencia);
        aux_imprime_abp(resultado, print->esquerda);
    }
}

void imprime_abp(FILE *resultado, PtABP *print, int f0, int f1)
{
    fprintf(resultado, "*************************************************************\n");
    fprintf(resultado, "C %i %i\n", f0, f1);
    aux_imprime_abp(resultado, print);
}
