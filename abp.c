#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 5000
#define MAX 50

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
 * Verifica se ABP � vazia e incrementa contador de compara��es.
 *
 * ABP: ponteiro para a ABP a ser verificada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int vazia_abp(PtABP *abp, int *comp)
{
    (*comp)++;
    if(!abp)
        return 1;
    else
        return 0;
}

/**
 * COMPARA (INT)
 * Compara strings e incrementa contador de compara��es.
 *
 * ABP: ponteiro para a ABP a ser verificada;
 * PALAVRA: ponteiro para a palavra a ser comparada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int compara(PtABP *abp, char palavra[MAX], int *comp)
{
    (*comp)++;
    return (strcmp(abp->palavra, palavra));
}

/**
 * MAIOR (INT)
 * Compara inteiros, se I � maior que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int maior(int i, int j, int *comp)
{
    (*comp)++;
    return i > j;
}

/**
 * MAIOR_IGUAL (INT)
 * Compara inteiros, se I � maior ou igual que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int maior_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i >= j;
}

/**
 * MENOR (INT)
 * Compara inteiros, se I � menor que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int menor(int i, int j, int *comp)
{
    (*comp)++;
    return i < j;
}

/**
 * MENOR_IGUAL (INT)
 * Compara inteiros, se I � menor ou igual que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int menor_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i <= j;
}

/**
 * IGUAL (INT)
 * Compara inteiros, se I � igual a J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int igual(int i, int j, int *comp)
{
    (*comp)++;
    return i == j;
}

/**
 * INSERE_ABP (PTABP)
 * Insere nodo na ABP, incrementando contador de compara��es.
 *
 * ABP: ponteiro para a ABP que est� recebendo o novo nodo;
 * P: ponteiro para a palavra a ser inserida;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
PtABP* insere_abp(PtABP *abp, char p[], int *comp)
{
    if(vazia_abp(abp, comp))
    {
        abp = (PtABP*) malloc(sizeof(PtABP));
        strcpy(abp->palavra, p);
        abp->esquerda = NULL;
        abp->direita = NULL;
        abp->frequencia = 1;
    }
    else if((compara(abp, p, comp)) == 0)
        abp->frequencia++;
    else if((compara(abp, p, comp)) < 0)
        abp->direita = insere_abp(abp->direita, p, comp);
    else
        abp->esquerda = insere_abp(abp->esquerda, p, comp);
    return abp;
}

/**
 * INSERE_ABP_FREQ (PTABP)
 * Insere nodo na ABP, desta vez usando frequ�ncia como crit�rio, incrementando contador de compara��es.
 *
 * ABP0: ponteiro para a ABP que est� recebendo o novo nodo;
 * ABP1: ponteiro para a ABP com palavra a ser inserida;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
PtABP* insere_abp_freq(PtABP *abp0, PtABP *abp1, int *comp)
{
    if(vazia_abp(abp0, comp))
    {
        abp0 = (PtABP*) malloc(sizeof(PtABP));
        strcpy(abp0->palavra, abp1->palavra);
        abp0->frequencia = abp1->frequencia;
        abp0->esquerda = NULL;
        abp0->direita = NULL;
    }
    else if(menor(abp0->frequencia, abp1->frequencia, comp))
        abp0->direita = insere_abp_freq(abp0->direita, abp1, comp);
    else
        abp0->esquerda = insere_abp_freq(abp0->esquerda, abp1, comp);
    return abp0;
}

/**
 * CONTA_ABP (INT)
 * Conta n�mero de nodos da ABP, incrementando contador de compara��es.
 *
 * ABP: ponteiro para a ABP cujos nodos ser�o contados;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int conta_abp(PtABP *abp, int *comp)
{
    if(vazia_abp(abp, comp))
        return 0;
    else
    {
        return 1 + conta_abp(abp->esquerda, comp) + conta_abp(abp->direita, comp);
    }
}

/**
 * AUX_FREQUENCIA_ABP (INT)
 * Conta n�mero de ocorr�ncias de uma palavra dentro da ABP, incrementando contador de compara��es.
 *
 * ABP: ponteiro para a ABP com a palavra a ser buscada;
 * P: ponteiro para a palavra buscada cujas ocorr�ncias ser�o devolvidas;
 * COMP: ponteiro para o n�mero de compara��oes realizadas.
 */
int aux_frequencia_abp(PtABP *abp, char p[], int *comp)
{
    if(vazia_abp(abp, comp))
        return 0;
    else if((compara(abp, p, comp)) == 0)
    {
        return abp->frequencia;
    }
    else if((compara(abp, p, comp)) > 0)
    {
        return aux_frequencia_abp(abp->esquerda, p, comp);
    }
    else
        return aux_frequencia_abp(abp->direita, p, comp);
}

/**
 * FREQUENCIA_ABP (VOID)
 * Imprime no arquivo saida a frequ�ncia de ocorr�ncia palavra solicitada, incrementando contador de compara��es.
 *
 * SAIDA: ponteiro para o arquivo de sa�da;
 * ABP: ponteiro para a ABP onde a palavra ser� pesquisada;
 * P: ponteiro para a palavra pesquisada;
 * COMP: ponteiro para o n�mero de compara��oes realizadas.
 */
void frequencia_abp(FILE *saida, PtABP *abp, char p[], int *comp)
{
    fprintf(saida, "*************************************************************\n");
    fprintf(saida, "F %s\n%s: %i\n", p, p, aux_frequencia_abp(abp, p, comp));
}

/**
 * CONTADOR_ABP (VOID)
 * Controla a chamada da fun��o AUX_CONTADOR_ABP, chamando uma vez para cada frequ�ncia da s�rie solicitada, incrementando contador de compara��es.
 *
 * SAIDA: ponteiro para o arquivo de sa�da;
 * ABP: ponteiro para a ABP onde as palavras ser�o pesquisadas;
 * F0: frequ�ncia inicial das palavras buscadas;
 * F1: frequ�ncia final das palavras buscadas;
 * COMP: ponteiro para o n�mero de compara��oes realizadas.
 */
void contador_abp(PtABP **abp0, PtABP *abp, int f0, int f1, int *comp)
{
    if(!(vazia_abp(abp, comp)))
    {
        contador_abp(abp0, abp->esquerda, f0, f1, comp);
        if(maior_igual(abp->frequencia, f0, comp) && menor_igual(abp->frequencia, f1, comp))
            *abp0 = insere_abp_freq(*abp0, abp, comp);
        contador_abp(abp0, abp->direita, f0, f1, comp);
    }
}

/**
 * ALTURA_ABP (INT)
 * Calcula a altura da ABP, incrementando contador de compara��es.
 *
 * ABP: ponteiro para a ABP cuja altura ser� calculada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int altura_abp(PtABP *abp, int *comp)
{
    int altura_esquerda = 0;
    int altura_direita = 0;

    if(vazia_abp(abp, comp))
        return 0;
    else
    {
        altura_esquerda = altura_abp(abp->esquerda, comp);
        altura_direita = altura_abp(abp->direita, comp);
        if(altura_esquerda > altura_direita)
            return (1 + altura_esquerda);
        else
            return (1 + altura_direita);
    }
}

/**
 * FATOR_BALANCEAMENTO_NODO (INT)
 * Retorna o FB do nodo, incrementando contador de compara��es.
 *
 * ABP: ponteiro para o nodo cuja altura ser� calculada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int fator_balanceamento_nodo(PtABP *abp, int *comp)
{
    return (altura_abp(abp->esquerda, comp) - altura_abp(abp->direita, comp));
}

/**
 * FATOR_BALANCEAMENTO_ABP (INT)
 * Retorna o FB da ABP, incrementando contador de compara��es.
 *
 * ABP: ponteiro para a ABP cuja altura ser� calculada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int fator_balanceamento_abp(PtABP *abp, int *comp)
{
    int fator = fator_balanceamento_nodo(abp, comp);

    if(vazia_abp(abp, comp))
        return 0;
    else
    {
        if(abp->esquerda)
        {
            if(abs(fator) <= abs(fator_balanceamento_nodo(abp->esquerda, comp)))
                fator = fator_balanceamento_nodo(abp->esquerda, comp);
        }
        if(abp->direita)
        {
            if(abs(fator) <= abs(fator_balanceamento_nodo(abp->direita, comp)))
            fator = fator_balanceamento_nodo(abp->direita, comp);
        }
        return fator;
    }
}

/**
 * AUX_IMPRIME_ABP (VOID)
 * Imprime ABP no arquivo, em ordem decrescente pela frequ�ncia, incrementando contador de compara��es.
 *
 * RESULTADO: ponteiro para o arquivo de sa�da;
 * ABP: ponteiro para a ABP cuja altura ser� impressa;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void aux_imprime_abp(FILE *resultado, PtABP *abp, int *comp)
{
    if(!(vazia_abp(abp, comp)))
    {
        aux_imprime_abp(resultado, abp->direita, comp);
        fprintf(resultado, "%s: %i\n", abp->palavra, abp->frequencia);
        aux_imprime_abp(resultado, abp->esquerda, comp);
    }
}

/**
 * IMPRIME_ABP (VOID)
 * Imprime ABP no arquivo, chama la�o de impress�o da fun��o auxiliar, em ordem decrescente pela frequ�ncia, incrementando contador de compara��es.
 *
 * RESULTADO: ponteiro para o arquivo de sa�da;
 * ABP: ponteiro para a ABP cuja altura ser� impressa;
 * F0: frequ�ncia inicial das palavras buscadas;
 * F1: frequ�ncia final das palavras buscadas;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void imprime_abp(FILE *resultado, PtABP *abp, int f0, int f1, int *comp)
{
    fprintf(resultado, "*************************************************************\n");
    fprintf(resultado, "C %i %i\n", f0, f1);
    aux_imprime_abp(resultado, abp, comp);
}
