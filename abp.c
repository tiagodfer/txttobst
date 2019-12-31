#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 5000

PtABP* inicializa_abp()
{
    return NULL;
}

int vazia_abp(PtABP *abp)
{
    if(!abp)
        return 1;
    else
        return 0;
}

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

int conta_abp(PtABP *abp)
{
    if(vazia_abp(abp))
        return 0;
    else
    {
        return 1 + conta_abp(abp->esquerda) + conta_abp(abp->direita);
    }
}

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

void frequencia_abp(FILE *saida, PtABP *abp, char p[], int *comp_rel)
{
    fprintf(saida, "*************************************************************\n");
    fprintf(saida, "F %s\n%s: %i\n", p, p, aux_frequencia_abp(abp, p, comp_rel));
}

void aux_contador_abp(FILE *saida, PtABP *abp, int f, int *comp_rel)
{
    if(!(vazia_abp(abp)))
    {
        (*comp_rel)++;
        aux_contador_abp(saida, abp->esquerda, f, comp_rel);
        if(abp->frequencia == f)
            fprintf(saida, "%s: %i\n", abp->palavra, abp->frequencia);
        aux_contador_abp(saida, abp->direita, f, comp_rel);
    }
}

void contador_abp(FILE *saida, PtABP *abp, int f0, int f1, int *comp_rel)
{
    if(!(vazia_abp(abp)))
    {
        fprintf(saida, "*************************************************************\n");
        fprintf(saida, "C %i %i\n", f0, f1);
        for(int i = f1; i >= f0; i--)
        {
            aux_contador_abp(saida, abp, i, comp_rel);
        }
    }
}

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

int fator_balanceamento_nodo(PtABP *abp)
{
    return (altura_abp(abp->esquerda) - altura_abp(abp->direita));
}

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
