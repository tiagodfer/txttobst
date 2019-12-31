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
 * TXTTOBST 1.2.3:
 * Recebe dois arquivos de texto como entrada, o primeiro é um texto, o segundo um conjunto de operações. Converte todos caracteres do texto para caixa baixa e,
 * passa cada palavra do texto para uma ABP de strings, em seguida, aplica as operações contidas no segundo arquivo e emite um relatório das operações aplicadas e seus resultados.
 * Um otimização na função CONTADOR_ABP evita que se percorra a árvore em vão quando se busca uma frequência a qual nenhuma palavra na ABP tem.
 * Exemplo de chamada "compararvores entrada.txt operacoes.txt saida.txt"
 */

/**
 * MAIN (INT)
 * Recebe dois arquivos de texto como entrada, o primeiro é um texto, o segundo um conjunto de operações. Converte todos caracteres do texto para caixa baixa e,
 * passa cada palavra do texto para uma ABP de strings, em seguida, aplica as operações contidas no segundo arquivo e emite um relatório das operações aplicadas e seus resultados.
 * Exemplo de chamada "compararvores entrada.txt operacoes.txt saida.txt"
 *
 * ARGV[1]: texto de entrada;
 * ARGV[2]: texto com as operações;
 * ARGV[3]: texto de saída.
 */
int main(int argc, char *argv[])
{
    //configuração do System Locale
    setlocale(LC_ALL,"portuguese"); //para imprimir corretamente na tela os caracteres acentuados, tive colocar "portuguese" pois minha máquina está com system locale configurado para inglês

    //declaração de variáveis
    clock_t start_ger, end_ger, start_rel, end_rel; //para contar o tempo de execução do programa
    FILE *entrada, *op, *resultado, *saida;         //entrada recebe argv[1]; temp recebe o texto convertido para caixa baixa; op recebe argv[2]; resultado recebe o resultado das operações; saida recebe o relatório final
    PtABP *abp, *print;                             //abp recebe a árvore binária de pesquisa (ABP); print recebe a ABP apenas com as palavras com a frequência solicitada
    int nodos, altura, fb, comp_ger, comp_rel;      //nodos recebe o número de nodos; altura recebe a altura da árvore; fb recebe o fator de balanceamento (FB) da árvore; comp_ger recebe o número de comparações realizadas para gerar a árvore binária de pequisa; comp_rel recebe o número de comparações realizadas da geração dos resultados das operações
    double miliseconds_ger, miliseconds_rel;        //miliseconds_ger recebe o tempo de execução da geração da ABP; miliseconds_rel recebe o tempo de execução da geração dos resultados das operações

    //inicialização de variáveis
    abp = inicializa_abp();
    print = inicializa_abp();
    comp_ger = 0;
    comp_rel = 0;

    //início do programa
    if(argc!=PARAM) //testa se números de parâmetros para chamada do programa está correto, caso contrário exibe mensagem de erro, encerrando execução com código 1
    {
        printf("Número incorreto de argumentos.\nPara chamar o programa, digite: \"compararvores <entrada>.txt operacoes.txt <saida>.txt\".\n");
        return 1;
    }
    else
    {
        entrada = fopen (argv[1], "r"); //abre argv[1] e em seguida testa se sua abertura foi bem sucedida, caso contrário, encerra execução com código 1
        if (!entrada)
        {
            printf("Erro ao abrir o arquivo %s.",argv[1]);
            return 1;
        }
        op = fopen (argv[2], "r"); //abre argv[2] e em seguida testa se sua abertura foi bem sucedida, caso contrário, encerra execução com código 1
        if (!op)
        {
            printf("Erro ao abrir o arquivo %s.",argv[2]);
            return 1;
        }
        saida = fopen(argv[3], "w");
        resultado = fopen("resultado.txt", "w");

        //geração da ABP com as palavras do texto argv[1]
        start_ger = clock();                                              //inicia a contagem do tempo
        caixa_baixa_abp(entrada, &abp, &comp_ger);                        //converte argv[1] para caixa baixa e exporta o resultado para temp.txt
        end_ger = clock();                                                //finaliza contagem do tempo
        miliseconds_ger = (double)(end_ger - start_ger) / CLOCKS_PER_SEC; //calcula o tempo decorrido

        //realização das operações contidas em argv[2]
        start_rel = clock();                                              //inicia a contagem do tempo
        nodos = conta_abp(abp, &comp_rel);                                //calcula número de nodos da ABP
        altura = altura_abp(abp, &comp_rel);                              //calcula altura da ABP
        fb = fator_balanceamento_abp(abp, &comp_rel);                     //calcula FB da ABP
        le_operacoes(op, resultado, print, abp, &comp_rel);               //interpreta e realiza as operações solicitadas
        resultado = fopen("resultado.txt", "r");                          //abre resultado.txt par leitura
        end_rel = clock();                                                //finaliza contagem do tempo
        miliseconds_rel = (double)(end_rel - start_rel) / CLOCKS_PER_SEC; //calcula o tempo decorrido

        //gera relatório
        relatorio_abp(saida, resultado, abp, nodos, altura, fb, miliseconds_ger, miliseconds_rel, comp_ger, comp_rel);
        return 0;
    }
}
