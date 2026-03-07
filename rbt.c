#include <stdlib.h>
#include "rbt.h"

/* -- Sentinela NIL -- */
struct NO NIL_NODE = {0, &NIL_NODE, &NIL_NODE, BLACK};
ArvRB NIL = &NIL_NODE;

/* -- Criar Arvore -- */
ArvRB* criar_ArvRB(void)
{
    ArvRB *raiz = malloc(sizeof(ArvRB));
    if (raiz == NULL) return NULL;
    *raiz = NIL;
    return raiz;
}

static void destroi_recursive(ArvRB no)
{
    if (no == NULL || no == NIL) return;
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
    if (valor < (*raiz)->info) return busca_ArvRB(&(*raiz)->esq,valor);
    return busca_ArvRB(&(*raiz)->dir,valor);
}

void colocar_cor(ArvRB no,int cor)
{
    if (no == NULL || no == NIL) return;
    no->cor = cor;
}

void trocar_cor(ArvRB no)
{
    if (no == NULL || no == NIL) return;
    no->cor = !no->cor;
    if (no->esq != NIL) no->esq->cor = !no->esq->cor;
    if (no->dir != NIL) no->dir->cor = !no->dir->cor;
}

ArvRB rotacao_esq(ArvRB x)
{
    ArvRB y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    y->cor = x->cor;
    x->cor = RED;
    return y;
}

ArvRB rotacao_dir(ArvRB x)
{
    ArvRB y = x->esq;
    x->esq = y->dir;
    y->dir = x;
    y->cor = x->cor;
    x->cor = RED;
    return y;
}
