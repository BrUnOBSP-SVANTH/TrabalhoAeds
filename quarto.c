#include "quarto.h"
#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO_QUARTOS "quartos.dat"

Quarto quartos[MAX_QUARTOS];
int total_quartos = 0;

// ========================================================
// CARREGAR QUARTOS
// ========================================================
void carregar_quartos() {
    FILE *fp = fopen(ARQUIVO_QUARTOS, "rb");
    if (fp != NULL) {
        total_quartos = fread(quartos, sizeof(Quarto), MAX_QUARTOS, fp);
        fclose(fp);
    }
}

// ========================================================
// SALVAR QUARTOS
// ========================================================
void salvar_quartos() {
    FILE *fp = fopen(ARQUIVO_QUARTOS, "wb");
    if (fp != NULL) {
        fwrite(quartos, sizeof(Quarto), total_quartos, fp);
        fclose(fp);
    }
}

// ========================================================
// CADASTRAR QUARTO
// ========================================================
void cadastrar_quarto() {
    Quarto q;

    printf("Numero do quarto: ");
    scanf("%d", &q.numero);

    // Verifica se o quarto já existe
    for (int i = 0; i < total_quartos; i++) {
        if (quartos[i].numero == q.numero) {
            printf("ERRO: Esse quarto ja existe!\n");
            return;
        }
    }

    printf("Capacidade (hospedes): ");
    scanf("%d", &q.quantidadeHospedes);

    printf("Valor da diaria: ");
    scanf("%f", &q.valorDiaria);

    q.status = 0;   // sempre começa desocupado

    quartos[total_quartos++] = q;
    salvar_quartos();

    printf("\nQuarto cadastrado com sucesso!\n");
}

// ========================================================
// LISTAR QUARTOS
// ========================================================
void listar_quartos() {
    if (total_quartos == 0) {
        printf("Nenhum quarto cadastrado.\n");
        return;
    }

    printf("\n==== LISTA DE QUARTOS ====\n");
    for (int i = 0; i < total_quartos; i++) {
        printf("Numero: %d | Capacidade: %d | Valor: R$ %.2f | Status: %s\n",
               quartos[i].numero,
               quartos[i].quantidadeHospedes,
               quartos[i].valorDiaria,
               quartos[i].status ? "OCUPADO" : "DESOCUPADO");
    }
}

// ========================================================
// VERIFICA SE EXISTE QUARTO DISPONÍVEL
// Retorna o INDICE do quarto disponível ou -1
// ========================================================
int verificar_quarto_disponivel(int qtd) {
    for (int i = 0; i < total_quartos; i++) {
        if (quartos[i].status == 0 && quartos[i].quantidadeHospedes >= qtd) {
            return i;
        }
    }
    return -1;
}

// ========================================================
// ATUALIZAR STATUS DO QUARTO
// (novoStatus = 0
