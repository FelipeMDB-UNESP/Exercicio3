#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct clienteP{

    char        nome[100];
    char             tipo;
    int  tamanho_carrinho;
    int        prioridade;
} ClienteP;

typedef struct no_prioritario{

    ClienteP cliente_prioritario;
    struct no_prioritario* proximo;
    struct no_prioritario* anterior;
} NoPrioritario;

typedef struct fila_Prioritaria {

    int qtd_nos;
    NoPrioritario*   primeiro;
    NoPrioritario*     ultimo;
} Fila_Prioritaria;

Fila_Prioritaria* criar_fila_prioritaria(){

    Fila_Prioritaria* fila = (Fila_Prioritaria*) malloc(sizeof(Fila_Prioritaria));
    fila->qtd_nos = 0;
    fila->primeiro = NULL;
    fila->ultimo =  NULL;
    return fila;
}

bool isVazia_prioritaria(Fila_Prioritaria* fila){
    return fila->primeiro == NULL;
}

void adicionar_na_fila_prioritaria(Fila_Prioritaria* fila, ClienteP cliente_prioritario){
    NoPrioritario* novoNo = (NoPrioritario*)malloc(sizeof(NoPrioritario));
    strcpy(novoNo->cliente_prioritario.nome, cliente_prioritario.nome);
    novoNo->cliente_prioritario.tipo = cliente_prioritario.tipo;
    novoNo->cliente_prioritario.tamanho_carrinho = cliente_prioritario.tamanho_carrinho;
    novoNo->cliente_prioritario.prioridade = cliente_prioritario.prioridade;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    if (isVazia_prioritaria(fila)) {
        fila->primeiro = novoNo;
        fila->ultimo = novoNo;
    } else {
        novoNo->anterior = fila->ultimo;
        fila->ultimo->proximo = novoNo;
        fila->ultimo = novoNo;
    }
    fila->qtd_nos++;
}

void remover_da_fila_prioritaria(Fila_Prioritaria* fila){

    if(isVazia_prioritaria(fila)) {
        printf("A fila esta vazia. \n");
        return;
    }

    NoPrioritario* aux = fila->primeiro;
    ClienteP cliente_prioritario = aux->cliente_prioritario;

    fila->primeiro = fila->primeiro->proximo;

    if (fila->primeiro != NULL) {
        fila->primeiro->anterior = NULL;
    } else {
        fila->ultimo = NULL;
    }

    fila->qtd_nos--;
}

int encontrar_maior_prioridade(Fila_Prioritaria* fila){

    NoPrioritario* atual = fila->primeiro;
    int prioridade = 0;

    while(atual != NULL) {
        if(atual->cliente_prioritario.prioridade > prioridade){
            prioridade = atual->cliente_prioritario.prioridade;
        }
        atual = atual->proximo;
    }

    return prioridade;
}

void remover_da_fila_elemento_prioritario(Fila_Prioritaria* fila){

    int maior_prioridade = encontrar_maior_prioridade(fila);
    NoPrioritario* atual = fila->primeiro;

    while (atual != NULL) {
        if (atual->cliente_prioritario.prioridade == maior_prioridade) {
            if (atual == fila->primeiro) {
                remover_da_fila(fila);
            } else if (atual == fila->ultimo) {
                fila->ultimo = atual->anterior;
                fila->ultimo->proximo = NULL;
                fila->qtd_nos--;
            } else {
                atual->anterior->proximo = atual->proximo;
                atual->proximo->anterior = atual->anterior;
                fila->qtd_nos--;
            }
            return;
        }
        atual = atual->proximo;
    }
}

int get_tamanho_prioritario(Fila_Prioritaria* fila){

    return fila->qtd_nos;
}

void liberar_fila_prioritaria(Fila_Prioritaria* fila) {
    NoPrioritario* atual = fila->primeiro;
    while (atual != NULL) {
        NoPrioritario* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(fila);
}