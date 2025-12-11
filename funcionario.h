#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#define MAX_NOME 50
#define MAX_TEL 15
#define MAX_CARGO 30

typedef struct {
    long codigo;
    char nome[MAX_NOME];
    char telefone[MAX_TEL];
    char cargo[MAX_CARGO];
    float salario;
} Funcionario;

void cadastrar_funcionario();
void pesquisar_funcionario();
long gerar_codigo_funcionario();
void carregar_funcionarios();
void salvar_funcionarios();

#endif
