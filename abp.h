typedef struct TipoABP
{
    char palavra;
    struct TipoABP *esquerda;
    struct TipoABP *direita;
} PtABP;

PtABP* inicializa_abp();
PtABP* consulta_abp(PtABP *a, char p);
PtABP* insere_abp(PtABP *a, char p);
int conta_abp(PtABP *a);
void imprime_abp_lista(PtABP *a);
void imprime_abp(PtABP *a, int nv);
