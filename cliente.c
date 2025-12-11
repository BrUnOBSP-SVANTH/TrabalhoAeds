#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_CLIENTES "clientes.dat"

Cliente clientes[100];
int total_clientes = 0;

void carregar_clientes() {
    FILE *fp = fopen(ARQUIVO_CLIENTES, "rb");
    if (fp != NULL) {
        total_clientes = fread(clientes, sizeof(Cliente), 100, fp);
        fclose(fp);
    }
}

void salvar_clientes() {
    FILE *fp = fopen(ARQUIVO_CLIENTES, "wb");
    if (fp != NULL) {
        fwrite(clientes, sizeof(Cliente), total_clientes, fp);
        fclose(fp);
    }
}

long gerar_codigo_cliente() {
    long max = 0;
    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].codigo > max)
            max = clientes[i].codigo;
    }
    return max + 1;
}

void cadastrar_cliente() {
    Cliente c;
    c.codigo = gerar_codigo_cliente();
    printf("Nome: "); scanf(" %[^\n]", c.nome);
    printf("Endereco: "); scanf(" %[^\n]", c.endereco);
    printf("Telefone: "); scanf(" %[^\n]", c.telefone);
    c.pontosFidelidade = 0;

    clientes[total_clientes++] = c;
    salvar_clientes();
    printf("Cliente cadastrado com sucesso! Codigo: %ld\n", c.codigo);
}

void pesquisar_cliente() {
    char nome[MAX_NOME];
    long codigo;
    int achou = 0;
    printf("Digite o codigo (0 para pesquisar por nome): "); scanf("%ld", &codigo);
    if (codigo != 0) {
        for (int i = 0; i < total_clientes; i++) {
            if (clientes[i].codigo == codigo) {
                printf("Codigo: %ld\nNome: %s\nEndereco: %s\nTelefone: %s\nPontos: %d\n",
                    clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone, clientes[i].pontosFidelidade);
                achou = 1;
                break;
            }
        }
    } else {
        printf("Digite o nome: "); scanf(" %[^\n]", nome);
        for (int i = 0; i < total_clientes; i++) {
            if (strcasecmp(clientes[i].nome, nome) == 0) {
                printf("Codigo: %ld\nNome: %s\nEndereco: %s\nTelefone: %s\nPontos: %d\n",
                    clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone, clientes[i].pontosFidelidade);
                achou = 1;
            }
        }
    }
    if (!achou) printf("Cliente nao encontrado!\n");
}

