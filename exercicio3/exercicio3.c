#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hcliente.h"
#include "hfila.h"
#include "time.h"



int randomizar(int minimo, int maximo)
{
    int num = (rand() %
    (maximo - minimo + 1)) + minimo;
    return num;
}

int main(){


    char lista_de_nomes[19][80] = {
        "Fera Clerical", "Padre Gascoigne",
        "Fera Sedenta de Sangue", "Vigario Amelia",
        "Bruxa de Hemwick", "Sombras de Yharnam",
        "ROM", "O Renascido",
        "Orfao de Kos", "Gherman",
        "Lady Maria da Torre Astral", "Presenca da Lua",
        "Ama-de-leite de Mergo", "Amygydala",
        "Micolash", "Emissario Celestial",
        "Ebrietas, filho do Cosmos", "Martyr Logarius", "Ludwig, o Amaldicoado"
    };
    printf("Bem vindo ao supermercado!\n");

    Fila* caixa_convencional = criar_fila();
    Fila* caixa_rapido = criar_fila();
    Fila* caixa_prioritario = criar_fila();

    int qtd_clientes_prioritarios = randomizar(1,5);
    for(int i = 0; i < qtd_clientes_prioritarios; i++){
        Cliente cliente_prioritario;
        strcpy(cliente_prioritario.nome, lista_de_nomes[randomizar(0,18)]);
        cliente_prioritario.tamanho_carrinho = randomizar(1, 20);
        cliente_prioritario.prioridade = randomizar(0,10);
        cliente_prioritario.tipo = 1;

        adicionar_na_fila(caixa_prioritario, cliente_prioritario);
    }

    bool esta_aberto_caixa_rapido = true;
    bool esta_aberto_caixa_convencional = true;
    int qtd_clientes_normais = randomizar(10, 20);
    for(int i = 0; i < qtd_clientes_normais; i++){
        Cliente cliente_normal;
        strcpy(cliente_normal.nome, lista_de_nomes[randomizar(0,18)]);
        cliente_normal.tamanho_carrinho = randomizar(1, 20);
        cliente_normal.tipo = 0;
        cliente_normal.prioridade = 0;

        
        if(cliente_normal.tamanho_carrinho <= 10 && caixa_rapido->qtd_nos < 7){
            adicionar_na_fila(caixa_rapido, cliente_normal);
        } else if(caixa_convencional->qtd_nos < 5) {
            if(esta_aberto_caixa_rapido == true){
                printf("\nCaixa rapido fechado.\n");
                esta_aberto_caixa_rapido = false;
            }
            adicionar_na_fila(caixa_convencional, cliente_normal);
        } else{
            if(esta_aberto_caixa_convencional == true){
                printf("\nCaixa convencional fechado.\n\n");
                esta_aberto_caixa_convencional = false;
            }
            adicionar_na_fila(caixa_prioritario, cliente_normal);
        }
    }

    float tempo_medio_de_servico_caixa_convencional = calcular_tempo_medio_de_servico(caixa_convencional);
    float tempo_medio_de_servico_caixa_rapido = calcular_tempo_medio_de_servico(caixa_rapido);
    float tempo_medio_de_servico_caixa_prioritario = calcular_tempo_medio_de_servico(caixa_prioritario);
        while(caixa_prioritario->qtd_nos != 0){
            
            Cliente cliente_removido = remover_da_fila_elemento_prioritario(caixa_prioritario);
            printf("Cliente sendo atendido no caixa prioritario...\n");
            printf("Nome: %s\nTamanho do carrinho: %d\n", cliente_removido.nome, cliente_removido.tamanho_carrinho);
            if(cliente_removido.tipo == 1){
                printf("Tipo: prioritário\n");
            }else{printf("Tipo: nao prioritario\n");}
            printf("\nTamanho da fila atual: %d\n", caixa_prioritario->qtd_nos);
            printf("-----------------------------------------------------------------------------------\n\n\n");
        }

        while(caixa_convencional->qtd_nos != 0){
            
            Cliente cliente_removido = remover_da_fila(caixa_convencional);
            printf("Cliente sendo atendido no caixa convencional...\n");
            printf("Nome: %s\nTamanho do carrinho: %d\nTipo: nao prioritario\n", cliente_removido.nome, cliente_removido.tamanho_carrinho);
            printf("\nTamanho da fila atual: %d\n", caixa_convencional->qtd_nos);
            printf("-----------------------------------------------------------------------------------\n\n\n");
        }

        while(caixa_rapido->qtd_nos != 0){
            
            Cliente cliente_removido = remover_da_fila(caixa_rapido);
            printf("Cliente sendo atendido no caixa rapido...\n");
            printf("Nome: %s\nTamanho do carrinho: %d\nTipo: nao prioritario\n", cliente_removido.nome, cliente_removido.tamanho_carrinho);
            printf("\nTamanho da fila atual: %d\n", caixa_rapido->qtd_nos);
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