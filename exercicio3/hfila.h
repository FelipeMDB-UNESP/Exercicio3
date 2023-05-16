#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hcliente.h"

typedef struct no{

    Cliente cliente;
    struct no* proximo;
    struct no* anterior;
} No;

typedef struct fila {

    int qtd_nos;
    No*   primeiro;
    No*     ultimo;
} Fila;

Fila* criar_fila(){

    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->qtd_nos = 0;
    fila->primeiro = NULL;
    fila->ultimo =  NULL;
    return fila;
}

bool isVaziaFila(Fila* fila){
    return fila->primeiro == NULL;
}

void adicionar_na_fila(Fila* fila, Cliente cliente){
    No* novoNo = (No*)malloc(sizeof(No));
    strcpy(novoNo->cliente.nome, cliente.nome);
    novoNo->cliente.tamanho_carrinho = cliente.tamanho_carrinho;
    novoNo->cliente.tipo = cliente.tipo;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    if (isVaziaFila(fila)) {
        fila->primeiro = novoNo;
        fila->ultimo = novoNo;
    } else {
        novoNo->anterior = fila->ultimo;
        fila->ultimo->proximo = novoNo;
        fila->ultimo = novoNo;
    }
    fila->qtd_nos++;
}

void remover_da_fila(Fila* fila){

    if(isVaziaFila(fila)) {
        printf("A fila esta vazia. \n");
    }

    No* aux = fila->primeiro;
    Cliente cliente = aux->cliente;

    fila->primeiro = fila->primeiro->proximo;

    if (fila->primeiro != NULL) {
        fila->primeiro->anterior = NULL;
    } else {
        fila->ultimo = NULL;
    }

    free(aux);
    fila->qtd_nos--;
}

int get_tamanho(Fila* fila){

    return fila->qtd_nos;
}

void liberar_fila(Fila* fila) {
    No* atual = fila->primeiro;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(fila);
}