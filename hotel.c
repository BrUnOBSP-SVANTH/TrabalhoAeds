#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ============================================
// DEFINIÇÕES E CONSTANTES
// ============================================
#define MAX_NOME 50
#define MAX_END 100
#define MAX_TEL 15
#define MAX_CARGO 30
#define MAX_QUARTOS 100
#define MAX_ESTADIAS 100

#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_FUNCIONARIOS "funcionarios.dat"
#define ARQUIVO_QUARTOS "quartos.dat"
#define ARQUIVO_ESTADIAS "estadias.dat"

// ============================================
// ESTRUTURAS DE DADOS
// ============================================
typedef struct {
    long codigo;
    char nome[MAX_NOME];
    char endereco[MAX_END];
    char telefone[MAX_TEL];
    int pontosFidelidade;
} Cliente;

typedef struct {
    long codigo;
    char nome[MAX_NOME];
    char telefone[MAX_TEL];
    char cargo[MAX_CARGO];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    int status; // 0 = desocupado, 1 = ocupado
} Quarto;

typedef struct {
    long codigoEstadia;
    long codigoCliente;
    int numeroQuarto;
    int qtdDiarias;
    char dataEntrada[11]; // DD/MM/AAAA
    char dataSaida[11];   // DD/MM/AAAA
} Estadia;

// ============================================
// VARIÁVEIS GLOBAIS
// ============================================
Cliente clientes[100];
int total_clientes = 0;

Funcionario funcionarios[100];
int total_funcionarios = 0;

Quarto quartos[MAX_QUARTOS];
int total_quartos = 0;

Estadia estadias[MAX_ESTADIAS];
int total_estadias = 0;

// ============================================
// PROTÓTIPOS DE FUNÇÕES
// ============================================
// Cliente
void carregar_clientes();
void salvar_clientes();
long gerar_codigo_cliente();
void cadastrar_cliente();
void pesquisar_cliente();

// Funcionário
void carregar_funcionarios();
void salvar_funcionarios();
long gerar_codigo_funcionario();
void cadastrar_funcionario();
void pesquisar_funcionario();
int stricmp_custom(const char *s1, const char *s2);

// Quarto
void carregar_quartos();
void salvar_quartos();
void cadastrar_quarto();
void listar_quartos();
int verificar_quarto_disponivel(int qtd);

// Estadia
void carregar_estadias();
void salvar_estadias();
long gerar_codigo_estadia();
int calcular_diarias(const char *entrada, const char *saida);
int verificar_quarto_disponivel_com_datas(int qtd, const char *entrada, const char *saida);
void cadastrar_estadia();
void dar_baixa_estadia();
void listar_estadias_cliente();

// Sistema
void carregar_tudo();

// ============================================
// IMPLEMENTAÇÃO - CLIENTE
// ============================================
void carregar_clientes() {
    FILE *fp = fopen(ARQUIVO_CLIENTES, "rb");
    if (fp != NULL) {
        total_clientes = fread(clientes, sizeof(Cliente), 100, fp);
        fclose(fp);
    }
}

void salvar_clientes() {
    FILE *fp = fopen(ARQUIVO_CLIENTES, "wb");
    if (fp != NULL) {
        fwrite(clientes, sizeof(Cliente), total_clientes, fp);
        fclose(fp);
    }
}

long gerar_codigo_cliente() {
    long max = 0;
    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].codigo > max)
            max = clientes[i].codigo;
    }
    return max + 1;
}

void cadastrar_cliente() {
    Cliente c;
    c.codigo = gerar_codigo_cliente();
    printf("Nome: "); scanf(" %[^\n]", c.nome);
    printf("Endereco: "); scanf(" %[^\n]", c.endereco);
    printf("Telefone: "); scanf(" %[^\n]", c.telefone);
    c.pontosFidelidade = 0;

    clientes[total_clientes++] = c;
    salvar_clientes();
    printf("Cliente cadastrado com sucesso! Codigo: %ld\n", c.codigo);
}

void pesquisar_cliente() {
    char nome[MAX_NOME];
    long codigo;
    int achou = 0;
    printf("Digite o codigo (0 para pesquisar por nome): "); scanf("%ld", &codigo);
    if (codigo != 0) {
        for (int i = 0; i < total_clientes; i++) {
            if (clientes[i].codigo == codigo) {
                printf("Codigo: %ld\nNome: %s\nEndereco: %s\nTelefone: %s\nPontos: %d\n",
                    clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone, clientes[i].pontosFidelidade);
                achou = 1;
                break;
            }
        }
    } else {
        printf("Digite o nome: "); scanf(" %[^\n]", nome);
        for (int i = 0; i < total_clientes; i++) {
            if (strcasecmp(clientes[i].nome, nome) == 0) {
                printf("Codigo: %ld\nNome: %s\nEndereco: %s\nTelefone: %s\nPontos: %d\n",
                    clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone, clientes[i].pontosFidelidade);
                achou = 1;
            }
        }
    }
    if (!achou) printf("Cliente nao encontrado!\n");
}

// ============================================
// IMPLEMENTAÇÃO - FUNCIONÁRIO
// ============================================
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

void carregar_funcionarios() {
    FILE *fp = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (fp != NULL) {
        total_funcionarios = fread(funcionarios, sizeof(Funcionario), 100, fp);
        fclose(fp);
    } else {
        total_funcionarios = 0;
    }
}

void salvar_funcionarios() {
    FILE *fp = fopen(ARQUIVO_FUNCIONARIOS, "wb");
    if (fp != NULL) {
        fwrite(funcionarios, sizeof(Funcionario), total_funcionarios, fp);
        fclose(fp);
    }
}

long gerar_codigo_funcionario() {
    long max = 0;
    for (int i = 0; i < total_funcionarios; i++) {
        if (funcionarios[i].codigo > max)
            max = funcionarios[i].codigo;
    }
    return max + 1;
}

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

// ============================================
// IMPLEMENTAÇÃO - QUARTO
// ============================================
void carregar_quartos() {
    FILE *fp = fopen(ARQUIVO_QUARTOS, "rb");
    if (fp != NULL) {
        total_quartos = fread(quartos, sizeof(Quarto), MAX_QUARTOS, fp);
        fclose(fp);
    }
}

void salvar_quartos() {
    FILE *fp = fopen(ARQUIVO_QUARTOS, "wb");
    if (fp != NULL) {
        fwrite(quartos, sizeof(Quarto), total_quartos, fp);
        fclose(fp);
    }
}

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

int verificar_quarto_disponivel(int qtd) {
    for (int i = 0; i < total_quartos; i++) {
        if (quartos[i].status == 0 && quartos[i].quantidadeHospedes >= qtd) {
            return i;
        }
    }
    return -1;
}

// ============================================
// IMPLEMENTAÇÃO - ESTADIA
// ============================================
void carregar_estadias() {
    FILE *fp = fopen(ARQUIVO_ESTADIAS, "rb");
    if (fp != NULL) {
        total_estadias = fread(estadias, sizeof(Estadia), MAX_ESTADIAS, fp);
        fclose(fp);
    }
}

void salvar_estadias() {
    FILE *fp = fopen(ARQUIVO_ESTADIAS, "wb");
    if (fp != NULL) {
        fwrite(estadias, sizeof(Estadia), total_estadias, fp);
        fclose(fp);
    }
}

long gerar_codigo_estadia() {
    long max = 0;
    for (int i = 0; i < total_estadias; i++)
        if (estadias[i].codigoEstadia > max)
            max = estadias[i].codigoEstadia;
    return max + 1;
}

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

// ============================================
// FUNÇÃO PRINCIPAL
// ============================================
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
