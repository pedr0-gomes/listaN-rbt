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