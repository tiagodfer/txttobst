typedef struct TipoABP
{
    char palavra[50];
    int frequencia;
    struct TipoABP *esquerda;
    struct TipoABP *direita;
} PtABP;

PtABP* inicializa_abp();
int vazia_abp(PtABP *abp);
PtABP* insere_abp(PtABP *abp, char p[], int *comp_ger);
PtABP* insere_abp_freq(PtABP *print, PtABP *abp, int *comp_rel);
int conta_abp(PtABP *abp);
int aux_frequencia_abp(PtABP *abp, char p[], int *comp_rel);
void frequencia_abp(FILE *saida, PtABP *abp, char p[], int *comp_rel);
void contador_abp(PtABP **print, PtABP *abp, int f0, int f1, int *comp_rel);
int altura_abp(PtABP *abp);
int fator_balanceamento_nodo(PtABP *abp);
int fator_balanceamento_abp(PtABP *abp);
void aux_imprime_abp(FILE *resultado, PtABP *print);
void imprime_abp(FILE *resultado, PtABP *print, int f0, int f1);
