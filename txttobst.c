#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "texto.h"

#define LINHAS 5000
#define PARAM 4

/**
 * TXTTOBST 1.0.0:
 * Recebe dois arquivos de texto como entrada, o primeiro é um texto, o segundo um conjunto de operações. Converte todos caracteres do texto para caixa baixa e,
 * passa cada palavra do texto para uma ABP de strings, em seguida, aplica as operações contidas no segundo arquivo e emite um relatório das operações aplicadas e seus resultados.
 * Exemplo de chamada "compararvores entrada.txt operacoes.txt saida.txt"
 */

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"portuguese"); //para imprimir corretamente na tela os caracteres acentuados, tive colocar "portuguese" pois minha máquina está com system locale configurado para inglês
    clock_t start_ger, end_ger, start_rel, end_rel; //para contar o tempo de execução do programa

    FILE *entrada;
    FILE *temp;
    FILE *op;
    FILE *saida;
    FILE *resultado;

    PtABP *abp;
    abp = inicializa_abp();
    int nodos, altura, fb, comp_ger = 0, comp_rel = 0;
    double miliseconds_ger, miliseconds_rel;

    if(argc!=PARAM)
    {
        printf("Número incorreto de argumentos.\nPara chamar o programa, digite: \"compararvores <entrada>.txt operacoes.txt <saida>.txt\".\n");
        return 1;
    }
    else
    {
        entrada = fopen (argv[1], "r");
        if (!entrada)
        {
            printf("Erro ao abrir o arquivo %s.",argv[1]);
            return 1;
        }
        temp = fopen("temp.txt", "w");
        op = fopen (argv[2], "r");
        saida = fopen(argv[3], "w");
        resultado = fopen("resultado.txt", "w");

        start_ger = clock(); //inicia a contagem do tempo

        caixa_baixa(entrada, temp);

        temp = fopen("temp.txt", "r");

        abp = le_para_abp(temp, &comp_ger);

        end_ger = clock(); //finaliza contagem do tempo
        miliseconds_ger = (double)(end_ger - start_ger) / CLOCKS_PER_SEC; //calcula o tempo decorrido

        start_rel = clock();

        nodos = conta_abp(abp);
        altura = altura_abp(abp);
        fb = fator_balanceamento_abp(abp);

        le_operacoes(op, resultado, abp, &comp_rel);

        resultado = fopen("resultado.txt", "r");

        end_rel = clock(); //finaliza contagem do tempo
        miliseconds_rel = (double)(end_rel - start_rel) / CLOCKS_PER_SEC; //calcula o tempo decorrido

        relatorio_abp(saida, resultado, abp, nodos, altura, fb, miliseconds_ger, miliseconds_rel, comp_ger, comp_rel);
        return 0;
    }
}
