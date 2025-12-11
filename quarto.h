#ifndef QUARTO_H
#define QUARTO_H

#define MAX_QUARTOS 100

typedef struct {
    int numero;                  // Número identificador do quarto
    int quantidadeHospedes;      // Capacidade máxima de hóspedes
    float valorDiaria;           // Valor da diária
    int status;                  // 0 = desocupado, 1 = ocupado
} Quarto;

// Variáveis globais (declaradas aqui como extern e definidas em quarto.c)
extern Quarto quartos[MAX_QUARTOS];
extern int total_quartos;

// Protótipos das funções
void carregar_quartos();
void salvar_quartos();
void cadastrar_quarto();
void listar_quartos();
int verificar_quarto_disponivel(int qtd);
void atualizar_status_quarto(int numero, int novoStatus);

#endif // QUARTO_H
