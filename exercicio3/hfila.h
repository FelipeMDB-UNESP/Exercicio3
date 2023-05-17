#ifndef HFILA_H
#define HFILA_H


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

bool isVazia(Fila* fila){
    return fila->primeiro == NULL;
}

void adicionar_na_fila(Fila* fila, Cliente cliente){
    No* novoNo = (No*)malloc(sizeof(No));
    strcpy(novoNo->cliente.nome, cliente.nome);
    novoNo->cliente.tamanho_carrinho = cliente.tamanho_carrinho;
    novoNo->cliente.tipo = cliente.tipo;
    novoNo->cliente.prioridade = cliente.prioridade;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    if (isVazia(fila)) {
        fila->primeiro = novoNo;
        fila->ultimo = novoNo;
    } else {
        novoNo->anterior = fila->ultimo;
        fila->ultimo->proximo = novoNo;
        fila->ultimo = novoNo;
    }
    fila->qtd_nos++;
}

Cliente remover_da_fila(Fila* fila){

    if(isVazia(fila)) {
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
    return cliente;
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

float calcular_tempo_medio_de_servico(Fila* fila){

    float tempo_total = 0;
    No* atual = fila->primeiro;
    while (atual != NULL) {
        tempo_total = tempo_total + atual->cliente.tamanho_carrinho;
    }
    return (tempo_total/fila->qtd_nos);
}

#endif /* HFILA_H */