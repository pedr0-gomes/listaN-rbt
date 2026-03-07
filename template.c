#include <stdio.h>
#include "rbt.h"

int main(void) {
    ArvRB *arvore = criar_ArvRB();
    if (arvore == NULL) {
        printf("Erro ao criar arvore.\n");
        return 1;
    }

    // testes do exercicio aqui

    destroi_ArvRB(arvore);
    return 0;
}