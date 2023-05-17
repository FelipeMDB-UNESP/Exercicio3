#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hcliente.h"
#include "hfila_prioritaria.h"
#include "hfila.h"
#include "time.h"



int randomizar(int minimo, int maximo)
{
    int num = (rand() %
    (maximo - minimo + 1)) + minimo;
    return num;
}

int main(){


    char lista_de_nomes[10][50] = {"Fera Clerica", "Padre Gascoigne", "Fera Sedenta de Sangue", "Vigario Amelia", "Bruxa de Hemwick", "Sombras de Yharnam", "ROM", "O Renascido", "Orfao de Kos", "Gherman"};
    printf("Bem vindo ao supermercado!\n");

    Fila* caixa_convencional = criar_fila();
    Fila* caixa_rapido = criar_fila();
    Fila_Prioritaria* caixa_prioritario = criar_fila_prioritaria();

    int qtd_clientes_prioritarios = randomizar(1,5);
    int qtd_clientes_normais = randomizar(10, 20);

    for(int i = 0; i < qtd_clientes_prioritarios; i++){
        Cliente cliente_prioritario;
        strcmp(cliente_prioritario.nome, lista_de_nomes[randomizar(0,9)]);
        cliente_prioritario.tamanho_carrinho = randomizar(3, 20);
        cliente_prioritario.prioridade = randomizar(0,10);
        cliente_prioritario.tipo = 1;

        adicionar_na_fila(caixa_prioritario, cliente_prioritario);
    }


    bool esta_aberto_caixa_convencional = true;
    bool esta_aberto_caixa_rapido = true;
    for(int i = 0; i < qtd_clientes_normais; i++){
        Cliente cliente_normal;
        strcmp(cliente_normal.nome, lista_de_nomes[randomizar(0,9)]);
        cliente_normal.tamanho_carrinho = randomizar(3, 20);
        cliente_normal.tipo = 0;

        
        if(cliente_normal.tamanho_carrinho <= 10 && caixa_convencional->qtd_nos < 5){
            adicionar_na_fila(caixa_rapido, cliente_normal);
        } else if(caixa_rapido->qtd_nos < 7) {
            if(esta_aberto_caixa_convencional){
                printf("\n\n\nCaixa convencional fechado\n\n\n");
                esta_aberto_caixa_convencional = false;
            }
            adicionar_na_fila(caixa_convencional, cliente_normal);
        }else{
            if(esta_aberto_caixa_rapido){
                printf("\n\n\nCaixa rapido fechado\n\n\n");
                esta_aberto_caixa_rapido = false;
            }
            adicionar_na_fila_prioritaria(caixa_prioritario, cliente_normal);
        }
    }

    float tempo_medio_de_servico_caixa_convencional = calcular_tempo_medio_de_servico(caixa_convencional);
    float tempo_medio_de_servico_caixa_rapido = calcular_tempo_medio_de_servico(caixa_rapido);
    float tempo_medio_de_servico_caixa_prioritario = calcular_tempo_medio_de_servico_fila_prioritaria(caixa_prioritario);

        while(caixa_prioritario->qtd_nos != 0){
            
            Cliente cliente_removido = remover_da_fila_elemento_prioritario(caixa_prioritario);
            printf("Cliente sendo atendido no caixa prioritario...\n");
            printf("Nome: %s\nTamanho do carrinho: %d\n", cliente_removido.nome, cliente_removido.tamanho_carrinho);
            if(cliente_removido.tipo == 1){
                printf("Tipo: prioritário\n");
            }else{printf("Tipo: nao prioritario\n");}
            printf("Tamanho da fila atual: %d\n", caixa_prioritario->qtd_nos);
            printf("-----------------------------------------------------------------------------------\n\n\n");
        }

        while(caixa_convencional->qtd_nos != 0){
            
            Cliente cliente_removido = remover_da_fila(caixa_convencional);
            printf("Cliente sendo atendido no caixa convencional...\n");
            printf("Nome: %s\nTamanho do carrinho: %d\nTipo: nao prioritario\n", cliente_removido.nome, cliente_removido.tamanho_carrinho);
            printf("Tamanho da fila atual: %d\n", caixa_convencional->qtd_nos);
            printf("-----------------------------------------------------------------------------------\n\n\n");
        }

        while(caixa_rapido->qtd_nos != 0){
            
            Cliente cliente_removido = remover_da_fila(caixa_rapido);
            printf("Cliente sendo atendido no caixa rapido...\n");
            printf("Nome: %s\nTamanho do carrinho: %d\nTipo: nao prioritario\n", cliente_removido.nome, cliente_removido.tamanho_carrinho);
            printf("Tamanho da fila atual: %d\n", caixa_rapido->qtd_nos);
            printf("-----------------------------------------------------------------------------------\n\n\n");
        }


    /*
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

        adicionar_na_fila_prioritaria(caixa_prioritario, cliente_prioritario);

    }else{
        Cliente cliente;
        printf("Digite o nome do cliente: \n");
        fgets(cliente.nome, sizeof(cliente.nome), stdin);
        scanf(" %[^\n]", &cliente.nome);

        printf("Digite o tipo do cliente: \n");
        scanf(" %c", &cliente.tipo);

        printf("Digite o tamanho do carrinho do cliente: \n");
        scanf(" %d", &cliente.tamanho_carrinho);

        if(cliente.tamanho_carrinho <= 10 && caixa_convencional->qtd_nos < 5){
            adicionar_na_fila(caixa_rapido, cliente);
        } else if(caixa_rapido->qtd_nos < 7) {
            printf("Caixa convencional fechado\n");
            adicionar_na_fila(caixa_convencional, cliente);
        }else{
            printf("Caixa rapido fechado");
            adicionar_na_fila(caixa_prioritario, cliente);
        }
    }*/

    
    printf("Tempo medio de servico do caixa prioritario: %.2f\n", tempo_medio_de_servico_caixa_prioritario);
    printf("Tempo medio de servico do caixa convencional: %.2f\n", tempo_medio_de_servico_caixa_convencional);
    printf("Tempo medio de servico do caixa rapido: %.2f\n", tempo_medio_de_servico_caixa_rapido);

    printf("Mercado encerrado.\n");

    return 0;

}