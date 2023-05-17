
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hcliente.h"
#include "hfila.h"

typedef struct no_prioritario{

    Cliente cliente_prioritario;
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

void adicionar_na_fila_prioritaria(Fila_Prioritaria* fila, Cliente cliente_prioritario){
    NoPrioritario* novoNo = (NoPrioritario*)malloc(sizeof(NoPrioritario));
    strcpy(novoNo->cliente_prioritario.nome, cliente_prioritario.nome);
    novoNo->cliente_prioritario.tipo = cliente_prioritario.tipo;
    novoNo->cliente_prioritario.tamanho_carrinho = cliente_prioritario.tamanho_carrinho;
    novoNo->cliente_prioritario.prioridade = cliente_prioritario.prioridade;
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

/*void remover_da_fila_prioritaria_sem_priorizar(Fila_Prioritaria* fila){

    if(isVazia(fila)) {
        printf("A fila esta vazia. \n");
    }

    NoPrioritario* aux = fila->primeiro;
    Cliente cliente_prioritario = aux->cliente_prioritario;

    fila->primeiro = fila->primeiro->proximo;

    if (fila->primeiro != NULL) {
        fila->primeiro->anterior = NULL;
    } else {
        fila->ultimo = NULL;
    }

    fila->qtd_nos--;
}*/

int encontrar_maior_prioridade(Fila_Prioritaria* fila){

    NoPrioritario* atual = fila->primeiro;
    int maior_prioridade = 0;

    while(atual != NULL) {
        if(atual->cliente_prioritario.prioridade > maior_prioridade){
            maior_prioridade = atual->cliente_prioritario.prioridade;
        }
        atual = atual->proximo;
    }

    return maior_prioridade;
}

Cliente remover_da_fila_elemento_prioritario(Fila_Prioritaria* fila){

    int maior_prioridade = encontrar_maior_prioridade(fila);
    NoPrioritario* atual = fila->primeiro;

    while (atual != NULL) {
        if (atual->cliente_prioritario.prioridade == maior_prioridade) {
            Cliente cliente_removido = atual->cliente_prioritario;
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
            return cliente_removido;
        }
        atual = atual->proximo;
    }

    Cliente cliente_vazio;
    return cliente_vazio;
}

/*int get_tamanho_prioritario(Fila_Prioritaria* fila){

    return fila->qtd_nos;
}*/

void liberar_fila_prioritaria(Fila_Prioritaria* fila) {
    NoPrioritario* atual = fila->primeiro;
    while (atual != NULL) {
        NoPrioritario* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(fila);
}

float calcular_tempo_medio_de_servico_fila_prioritaria(Fila_Prioritaria* fila){

    float tempo_total = 0;
    NoPrioritario* atual = fila->primeiro;
    while (atual != NULL) {
        tempo_total = tempo_total + atual->cliente_prioritario.tamanho_carrinho;
    }
    return (tempo_total/fila->qtd_nos);
}
