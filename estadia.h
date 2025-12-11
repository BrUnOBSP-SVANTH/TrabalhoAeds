#ifndef ESTADIA_H
#define ESTADIA_H

#include "quarto.h"
#include "cliente.h"

#define MAX_ESTADIAS 100

typedef struct {
    long codigoEstadia;
    long codigoCliente;
    int numeroQuarto;
    int qtdDiarias;
    char dataEntrada[11]; // DD/MM/AAAA
    char dataSaida[11];   // DD/MM/AAAA
} Estadia;

// ===============================================
//     FUNÇÕES DE ARQUIVO
// ===============================================
void carregar_estadias();
void salvar_estadias();

// ===============================================
//     FUNÇÕES DE CÓDIGO E CÁLCULOS
// ===============================================
long gerar_codigo_estadia();
int calcular_diarias(const char *entrada, const char *saida);

// ===============================================
//     FUNÇÕES DE VERIFICAÇÃO
// ===============================================
int verificar_quarto_disponivel_com_datas(int qtd, const char *entrada, const char *saida);

// ===============================================
//     FUNÇÕES DE OPERAÇÃO
// ===============================================
void cadastrar_estadia();
void dar_baixa_estadia();
void listar_estadias_cliente();

#endif
