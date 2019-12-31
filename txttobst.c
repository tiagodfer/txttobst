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
 * COMPARÁRVORES 0.1.0-alpha:
 * Recebe um arquivo texto como entrada, converte todos caracteres para caixa baixa e, passa cada palavra do texto para um array de strings.
 * Exemplo de chamada "compararvores entrada.txt"
 */

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"portuguese"); //para imprimir corretamente na tela os caracteres acentuados, tive colocar "portuguese" pois minha máquina está com system locale configurado para inglês
    clock_t start, end; //para contar o tempo de execução do programa

    FILE *entrada;
    FILE *saida;

    char vetor[LINHAS][LINHAS];

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

        le_para_array(saida, vetor);

        end = clock(); //finaliza contagem do tempo

        printf("\nArquivo temp.txt gerado com sucesso.\n");

        float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
        printf("Tempo: %i ms\n", (int)miliseconds);

        return 0;
    }
}
