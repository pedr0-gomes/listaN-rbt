#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

static int is_red(ArvRB no)
{
    return (no != NIL) && (no->cor == RED);
}

static ArvRB insere_rec(ArvRB no, int valor, int *ok)
{
    if (no == NIL)
    {
        ArvRB novo = malloc(sizeof(struct NO));
        if (novo == NULL)
        {
            *ok = 0;
            return NIL;
        }
        novo->info = valor;
        novo->cor = RED;
        novo->esq = NIL;
        novo->dir = NIL;
        return novo;
    }

    if (valor < no->info)
    {
        ArvRB filho = insere_rec(no->esq, valor, ok);
        if (!*ok) return no;
        no->esq = filho;
    }
    else if (valor > no->info)
    {
        ArvRB filho = insere_rec(no->dir, valor, ok);
        if (!*ok) return no;
        no->dir = filho;
    }
    else
    {
        return no;
    }

    if (is_red(no->dir) && is_red(no->dir->dir))
    {
        no = rotacao_esq(no);
    }
    if (is_red(no->esq) && !is_red(no->dir))
    {
        no = rotacao_dir(no);
    }
    if (is_red(no->esq) && is_red(no->dir))
    {
        trocar_cor(no);
    }

    return no;
}

int insere_ArvRB(ArvRB *raiz, int valor)
{
    int ok = 1;

    if (raiz == NULL) return 0;
    *raiz = insere_rec(*raiz, valor, &ok);
    if (!ok) return 0;
    if (*raiz != NIL) (*raiz)->cor = BLACK;
    return 1;
}

static int contar_nos(ArvRB no)
{
    if (no == NIL) return 0;
    return 1 + contar_nos(no->esq) + contar_nos(no->dir);
}

static int valida_bst(ArvRB no, int min, int max)
{
    if (no == NIL) return 1;
    if (no->info <= min || no->info >= max) return 0;
    return valida_bst(no->esq, min, no->info) && valida_bst(no->dir, no->info, max);
}

static int valida_sem_vermelho_consecutivo(ArvRB no)
{
    if (no == NIL) return 1;
    if (is_red(no) && (is_red(no->esq) || is_red(no->dir))) return 0;
    return valida_sem_vermelho_consecutivo(no->esq) && valida_sem_vermelho_consecutivo(no->dir);
}

static int black_height(ArvRB no)
{
    int esq;
    int dir;

    if (no == NIL) return 1;

    esq = black_height(no->esq);
    dir = black_height(no->dir);
    if (esq == 0 || dir == 0 || esq != dir) return 0;

    return esq + (no->cor == BLACK ? 1 : 0);
}

static int valida_direitista(ArvRB no)
{
    if (no == NIL) return 1;
    if (is_red(no->esq)) return 0;
    return valida_direitista(no->esq) && valida_direitista(no->dir);
}

static int valida_rbt(ArvRB raiz)
{
    if (raiz == NIL) return 1;
    if (raiz->cor != BLACK) return 0;
    if (!valida_bst(raiz, INT_MIN, INT_MAX)) return 0;
    if (!valida_sem_vermelho_consecutivo(raiz)) return 0;
    if (black_height(raiz) == 0) return 0;
    if (!valida_direitista(raiz)) return 0;
    return 1;
}

static int testar_sequencia(ArvRB *arvore, const int *valores, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!insere_ArvRB(arvore, valores[i])) return 0;
        if (!valida_rbt(*arvore)) return 0;
    }
    return 1;
}

int main(void)
{
    ArvRB *arvore = criar_ArvRB();
    ArvRB *vazia = criar_ArvRB();

    int seq_simples[] = {10, 20, 30, 15, 5};
    int seq_crescente[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int seq_decrescente[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int seq_mista[] = {40, 10, 60, 50, 70, 20, 30, 65, 55};

    int antes;
    int depois;

    if (arvore == NULL || vazia == NULL)
    {
        printf("ERRO: falha ao criar arvore.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    if (!testar_sequencia(arvore, seq_simples, (int)(sizeof(seq_simples) / sizeof(seq_simples[0]))))
    {
        printf("ERRO: sequencia simples invalida.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    if (!testar_sequencia(arvore, seq_crescente, (int)(sizeof(seq_crescente) / sizeof(seq_crescente[0]))))
    {
        printf("ERRO: sequencia crescente invalida.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    if (!testar_sequencia(arvore, seq_decrescente, (int)(sizeof(seq_decrescente) / sizeof(seq_decrescente[0]))))
    {
        printf("ERRO: sequencia decrescente invalida.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    if (!testar_sequencia(arvore, seq_mista, (int)(sizeof(seq_mista) / sizeof(seq_mista[0]))))
    {
        printf("ERRO: sequencia mista invalida.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    antes = contar_nos(*arvore);
    if (!insere_ArvRB(arvore, 30))
    {
        printf("ERRO: insercao de duplicata falhou.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }
    depois = contar_nos(*arvore);
    if (antes != depois)
    {
        printf("ERRO: duplicata alterou quantidade de nos.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    if (!busca_ArvRB(arvore, 65) || busca_ArvRB(arvore, 999))
    {
        printf("ERRO: busca inconsistente.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    if (!valida_rbt(*arvore))
    {
        printf("ERRO: arvore final invalida.\n");
        destroi_ArvRB(arvore);
        destroi_ArvRB(vazia);
        return 1;
    }

    destroi_ArvRB(vazia);
    destroi_ArvRB(arvore);

    printf("OK: insercao, propriedades RBT direitista, busca e destruicao validadas.\n");
    return 0;
}
