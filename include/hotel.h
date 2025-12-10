// ====================================================================
// Trabalho Prático - Algoritmos e Estruturas de Dados I (AED I)
// Pontifícia Universidade Católica de Minas Gerais (PUC Minas)
//
// Hotel Descanso Garantido
//
// Alunos:
// - Bruno da Silva de Paulo
// - João Pedro Bandeira Ribas
// - Gabriel de Sousa Carvalho Ferreira
// ====================================================================

#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para manipulação de datas

// Tamanhos máximos para strings
#define MAX_NOME 100
#define MAX_ENDERECO 150
#define MAX_TELEFONE 15
#define MAX_CARGO 50
#define MAX_STATUS 15 // "ocupado" ou "desocupado"

// Estrutura para representar uma data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// Estrutura para o Quarto
typedef struct {
    int numero; // Chave primária
    int qtd_hospedes;
    float valor_diaria;
    char status[MAX_STATUS]; // "ocupado" ou "desocupado"
} Quarto;

// Estrutura para o Cliente
typedef struct {
    int codigo; // Chave primária
    char nome[MAX_NOME];
    char endereco[MAX_ENDERECO];
    char telefone[MAX_TELEFONE];
} Cliente;

// Estrutura para o Funcionário
typedef struct {
    int codigo; // Chave primária
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    char cargo[MAX_CARGO];
    float salario;
} Funcionario;

// Estrutura para a Estadia
typedef struct {
    int codigo_estadia; // Chave primária
    Data data_entrada;
    Data data_saida;
    int qtd_diarias;
    int codigo_cliente; // Chave estrangeira para Cliente
    int numero_quarto;  // Chave estrangeira para Quarto
} Estadia;

// Protótipos das Funções de Utilidade
int calcular_dias(Data d1, Data d2);
int validar_data(Data d);
void exibir_menu();
time_t data_to_time_t(Data d);
int quarto_ocupado_no_periodo(int numero_quarto, Data entrada, Data saida);

// Protótipos das Funções de Manipulação de Arquivos
void inicializar_arquivos();
int buscar_proximo_codigo(const char *nome_arquivo);
Cliente *buscar_cliente_por_codigo(int codigo);
Quarto *buscar_quarto_por_numero(int numero);
int atualizar_quarto(Quarto q);
Estadia *buscar_estadia_por_codigo(int codigo);
int atualizar_estadia(Estadia e);
Funcionario *buscar_funcionario_por_codigo(int codigo);

// Protótipos das Funções de Cadastro (Sprint 1)
void cadastrar_cliente();
void cadastrar_funcionario();
void cadastrar_quarto();
void cadastrar_estadia();

// Protótipos das Funções de Operação (Sprint 2)
void dar_baixa_estadia();
void pesquisar_cliente_ou_funcionario();
void mostrar_estadias_cliente();
void calcular_pontos_fidelidade();

#endif // HOTEL_H
