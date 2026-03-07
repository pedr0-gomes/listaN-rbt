#include <stdlib.h>
#include "rbt.h"

/* -- Sentinela NIL -- */
struct NO NIL_NODE = {0,NULL,NULL,BLACK};
ArvRB NIL = &NIL_NODE;

/* -- Criar Árvore -- */
ArvRB* criar_ArvRB(void)
{
    ArvRB *raiz = malloc(sizeof(ArvRB));
    if (raiz == NULL) return NULL;
    *raiz = NIL;
    return raiz;
}

static void destroi_recursive(ArvRB no)
{
    if (no == NULL) return;
    destroi_recursive(no->esq);
    destroi_recursive(no->dir);
    free(no);
}

void destroi_ArvRB(ArvRB *raiz)
{
    if (raiz == NULL) return;
    destroi_recursive(*raiz);
    free(raiz);
}

int busca_ArvRB (ArvRB *raiz,int valor)
{
    if (raiz == NULL) return 0;
    if (*raiz == NIL) return 0;
    if ((*raiz)->info == valor) return 1;
    if ((*raiz)->info < valor) return busca_ArvRB(&(*raiz)->esq,valor);
    return busca_ArvRB(&(*raiz)->dir,valor);
}

void colocar_cor(ArvRB no,int cor)
{
    if (no == NULL) return;
    no->cor = cor;
}

void trocar_cor(ArvRB no)
{
    if (no == NULL) return;
    no->cor = !no->cor;
    no->esq->cor = !no->esq->cor;
    no->dir->cor = !no->dir->cor; 
}