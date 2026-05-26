#include <stdio.h>
#include <stdlib.h>
#include "minhabib.h"


void imprimir_nos_internos(No* raiz){
    if(raiz == NULL){ 
    return;
    }
    
    if(raiz->esq != NULL || raiz->dir != NULL){
        printf("%d ", raiz->valor);
    }

    imprimir_nos_internos(raiz->esq);
    imprimir_nos_internos(raiz->dir);
}

void imprimir_folhas(No* raiz){
    if(raiz == NULL)
    return;

    if(raiz->esq == NULL && raiz->dir == NULL){
        printf("%d ", raiz->valor);
    }

    imprimir_folhas(raiz->esq);
    imprimir_folhas(raiz->dir);
}

void imprimir_niveis(No* raiz, int nivel_atual){
    if(raiz == NULL) 
    return;

    printf("Nivel %d: %d\n", nivel_atual, raiz->valor);

    imprimir_niveis(raiz->esq, nivel_atual+ 1);
    imprimir_niveis(raiz->dir, nivel_atual+ 1);
}

int calcular_altura(No* no){
    if(no == NULL){ 
    return -1;
    }
    int esq = calcular_altura(no->esq);
    int dir = calcular_altura(no->dir);

        if (esq > dir) {
        return esq + 1;
    } else {
        return dir + 1;
    }
}

int calcular_profundidade(No* raiz, int valor, int profundidade_atual){
    if(raiz == NULL) return -1;

    if(raiz->valor == valor) return profundidade_atual;

    int esq = calcular_profundidade(raiz->esq, valor, profundidade_atual + 1);
    if(esq != -1){
    return esq;
    }
    return calcular_profundidade(raiz->dir, valor, profundidade_atual + 1);
}

int imprimir_ancestrais(No* raiz, int valor){
    if(raiz == NULL) return 0;

    if(raiz->valor == valor) return 1;

    if(imprimir_ancestrais(raiz->esq, valor) ||
       imprimir_ancestrais(raiz->dir, valor)){
        printf("%d ", raiz->valor);
        return 1;
    }

    return 0;
}

void imprimir_descendentes(No* no){
    if(no == NULL) return;

    if(no->esq != NULL){
        printf("%d ", no->esq->valor);
        imprimir_descendentes(no->esq);
    }

    if(no->dir != NULL){
        printf("%d ", no->dir->valor);
        imprimir_descendentes(no->dir);
    }
}

void analisar_arvore(No* raiz, int valorBusca){

    if(raiz == NULL){
        printf("Arvore vazia.\n");
        return;
    }

    printf("\n========== DIAGNOSTICO GERAL ==========\n");

    printf("Raiz: %d\n", raiz->valor);

    printf("Nos internos: ");
    imprimir_nos_internos(raiz);
    printf("\n");

    printf("Folhas: ");
    imprimir_folhas(raiz);
    printf("\n");

    printf("\nExibicao por niveis:\n");
    imprimir_niveis(raiz, 0);

    
    No* atual = raiz;

    while(atual != NULL && atual->valor != valorBusca){
        if(valorBusca < atual->valor){
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if(atual == NULL){
        printf("\n========================================");
        printf("\nERRO: Valor %d nao encontrado na arvore.", valorBusca);
        printf("\n========================================\n");
        return;
    }

  
    printf("\n========================================");
    printf("\nDIAGNOSTICO ESPECIFICO: NO %d", valorBusca);
    printf("\n========================================\n");

    // Grau
    int grau = 0;
    if(atual->esq != NULL) grau++;
    if(atual->dir != NULL) grau++;
    printf("Grau do no: %d\n", grau);

    // Ancestrais
    printf("Ancestrais: ");
    imprimir_ancestrais(raiz, valorBusca);
    printf("\n");

    // Descendentes
    printf("Descendentes: ");
    imprimir_descendentes(atual);
    printf("\n");

    // Altura e profundidade
    printf("Altura do no: %d\n", calcular_altura(atual));
    printf("Profundidade do no: %d\n", calcular_profundidade(raiz, valorBusca, 0));

    //Subarvore 
    printf("\nSub-arvore a partir do no %d:\n", valorBusca);
    printf("----------------------------------------\n");
    imprimir_niveis(atual, 0);
    printf("----------------------------------------\n");
}