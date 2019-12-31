#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 500
#define PARAM 2

/**
 * TXTTOBST 0.2.0-beta:
 * Recebe um arquivo texto como entrada, converte todos caracteres para caixa baixa e, passa cada palavra do texto para uma ABP de strings.
 * Exemplo de chamada "compararvores entrada.txt"
 */

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"portuguese"); //para imprimir corretamente na tela os caracteres acentuados, tive colocar "portuguese" pois minha máquina está com system locale configurado para inglês
    clock_t start, end; //para contar o tempo de execução do programa

    FILE *entrada;
    FILE *saida;

    PtABP *abp;
    abp = inicializa_abp();

    if (argc!=PARAM)
    {
        printf ("Número incorreto de argumentos.\nPara chamar o programa, digite: \"compararvores <entrada>.txt <saida>.txt\".\n");
        return 1;
    }
    else
    {
        entrada = fopen (argv[1], "r");
        if (!entrada)
        {
            printf ("Erro ao abrir o arquivo %s.",argv[1]);
            return 1;
        }
        saida = fopen ("temp.txt", "w");

        start = clock(); //inicia a contagem do tempo

        caixa_baixa(entrada, saida);

        saida = fopen("temp.txt", "r");

        abp = le_para_abp(saida);

        printf("Imprimindo ABP em lista:");
        imprime_abp_lista(abp);
        printf("\nImprimindo ABP em níveis:\n");
        imprime_abp(abp, 0);

        end = clock(); //finaliza contagem do tempo

        float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
        printf("Tempo: %i ms\n", (int)miliseconds);

        return 0;
    }
}
