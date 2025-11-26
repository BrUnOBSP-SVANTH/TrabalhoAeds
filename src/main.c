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

#include "../include/hotel.h"

int main() {
    int opcao;

    // Inicializa os arquivos de dados se não existirem
    inicializar_arquivos();

    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de falha na leitura
            while (getchar() != '\n');
            opcao = -1; // Opção inválida
        }

        switch (opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                cadastrar_funcionario();
                break;
            case 3:
                cadastrar_quarto();
                break;
            case 4:
                cadastrar_estadia();
                break;
            case 5:
                dar_baixa_estadia();
                break;
            case 6:
                pesquisar_cliente_ou_funcionario();
                break;
            case 7:
                mostrar_estadias_cliente();
                break;
            case 8:
                calcular_pontos_fidelidade();
                break;
            case 0:
                printf("\nSaindo do sistema. Até mais!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            // Espera por um ENTER antes de mostrar o menu novamente
            while (getchar() != '\n');
            getchar();
        }
    } while (opcao != 0);

    return 0;
}
