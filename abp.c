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

PtABP* consulta_abp(PtABP *abp, char p[])
{
    if (!abp)
        return NULL;
    else if(strcmp(abp->palavra, p) == 0)
        return abp;
    else if(strcmp(abp->palavra, p) > 0)
        return consulta_abp(abp->esquerda, p);
    else
        return consulta_abp(abp->direita, p);
}

PtABP* insere_abp(PtABP *abp, char p[])
{
    if(!abp)
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
        abp->esquerda = insere_abp(abp->esquerda, p);
    else
        abp->direita = insere_abp(abp->direita, p);
    return abp;
}

int conta_abp(PtABP *abp)
{
    if(!abp)
        return 0;
    else
    {
        return 1 + conta_abp(abp->esquerda) + conta_abp(abp->direita);
    }
}

void imprime_abp_lista(PtABP *abp)
{
    if(abp)
    {
        printf("%s: %i, ", abp->palavra, abp->frequencia);
        imprime_abp_lista(abp->esquerda);
        imprime_abp_lista(abp->direita);
    }
}

void imprime_abp(PtABP *abp, int nv)
{
    if(abp)
    {
        for (int i = 1; i <= nv; i++)
            printf("=");
        printf("%s: %i\n", abp->palavra, abp->frequencia);
        nv++;
        imprime_abp(abp->esquerda, nv);
        imprime_abp(abp->direita, nv);
    }
}
