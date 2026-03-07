#ifndef RBT_H
#define RBT_H

/*
TAD - Árvore Rubro-Negra
Estrutura: nó sentinela NIL (externo, compartilhado)
Autoria: Pedro Gomes
*/

/* -- Constantes de cor --*/
#define RED 1
#define BLACK 0

/* -- Estrutura do nó -- */
struct NO
{
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
};

/* -- Tipo exportado -- */
typedef struct NO* ArvRB;

/* --- Nó sentinela NIL (declarado no .c, acessível via extern) --- */
extern struct NO NIL_NODE;
extern ArvRB     NIL;

ArvRB* criar_ArvRB (void);
void destroi_ArvRB (ArvRB *raiz);
int busca_ArvRB (ArvRB *raiz,int valor);

void colocar_cor (ArvRB no,int cor);
void trocar_cor (ArvRB no);
ArvRB rotacao_esq (ArvRB x);
ArvRB rotacao_dir (ArvRB x);

#endif