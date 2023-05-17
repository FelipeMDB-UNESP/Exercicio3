#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct cliente{

    char        nome[100];
    int              tipo;
    int  tamanho_carrinho;
    int        prioridade;
} Cliente;

#endif /* CLIENTE_H */