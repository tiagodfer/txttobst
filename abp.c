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
 * Verifica se ABP é vazia e incrementa contador de comparações.
 *
 * ABP: ponteiro para a ABP a ser verificada;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Compara strings e incrementa contador de comparações.
 *
 * ABP: ponteiro para a ABP a ser verificada;
 * PALAVRA: ponteiro para a palavra a ser comparada;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int compara(PtABP *abp, char palavra[MAX], int *comp)
{
    (*comp)++;
    return (strcmp(abp->palavra, palavra));
}

/**
 * MAIOR (INT)
 * Compara inteiros, se I é maior que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int maior(int i, int j, int *comp)
{
    (*comp)++;
    return i > j;
}

/**
 * MAIOR_IGUAL (INT)
 * Compara inteiros, se I é maior ou igual que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int maior_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i >= j;
}

/**
 * MENOR (INT)
 * Compara inteiros, se I é menor que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int menor(int i, int j, int *comp)
{
    (*comp)++;
    return i < j;
}

/**
 * MENOR_IGUAL (INT)
 * Compara inteiros, se I é menor ou igual que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int menor_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i <= j;
}

/**
 * IGUAL (INT)
 * Compara inteiros, se I é igual a J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int igual(int i, int j, int *comp)
{
    (*comp)++;
    return i == j;
}

/**
 * INSERE_ABP (PTABP)
 * Insere nodo na ABP, incrementando contador de comparações.
 *
 * ABP: ponteiro para a ABP que está recebendo o novo nodo;
 * P: ponteiro para a palavra a ser inserida;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Insere nodo na ABP, desta vez usando frequência como critério, incrementando contador de comparações.
 *
 * ABP0: ponteiro para a ABP que está recebendo o novo nodo;
 * ABP1: ponteiro para a ABP com palavra a ser inserida;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Conta número de nodos da ABP, incrementando contador de comparações.
 *
 * ABP: ponteiro para a ABP cujos nodos serão contados;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Conta número de ocorrências de uma palavra dentro da ABP, incrementando contador de comparações.
 *
 * ABP: ponteiro para a ABP com a palavra a ser buscada;
 * P: ponteiro para a palavra buscada cujas ocorrências serão devolvidas;
 * COMP: ponteiro para o número de comparaçãoes realizadas.
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
 * Imprime no arquivo saida a frequência de ocorrência palavra solicitada, incrementando contador de comparações.
 *
 * SAIDA: ponteiro para o arquivo de saída;
 * ABP: ponteiro para a ABP onde a palavra será pesquisada;
 * P: ponteiro para a palavra pesquisada;
 * COMP: ponteiro para o número de comparaçãoes realizadas.
 */
void frequencia_abp(FILE *saida, PtABP *abp, char p[], int *comp)
{
    fprintf(saida, "*************************************************************\n");
    fprintf(saida, "F %s\n%s: %i\n", p, p, aux_frequencia_abp(abp, p, comp));
}

/**
 * CONTADOR_ABP (VOID)
 * Controla a chamada da função AUX_CONTADOR_ABP, chamando uma vez para cada frequência da série solicitada, incrementando contador de comparações.
 *
 * SAIDA: ponteiro para o arquivo de saída;
 * ABP: ponteiro para a ABP onde as palavras serão pesquisadas;
 * F0: frequência inicial das palavras buscadas;
 * F1: frequência final das palavras buscadas;
 * COMP: ponteiro para o número de comparaçãoes realizadas.
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
 * Calcula a altura da ABP, incrementando contador de comparações.
 *
 * ABP: ponteiro para a ABP cuja altura será calculada;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Retorna o FB do nodo, incrementando contador de comparações.
 *
 * ABP: ponteiro para o nodo cuja altura será calculada;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int fator_balanceamento_nodo(PtABP *abp, int *comp)
{
    return (altura_abp(abp->esquerda, comp) - altura_abp(abp->direita, comp));
}

/**
 * FATOR_BALANCEAMENTO_ABP (INT)
 * Retorna o FB da ABP, incrementando contador de comparações.
 *
 * ABP: ponteiro para a ABP cuja altura será calculada;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Imprime ABP no arquivo, em ordem decrescente pela frequência, incrementando contador de comparações.
 *
 * RESULTADO: ponteiro para o arquivo de saída;
 * ABP: ponteiro para a ABP cuja altura será impressa;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Imprime ABP no arquivo, chama laço de impressão da função auxiliar, em ordem decrescente pela frequência, incrementando contador de comparações.
 *
 * RESULTADO: ponteiro para o arquivo de saída;
 * ABP: ponteiro para a ABP cuja altura será impressa;
 * F0: frequência inicial das palavras buscadas;
 * F1: frequência final das palavras buscadas;
 * COMP: ponteiro para o número de comparações realizadas.
 */
void imprime_abp(FILE *resultado, PtABP *abp, int f0, int f1, int *comp)
{
    fprintf(resultado, "*************************************************************\n");
    fprintf(resultado, "C %i %i\n", f0, f1);
    aux_imprime_abp(resultado, abp, comp);
}
