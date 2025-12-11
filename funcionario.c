#include "funcionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQUIVO_FUNCIONARIOS "funcionarios.dat"

Funcionario funcionarios[100];
int total_funcionarios = 0;


int stricmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = tolower(*s1);
        char c2 = tolower(*s2);

        if (c1 != c2)
            return c1 - c2;

        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}

// ----------------------------------------------------
void carregar_funcionarios() {
    FILE *fp = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (fp != NULL) {
        total_funcionarios = fread(funcionarios, sizeof(Funcionario), 100, fp);
        fclose(fp);
    } else {
        total_funcionarios = 0;
    }
}

// ----------------------------------------------------
void salvar_funcionarios() {
    FILE *fp = fopen(ARQUIVO_FUNCIONARIOS, "wb");
    if (fp != NULL) {
        fwrite(funcionarios, sizeof(Funcionario), total_funcionarios, fp);
        fclose(fp);
    }
}

// ----------------------------------------------------
long gerar_codigo_funcionario() {
    long max = 0;
    for (int i = 0; i < total_funcionarios; i++) {
        if (funcionarios[i].codigo > max)
            max = funcionarios[i].codigo;
    }
    return max + 1;
}

// ----------------------------------------------------
void cadastrar_funcionario() {
    if (total_funcionarios >= 100) {
        printf("Limite de funcionarios atingido!\n");
        return;
    }

    Funcionario f;
    f.codigo = gerar_codigo_funcionario();

    printf("Nome: ");
    fgets(f.nome, MAX_NOME, stdin);
    f.nome[strcspn(f.nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(f.telefone, MAX_TEL, stdin);
    f.telefone[strcspn(f.telefone, "\n")] = '\0';

    printf("Cargo: ");
    fgets(f.cargo, MAX_CARGO, stdin);
    f.cargo[strcspn(f.cargo, "\n")] = '\0';

    printf("Salario: ");
    scanf("%f", &f.salario);
    getchar(); // limpa o ENTER do buffer

    funcionarios[total_funcionarios++] = f;
    salvar_funcionarios();

    printf("\nFuncionario cadastrado com sucesso!\nCodigo: %ld\n", f.codigo);
}

// ----------------------------------------------------
void pesquisar_funcionario() {
    long codigo;
    char nomeBusca[MAX_NOME];
    int achou = 0;

    printf("Digite o codigo do funcionario (0 para buscar por nome): ");
    scanf("%ld", &codigo);
    getchar(); // limpar buffer

    if (codigo != 0) {
        for (int i = 0; i < total_funcionarios; i++) {
            if (funcionarios[i].codigo == codigo) {
                printf("\n--- Funcionario encontrado ---\n");
                printf("Codigo: %ld\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n",
                       funcionarios[i].codigo,
                       funcionarios[i].nome,
                       funcionarios[i].telefone,
                       funcionarios[i].cargo,
                       funcionarios[i].salario);
                achou = 1;
                break;
            }
        }
    } else {
        printf("Digite o nome: ");
        fgets(nomeBusca, MAX_NOME, stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        for (int i = 0; i < total_funcionarios; i++) {
            if (stricmp_custom(funcionarios[i].nome, nomeBusca) == 0) {
                printf("\n--- Funcionario encontrado ---\n");
                printf("Codigo: %ld\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n",
                       funcionarios[i].codigo,
                       funcionarios[i].nome,
                       funcionarios[i].telefone,
                       funcionarios[i].cargo,
                       funcionarios[i].salario);
                achou = 1;
            }
        }
    }

    if (!achou)
        printf("Funcionario nao encontrado!\n");
}
