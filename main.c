#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"

// Variáveis globais dos módulos
extern Cliente clientes[100];
extern int total_clientes;

extern Funcionario funcionarios[100];
extern int total_funcionarios;

extern Quarto quartos[100];
extern int total_quartos;

extern Estadia estadias[100];
extern int total_estadias;

// Função para carregar todos os dados
void carregar_tudo() {
    carregar_clientes();
    carregar_funcionarios();
    carregar_quartos();
    carregar_estadias();
}


int main() {
    carregar_tudo();

    int opcao;
    do {
        system("cls");

        printf("============================================\n");
        printf("       HOTEL DESCANSO GARANTIDO - MENU      \n");
        printf("============================================\n");
        printf("  1. Cadastrar Cliente\n");
        printf("  2. Pesquisar Cliente\n");
        printf("  3. Cadastrar Funcionario\n");
        printf("  4. Pesquisar Funcionario\n");
        printf("  5. Cadastrar Quarto\n");
        printf("  6. Listar Quartos\n");
        printf("  7. Cadastrar Estadia\n");
        printf("  8. Dar Baixa em Estadia\n");
        printf("  9. Listar Estadias de um Cliente\n");
        printf("  0. Sair\n");
        printf("============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                pesquisar_cliente();
                break;
            case 3:
                cadastrar_funcionario();
                break;
            case 4:
                pesquisar_funcionario();
                break;
            case 5:
                cadastrar_quarto();
                break;
            case 6:
                listar_quartos();
                break;
            case 7:
                cadastrar_estadia();
                break;
            case 8:
                dar_baixa_estadia();
                break;
            case 9:
                listar_estadias_cliente();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // captura \n do scanf anterior
            getchar(); // espera ENTER
        }

    } while(opcao != 0);

    return 0;
}
