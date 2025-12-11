#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_NOME 50
#define MAX_END 100
#define MAX_TEL 15

typedef struct {
    long codigo;
    char nome[MAX_NOME];
    char endereco[MAX_END];
    char telefone[MAX_TEL];
    int pontosFidelidade;
} Cliente;

void cadastrar_cliente();
void pesquisar_cliente();
long gerar_codigo_cliente();
int contar_clientes();
void carregar_clientes();
void salvar_clientes();

#endif

