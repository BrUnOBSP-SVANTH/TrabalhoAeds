#include "estadia.h"
#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARQUIVO_ESTADIAS "estadias.dat"

Estadia estadias[MAX_ESTADIAS];
int total_estadias = 0;

extern Cliente clientes[100];
extern int total_clientes;

extern Quarto quartos[100];
extern int total_quartos;

// necessário para dar baixa corretamente
extern void salvar_clientes();

// ===============================
// Carregar estadias
// ===============================
void carregar_estadias() {
    FILE *fp = fopen(ARQUIVO_ESTADIAS, "rb");
    if (fp != NULL) {
        total_estadias = fread(estadias, sizeof(Estadia), MAX_ESTADIAS, fp);
        fclose(fp);
    }
}

// ===============================
// Salvar estadias
// ===============================
void salvar_estadias() {
    FILE *fp = fopen(ARQUIVO_ESTADIAS, "wb");
    if (fp != NULL) {
        fwrite(estadias, sizeof(Estadia), total_estadias, fp);
        fclose(fp);
    }
}

// ===============================
// Gerar código único
// ===============================
long gerar_codigo_estadia() {
    long max = 0;
    for (int i = 0; i < total_estadias; i++)
        if (estadias[i].codigoEstadia > max)
            max = estadias[i].codigoEstadia;
    return max + 1;
}

// ===============================
// Calcular diárias entre datas
// ===============================
int calcular_diarias(const char *entrada, const char *saida) {
    int d1, m1, a1, d2, m2, a2;

    sscanf(entrada, "%d/%d/%d", &d1, &m1, &a1);
    sscanf(saida, "%d/%d/%d", &d2, &m2, &a2);

    struct tm te = {0}, ts = {0};

    te.tm_mday = d1;
    te.tm_mon  = m1 - 1;
    te.tm_year = a1 - 1900;

    ts.tm_mday = d2;
    ts.tm_mon  = m2 - 1;
    ts.tm_year = a2 - 1900;

    time_t t1 = mktime(&te);
    time_t t2 = mktime(&ts);

    double diff = difftime(t2, t1);
    int dias = (int)(diff / (60 * 60 * 24));

    if (dias < 1) dias = 1;
    return dias;
}

// ===============================
// Verificar quartos disponíveis
// ===============================
int verificar_quarto_disponivel_com_datas(int qtd, const char *entrada, const char *saida) {

    for (int i = 0; i < total_quartos; i++) {

        if (quartos[i].quantidadeHospedes < qtd || quartos[i].status == 1)
            continue;

        int disponivel = 1;

        for (int j = 0; j < total_estadias; j++) {

            if (estadias[j].numeroQuarto != quartos[i].numero)
                continue;

            // datas da estadia já existente
            struct tm e_old = {0}, s_old = {0};
            struct tm e_new = {0}, s_new = {0};
            int d, m, a;

            sscanf(estadias[j].dataEntrada, "%d/%d/%d", &d, &m, &a);
            e_old.tm_mday = d; e_old.tm_mon = m - 1; e_old.tm_year = a - 1900;

            sscanf(estadias[j].dataSaida, "%d/%d/%d", &d, &m, &a);
            s_old.tm_mday = d; s_old.tm_mon = m - 1; s_old.tm_year = a - 1900;

            // datas novas
            sscanf(entrada, "%d/%d/%d", &d, &m, &a);
            e_new.tm_mday = d; e_new.tm_mon = m - 1; e_new.tm_year = a - 1900;

            sscanf(saida, "%d/%d/%d", &d, &m, &a);
            s_new.tm_mday = d; s_new.tm_mon = m - 1; s_new.tm_year = a - 1900;

            time_t t_start_new = mktime(&e_new);
            time_t t_end_new   = mktime(&s_new);
            time_t t_start_old = mktime(&e_old);
            time_t t_end_old   = mktime(&s_old);

            // se as datas se sobrepõem, não está disponível
            if (!(t_end_new <= t_start_old || t_start_new >= t_end_old)) {
                disponivel = 0;
                break;
            }
        }

        if (disponivel)
            return i;
    }

    return -1;
}

// ===============================
// Cadastrar estadia
// ===============================
void cadastrar_estadia() {

    if (total_estadias >= MAX_ESTADIAS) {
        printf("Limite de estadias atingido!\n");
        return;
    }

    long codCliente;
    int qtdHospedes;
    char dataEnt[11], dataSai[11];

    printf("Codigo do cliente: ");
    scanf("%ld", &codCliente);

    int achou = 0;
    for (int i = 0; i < total_clientes; i++)
        if (clientes[i].codigo == codCliente) achou = 1;

    if (!achou) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("Quantidade de hospedes: ");
    scanf("%d", &qtdHospedes);

    printf("Data de entrada (DD/MM/AAAA): ");
    scanf("%s", dataEnt);

    printf("Data de saida (DD/MM/AAAA): ");
    scanf("%s", dataSai);

    int idxQuarto = verificar_quarto_disponivel_com_datas(qtdHospedes, dataEnt, dataSai);

    if (idxQuarto == -1) {
        printf("Nenhum quarto disponivel para estas datas!\n");
        return;
    }

    Estadia e;
    e.codigoEstadia = gerar_codigo_estadia();
    e.codigoCliente = codCliente;
    e.numeroQuarto  = quartos[idxQuarto].numero;
    e.qtdDiarias    = calcular_diarias(dataEnt, dataSai);

    strcpy(e.dataEntrada, dataEnt);
    strcpy(e.dataSaida, dataSai);

    quartos[idxQuarto].status = 1;

    estadias[total_estadias++] = e;

    salvar_quartos();
    salvar_estadias();

    printf("Estadia cadastrada! Codigo: %ld | Quarto: %d\n",
           e.codigoEstadia, quartos[idxQuarto].numero);
}

// ===============================
// Dar baixa
// ===============================
void dar_baixa_estadia() {
    long cod;
    printf("Codigo da estadia: ");
    scanf("%ld", &cod);

    for (int i = 0; i < total_estadias; i++) {
        if (estadias[i].codigoEstadia == cod) {

            int idxQ = -1;
            for (int j = 0; j < total_quartos; j++)
                if (quartos[j].numero == estadias[i].numeroQuarto)
                    idxQ = j;

            if (idxQ == -1) {
                printf("Quarto nao encontrado!\n");
                return;
            }

            float total = quartos[idxQ].valorDiaria * estadias[i].qtdDiarias;
            quartos[idxQ].status = 0;

            // adiciona pontos para cliente
            for (int j = 0; j < total_clientes; j++)
                if (clientes[j].codigo == estadias[i].codigoCliente)
                    clientes[j].pontosFidelidade += estadias[i].qtdDiarias * 10;

            salvar_quartos();
            salvar_estadias();
            salvar_clientes();

            printf("Baixa realizada!\nValor a pagar: R$ %.2f\n", total);
            return;
        }
    }

    printf("Estadia nao encontrada!\n");
}

// ===============================
// Listar estadias de cliente
// ===============================
void listar_estadias_cliente() {
    long cod;
    printf("Codigo do cliente: ");
    scanf("%ld", &cod);

    int achou = 0;
    int pontos = 0;

    for (int i = 0; i < total_estadias; i++) {
        if (estadias[i].codigoCliente == cod) {
            printf("Estadia %ld | Quarto %d | %s a %s | %d diarias\n",
                   estadias[i].codigoEstadia,
                   estadias[i].numeroQuarto,
                   estadias[i].dataEntrada,
                   estadias[i].dataSaida,
                   estadias[i].qtdDiarias);

            pontos += estadias[i].qtdDiarias * 10;
            achou = 1;
        }
    }

    if (!achou) printf("Nenhuma estadia encontrada!\n");
    else printf("Pontos acumulados: %d\n", pontos);
}
