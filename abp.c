#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 500

PtABP* inicializa_abp()
{
    return NULL;
}

PtABP* consulta_abp(PtABP *a, char p)
{
    if (a==NULL)
        return NULL;
    else if (a->palavra == p)
        return a;
    else if (a->palavra > p)
        return consulta_abp(a->esquerda, p);
    else
        return consulta_abp(a->direita, p);
}

PtABP* insere_abp(PtABP *a, char p)
{
    if (!a)
    {
        a = (PtABP*) malloc(sizeof(PtABP));
        a->palavra = p;
        a->esquerda = NULL;
        a->direita = NULL;
    }
    else if (p < (a->palavra))
        a->esquerda = insere_abp(a->esquerda, p);
    else
        a->direita = insere_abp(a->direita, p);
    return a;
}

int conta_abp(PtABP *a)
{
    if(!a)
        return 0;
    else
    {
        return 1 + conta_abp(a->esquerda) + conta_abp(a->direita);
    }
}

void imprime_abp_lista(PtABP *a)
{
    if(a)
    {
        printf("%i", a->palavra);
        imprime_abp_lista(a->esquerda);
        imprime_abp_lista(a->direita);
    }
}

void imprime_abp(PtABP *a, int nv)
{
    if(a)
    {
        for (int i = 1; i <= nv; i++)
            printf("=");
        printf("%i\n", a->palavra);
        nv++;
        imprime_abp(a->esquerda, nv);
        imprime_abp(a->direita, nv);
    }
}
