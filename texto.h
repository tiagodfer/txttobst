#define LINHAS 5000

void caixa_baixa_abp(FILE *entrada, PtABP **abp, int *comp_ger);
void le_operacoes(FILE *op, FILE *resultado, PtABP *print, PtABP *abp, int *comp_rel);
void relatorio_abp(FILE *saida, FILE *resultado, PtABP *abp, int nodos, int altura, int fb, double miliseconds_ger, double miliseconds_rel, int comp_ger, int comp_rel);
