#define MAX 50

typedef struct TipoABP
{
    char palavra[MAX];
    int frequencia;
    struct TipoABP *esquerda;
    struct TipoABP *direita;
} PtABP;

PtABP* inicializa_abp();
int vazia_abp(PtABP *abp, int *comp);
int compara(PtABP *abp, char palavra[MAX], int *comp);
int maior(int i, int j, int *comp);
int maior_igual(int i, int j, int *comp);
int menor(int i, int j, int *comp);
int menor_igual(int i, int j, int *comp);
int igual(int i, int j, int *comp);
PtABP* insere_abp(PtABP *abp, char p[], int *comp);
PtABP* insere_abp_freq(PtABP *abp0, PtABP *abp, int *comp);
int conta_abp(PtABP *abp, int *comp);
int aux_frequencia_abp(PtABP *abp, char p[], int *comp);
void frequencia_abp(FILE *saida, PtABP *abp, char p[], int *comp);
void contador_abp(PtABP **abp0, PtABP *abp, int f0, int f1, int *comp);
int altura_abp(PtABP *abp, int *comp);
int fator_balanceamento_nodo(PtABP *abp, int *comp);
int fator_balanceamento_abp(PtABP *abp, int *comp);
void aux_imprime_abp(FILE *resultado, PtABP *abp0, int *comp);
void imprime_abp(FILE *resultado, PtABP *abp0, int f0, int f1, int *comp);
PtABP *destroi_abp(PtABP *abp, int *comp);
