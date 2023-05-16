#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hcliente.h"
#include "hfila_prioritaria.h"
#include "hfila.h"

int main(){

    int teclado = -1;
    printf("Bem vindo ao supermercado!");
    printf("nOBS: caso o cliente NÃO possua prioridade, atribua o valor -1 ao campo prioridade\n");
    Fila* caixa_convencional = criar_fila();
    Fila* caixa_rapido = criar_fila();
    Fila_Prioritaria* caixa_prioritario = criar_fila_prioritaria();

    do {
        printf("Digite:\n0-Sair\n1-Insira um cliente\n2-Atender Filas\n");
        scanf(" %d", &teclado);

        if(teclado == 1){
            int prioridade;
            printf("Qual a prioridade do cliente?\n");
            scanf(" %d", &prioridade);
            if(prioridade != -1){
                ClienteP cliente_prioritario;

                fflush(stdin);
                printf("Digite o nome do cliente: \n");
                fgets(cliente_prioritario.nome, sizeof(cliente_prioritario.nome), stdin);
                scanf(" %[^\n]", &cliente_prioritario.nome);

                printf("Digite o tipo do cliente: \n");
                scanf(" %c", &cliente_prioritario.tipo);

                printf("Digite o tamanho do carrinho do cliente: \n");
                scanf(" %d", &cliente_prioritario.tamanho_carrinho);

            }else{
                Cliente cliente;
                printf("Digite o nome do cliente: \n");
                fgets(cliente.nome, sizeof(cliente.nome), stdin);
                scanf(" %[^\n]", &cliente.nome);

                printf("Digite o tipo do cliente: \n");
                scanf(" %c", &cliente.tipo);

                printf("Digite o tamanho do carrinho do cliente: \n");
                scanf(" %d", &cliente.tamanho_carrinho);
            }

        }



    } while (teclado != 0);

    printf("Mercado encerrado.\n");

    return 0;

}