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
int conta_abp(PtABP *abp);
int aux_frequencia_abp(PtABP *abp, char p[], int *comp_rel);
void frequencia_abp(FILE *saida, PtABP *abp, char p[], int *comp_rel);
void aux_contador_abp(FILE *saida, PtABP *abp, int f, int *comp_rel);
void contador_abp(FILE *saida, PtABP *abp, int f0, int f1, int *comp_rel);
int altura_abp(PtABP *abp);
int fator_balanceamento_nodo(PtABP *abp);
int fator_balanceamento_abp(PtABP *abp);
