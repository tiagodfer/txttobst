typedef struct TipoABP
{
    char palavra[50];
    int frequencia;
    struct TipoABP *esquerda;
    struct TipoABP *direita;
} PtABP;

PtABP* inicializa_abp();
PtABP* consulta_abp(PtABP *abp, char p[]);
PtABP* insere_abp(PtABP *abp, char p[]);
int conta_abp(PtABP *abp);
void imprime_abp_lista(PtABP *abp);
void imprime_abp(PtABP *abp, int nv);
