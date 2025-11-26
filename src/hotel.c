// ====================================================================
// Implementação das funções do Hotel Descanso Garantido
// ====================================================================

#include "../include/hotel.h"
#include <time.h> // Necessário para mktime e difftime

// Nomes dos arquivos binários
#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_FUNCIONARIOS "funcionarios.dat"
#define ARQUIVO_QUARTOS "quartos.dat"
#define ARQUIVO_ESTADIAS "estadias.dat"

// ====================================================================
// Funções de Utilidade
// ====================================================================

/**
 * @brief Calcula a diferença em dias entre duas datas.
 * @param d1 Data de entrada.
 * @param d2 Data de saída.
 * @return O número de dias entre d1 e d2.
 */
int calcular_dias(Data d1, Data d2) {
    // Implementação simplificada: assume que d2 é sempre maior que d1
    // Para uma implementação robusta, seria necessário usar a biblioteca <time.h>
    // e a função mktime para converter para segundos e calcular a diferença.
    // A diária é calculada como d2 - d1.
    
    // Para o escopo do trabalho, a diferença simples de dias é aceitável, desde que d2 > d1.
    // Uma implementação mais robusta pode ser adicionada se o tempo permitir.
    
        // Implementação robusta usando time.h para calcular a diferença em dias
    struct tm tm1 = {0}, tm2 = {0};
    
    // Preenche a estrutura tm para a data de entrada
    tm1.tm_year = d1.ano - 1900;
    tm1.tm_mon = d1.mes - 1;
    tm1.tm_mday = d1.dia;
    
    // Preenche a estrutura tm para a data de saída
    tm2.tm_year = d2.ano - 1900;
    tm2.tm_mon = d2.mes - 1;
    tm2.tm_mday = d2.dia;
    
    // Converte para time_t (segundos desde a Epoch)
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    
    // Verifica se a conversão foi bem-sucedida e se a data de saída é posterior à de entrada
    if (t1 == (time_t)-1 || t2 == (time_t)-1 || t2 < t1) {
        return 0; // Retorna 0 diárias em caso de erro ou data inválida
    }
    
    // Calcula a diferença em segundos e converte para dias
    double diff_seconds = difftime(t2, t1);
    // Arredonda para o dia inteiro mais próximo (diferença de 1 dia = 1 diária)
    // O problema diz: "As diárias têm início às 14h00 e findam às 12h00 do dia seguinte."
    // Para simplificar o cálculo, consideraremos a diferença de dias inteiros.
    // Se a entrada for dia 1 e a saída dia 3, são 2 diárias.
    return (int)(diff_seconds / (60 * 60 * 24));
}

/**
 * @brief Valida se uma data é logicamente possível.
 * @param d A data a ser validada.
 * @return 1 se a data for válida, 0 caso contrário.
 */
int validar_data(Data d) {
    if (d.ano < 2024) return 0; // Ano mínimo razoável
    if (d.mes < 1 || d.mes > 12) return 0;
    if (d.dia < 1 || d.dia > 31) return 0;
    
    // Validação de dias por mês (simplificada)
    if (d.mes == 4 || d.mes == 6 || d.mes == 9 || d.mes == 11) {
        if (d.dia > 30) return 0;
    } else if (d.mes == 2) {
        // Considera ano bissexto (simplificado)
        int bissexto = (d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0);
        if (bissexto) {
            if (d.dia > 29) return 0;
        } else {
            if (d.dia > 28) return 0;
        }
    }
    return 1;
}

/**
 * @brief Exibe o menu principal do sistema.
 */
void exibir_menu() {
    printf("\n============================================\n");
    printf("       HOTEL DESCANSO GARANTIDO - MENU\n");
    printf("============================================\n");
    printf("  1. Cadastrar Cliente\n");
    printf("  2. Cadastrar Funcionário\n");
    printf("  3. Cadastrar Quarto\n");
    printf("  4. Cadastrar Estadia\n");
    printf("--------------------------------------------\n");
    printf("  5. Dar Baixa em Estadia\n");
    printf("  6. Pesquisar Cliente ou Funcionário\n");
    printf("  7. Mostrar Estadias de um Cliente\n");
    printf("  8. Calcular Pontos de Fidelidade\n");
    printf("--------------------------------------------\n");
    printf("  0. Sair\n");
    printf("============================================\n");
}

// ====================================================================
// Funções de Manipulação de Arquivos
// ====================================================================

/**
 * @brief Busca um cliente no arquivo pelo código.
 * @param codigo O código do cliente a ser buscado.
 * @return Um ponteiro para a estrutura Cliente alocada dinamicamente, ou NULL se não encontrado.
 */
Cliente *buscar_cliente_por_codigo(int codigo) {
    FILE *fp = fopen(ARQUIVO_CLIENTES, "rb");
    if (fp == NULL) {
        return NULL;
    }

    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    if (c == NULL) {
        fclose(fp);
        return NULL;
    }

    while (fread(c, sizeof(Cliente), 1, fp) == 1) {
        if (c->codigo == codigo) {
            fclose(fp);
            return c;
        }
    }

    fclose(fp);
    free(c);
    return NULL;
}

/**
 * @brief Busca um quarto no arquivo pelo número.
 * @param numero O número do quarto a ser buscado.
 * @return Um ponteiro para a estrutura Quarto alocada dinamicamente, ou NULL se não encontrado.
 */
Quarto *buscar_quarto_por_numero(int numero) {
    FILE *fp = fopen(ARQUIVO_QUARTOS, "rb");
    if (fp == NULL) {
        return NULL;
    }

    Quarto *q = (Quarto *)malloc(sizeof(Quarto));
    if (q == NULL) {
        fclose(fp);
        return NULL;
    }

    while (fread(q, sizeof(Quarto), 1, fp) == 1) {
        if (q->numero == numero) {
            fclose(fp);
            return q;
        }
    }

    fclose(fp);
    free(q);
    return NULL;
}

/**
 * @brief Atualiza um registro de quarto no arquivo.
 * @param q A estrutura Quarto com os dados atualizados.
 * @return 1 se a atualização foi bem-sucedida, 0 caso contrário.
 */
int atualizar_quarto(Quarto q) {
    FILE *fp = fopen(ARQUIVO_QUARTOS, "r+b");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de quartos para atualização");
        return 0;
    }

    Quarto temp_q;
    long pos = 0;
    int encontrado = 0;

    while (fread(&temp_q, sizeof(Quarto), 1, fp) == 1) {
        if (temp_q.numero == q.numero) {
            fseek(fp, pos, SEEK_SET);
            if (fwrite(&q, sizeof(Quarto), 1, fp) == 1) {
                encontrado = 1;
            }
            break;
        }
        pos = ftell(fp);
    }

    fclose(fp);
    return encontrado;
}

// ====================================================================
// Funções de Manipulação de Arquivos
// ====================================================================

/**
 * @brief Inicializa os arquivos binários de dados se eles não existirem.
 */
void inicializar_arquivos() {
    FILE *fp;
    
    // Cliente
    fp = fopen(ARQUIVO_CLIENTES, "rb");
    if (fp == NULL) {
        fp = fopen(ARQUIVO_CLIENTES, "wb");
        if (fp == NULL) {
            perror("Erro ao criar arquivo de clientes");
            exit(1);
        }
        // Adiciona um registro dummy para garantir que o arquivo não está vazio
        Cliente c_dummy = {0, "", "", ""};
        fwrite(&c_dummy, sizeof(Cliente), 1, fp);
    }
    fclose(fp);

    // Funcionário
    fp = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (fp == NULL) {
        fp = fopen(ARQUIVO_FUNCIONARIOS, "wb");
        if (fp == NULL) {
            perror("Erro ao criar arquivo de funcionários");
            exit(1);
        }
        Funcionario f_dummy = {0, "", "", "", 0.0};
        fwrite(&f_dummy, sizeof(Funcionario), 1, fp);
    }
    fclose(fp);

    // Quarto
    fp = fopen(ARQUIVO_QUARTOS, "rb");
    if (fp == NULL) {
        fp = fopen(ARQUIVO_QUARTOS, "wb");
        if (fp == NULL) {
            perror("Erro ao criar arquivo de quartos");
            exit(1);
        }
        Quarto q_dummy = {0, 0, 0.0, ""};
        fwrite(&q_dummy, sizeof(Quarto), 1, fp);
    }
    fclose(fp);

    // Estadia
    fp = fopen(ARQUIVO_ESTADIAS, "rb");
    if (fp == NULL) {
        fp = fopen(ARQUIVO_ESTADIAS, "wb");
        if (fp == NULL) {
            perror("Erro ao criar arquivo de estadias");
            exit(1);
        }
        Estadia e_dummy = {0, {0,0,0}, {0,0,0}, 0, 0, 0};
        fwrite(&e_dummy, sizeof(Estadia), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief Busca o próximo código sequencial disponível no arquivo.
 * @param nome_arquivo O nome do arquivo binário.
 * @return O próximo código (o maior código existente + 1).
 */
int buscar_proximo_codigo(const char *nome_arquivo) {
    FILE *fp = fopen(nome_arquivo, "rb");
    if (fp == NULL) {
        return 1; // Se o arquivo não existe ou está vazio, começa com 1
    }

    int maior_codigo = 0;
    
    if (strcmp(nome_arquivo, ARQUIVO_CLIENTES) == 0) {
        Cliente c;
        while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
            if (c.codigo > maior_codigo) {
                maior_codigo = c.codigo;
            }
        }
    } else if (strcmp(nome_arquivo, ARQUIVO_FUNCIONARIOS) == 0) {
        Funcionario f;
        while (fread(&f, sizeof(Funcionario), 1, fp) == 1) {
            if (f.codigo > maior_codigo) {
                maior_codigo = f.codigo;
            }
        }
    } else if (strcmp(nome_arquivo, ARQUIVO_ESTADIAS) == 0) {
        Estadia e;
        while (fread(&e, sizeof(Estadia), 1, fp) == 1) {
            if (e.codigo_estadia > maior_codigo) {
                maior_codigo = e.codigo_estadia;
            }
        }
    }
    
    fclose(fp);
    return maior_codigo + 1;
}

/**
 * @brief Busca uma estadia no arquivo pelo código.
 * @param codigo O código da estadia a ser buscada.
 * @return Um ponteiro para a estrutura Estadia alocada dinamicamente, ou NULL se não encontrada.
 */
Estadia *buscar_estadia_por_codigo(int codigo) {
    FILE *fp = fopen(ARQUIVO_ESTADIAS, "rb");
    if (fp == NULL) {
        return NULL;
    }

    Estadia *e = (Estadia *)malloc(sizeof(Estadia));
    if (e == NULL) {
        fclose(fp);
        return NULL;
    }

    while (fread(e, sizeof(Estadia), 1, fp) == 1) {
        if (e->codigo_estadia == codigo) {
            fclose(fp);
            return e;
        }
    }

    fclose(fp);
    free(e);
    return NULL;
}

/**
 * @brief Atualiza um registro de estadia no arquivo.
 * @param e A estrutura Estadia com os dados atualizados.
 * @return 1 se a atualização foi bem-sucedida, 0 caso contrário.
 */
int atualizar_estadia(Estadia e) {
    FILE *fp = fopen(ARQUIVO_ESTADIAS, "r+b");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de estadias para atualização");
        return 0;
    }

    Estadia temp_e;
    long pos = 0;
    int encontrado = 0;

    while (fread(&temp_e, sizeof(Estadia), 1, fp) == 1) {
        if (temp_e.codigo_estadia == e.codigo_estadia) {
            fseek(fp, pos, SEEK_SET);
            if (fwrite(&e, sizeof(Estadia), 1, fp) == 1) {
                encontrado = 1;
            }
            break;
        }
        pos = ftell(fp);
    }

    fclose(fp);
    return encontrado;
}

/**
 * @brief Busca um funcionário no arquivo pelo código.
 * @param codigo O código do funcionário a ser buscado.
 * @return Um ponteiro para a estrutura Funcionario alocada dinamicamente, ou NULL se não encontrado.
 */
Funcionario *buscar_funcionario_por_codigo(int codigo) {
    FILE *fp = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (fp == NULL) {
        return NULL;
    }

    Funcionario *f = (Funcionario *)malloc(sizeof(Funcionario));
    if (f == NULL) {
        fclose(fp);
        return NULL;
    }

    while (fread(f, sizeof(Funcionario), 1, fp) == 1) {
        if (f->codigo == codigo) {
            fclose(fp);
            return f;
        }
    }

    fclose(fp);
    free(f);
    return NULL;
}

// ====================================================================
// Funções de Cadastro (Implementação na próxima fase)
// ====================================================================

void cadastrar_cliente() {
    Cliente novo_cliente;
    FILE *fp;

    printf("\n--- Cadastro de Cliente ---\n");

    // 1. Gerar código
    novo_cliente.codigo = buscar_proximo_codigo(ARQUIVO_CLIENTES);
    printf("Código do Cliente: %d\n", novo_cliente.codigo);

    // 2. Coletar dados
    printf("Nome: ");
    // Limpa o buffer antes de ler a string
    while (getchar() != '\n'); 
    fgets(novo_cliente.nome, MAX_NOME, stdin);
    novo_cliente.nome[strcspn(novo_cliente.nome, "\n")] = 0; // Remove newline

    printf("Endereço: ");
    fgets(novo_cliente.endereco, MAX_ENDERECO, stdin);
    novo_cliente.endereco[strcspn(novo_cliente.endereco, "\n")] = 0;

    printf("Telefone: ");
    fgets(novo_cliente.telefone, MAX_TELEFONE, stdin);
    novo_cliente.telefone[strcspn(novo_cliente.telefone, "\n")] = 0;

    // 3. Salvar no arquivo
    fp = fopen(ARQUIVO_CLIENTES, "ab");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de clientes para escrita");
        return;
    }

    if (fwrite(&novo_cliente, sizeof(Cliente), 1, fp) != 1) {
        perror("Erro ao escrever cliente no arquivo");
    } else {
        printf("\nCliente %s (Código %d) cadastrado com sucesso!\n", novo_cliente.nome, novo_cliente.codigo);
    }

    fclose(fp);
}

void cadastrar_funcionario() {
    Funcionario novo_funcionario;
    FILE *fp;

    printf("\n--- Cadastro de Funcionário ---\n");

    // 1. Gerar código
    novo_funcionario.codigo = buscar_proximo_codigo(ARQUIVO_FUNCIONARIOS);
    printf("Código do Funcionário: %d\n", novo_funcionario.codigo);

    // 2. Coletar dados
    printf("Nome: ");
    while (getchar() != '\n'); 
    fgets(novo_funcionario.nome, MAX_NOME, stdin);
    novo_funcionario.nome[strcspn(novo_funcionario.nome, "\n")] = 0;

    printf("Telefone: ");
    fgets(novo_funcionario.telefone, MAX_TELEFONE, stdin);
    novo_funcionario.telefone[strcspn(novo_funcionario.telefone, "\n")] = 0;

    printf("Cargo: ");
    fgets(novo_funcionario.cargo, MAX_CARGO, stdin);
    novo_funcionario.cargo[strcspn(novo_funcionario.cargo, "\n")] = 0;

    printf("Salário: ");
    if (scanf("%f", &novo_funcionario.salario) != 1 || novo_funcionario.salario < 0) {
        printf("Salário inválido. Cadastro cancelado.\n");
        return;
    }

    // 3. Salvar no arquivo
    fp = fopen(ARQUIVO_FUNCIONARIOS, "ab");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de funcionários para escrita");
        return;
    }

    if (fwrite(&novo_funcionario, sizeof(Funcionario), 1, fp) != 1) {
        perror("Erro ao escrever funcionário no arquivo");
    } else {
        printf("\nFuncionário %s (Código %d) cadastrado com sucesso!\n", novo_funcionario.nome, novo_funcionario.codigo);
    }

    fclose(fp);
}

void cadastrar_quarto() {
    Quarto novo_quarto;
    FILE *fp;
    int numero_quarto_temp;

    printf("\n--- Cadastro de Quarto ---\n");

    // 1. Coletar número do quarto e validar unicidade
    printf("Número do Quarto: ");
    if (scanf("%d", &numero_quarto_temp) != 1 || numero_quarto_temp <= 0) {
        printf("Número de quarto inválido. Cadastro cancelado.\n");
        return;
    }
    novo_quarto.numero = numero_quarto_temp;

    // Validação de unicidade
    if (buscar_quarto_por_numero(novo_quarto.numero) != NULL) {
        printf("Erro: Já existe um quarto cadastrado com o número %d.\n", novo_quarto.numero);
        return;
    }

    printf("Quantidade de Hóspedes: ");
    if (scanf("%d", &novo_quarto.qtd_hospedes) != 1 || novo_quarto.qtd_hospedes <= 0) {
        printf("Quantidade de hóspedes inválida. Cadastro cancelado.\n");
        return;
    }

    printf("Valor da Diária: ");
    if (scanf("%f", &novo_quarto.valor_diaria) != 1 || novo_quarto.valor_diaria <= 0) {
        printf("Valor da diária inválido. Cadastro cancelado.\n");
        return;
    }

    // Status inicial é "desocupado"
    strcpy(novo_quarto.status, "desocupado");

    // 2. Salvar no arquivo
    fp = fopen(ARQUIVO_QUARTOS, "ab");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de quartos para escrita");
        return;
    }

    if (fwrite(&novo_quarto, sizeof(Quarto), 1, fp) != 1) {
        perror("Erro ao escrever quarto no arquivo");
    } else {
        printf("\nQuarto %d cadastrado com sucesso! Status: %s\n", novo_quarto.numero, novo_quarto.status);
    }

    fclose(fp);
}

void cadastrar_estadia() {
    Estadia nova_estadia;
    FILE *fp;
    int dia, mes, ano;

    printf("\n--- Cadastro de Estadia ---\n");

    // 1. Gerar código
    nova_estadia.codigo_estadia = buscar_proximo_codigo(ARQUIVO_ESTADIAS);
    printf("Código da Estadia: %d\n", nova_estadia.codigo_estadia);

    // 2. Coletar dados
    printf("Código do Cliente: ");
    if (scanf("%d", &nova_estadia.codigo_cliente) != 1 || nova_estadia.codigo_cliente <= 0) {
        printf("Código de cliente inválido. Cadastro cancelado.\n");
        return;
    }
    Cliente *cliente_existente = buscar_cliente_por_codigo(nova_estadia.codigo_cliente);
    if (cliente_existente == NULL) {
        printf("Erro: Cliente com código %d não encontrado. Cadastre o cliente primeiro.\n", nova_estadia.codigo_cliente);
        return;
    }
    free(cliente_existente); // Libera a memória alocada por buscar_cliente_por_codigo

    printf("Quantidade de Hóspedes: ");
    int qtd_hospedes;
    if (scanf("%d", &qtd_hospedes) != 1 || qtd_hospedes <= 0) {
        printf("Quantidade de hóspedes inválida. Cadastro cancelado.\n");
        return;
    }

    printf("Data de Entrada (dd mm aaaa): ");
    if (scanf("%d %d %d", &dia, &mes, &ano) != 3) {
        printf("Formato de data inválido. Cadastro cancelado.\n");
        return;
    }
    nova_estadia.data_entrada = (Data){dia, mes, ano};
    if (!validar_data(nova_estadia.data_entrada)) {
        printf("Data de entrada inválida. Cadastro cancelado.\n");
        return;
    }

    printf("Data de Saída (dd mm aaaa): ");
    if (scanf("%d %d %d", &dia, &mes, &ano) != 3) {
        printf("Formato de data inválido. Cadastro cancelado.\n");
        return;
    }
    nova_estadia.data_saida = (Data){dia, mes, ano};
    if (!validar_data(nova_estadia.data_saida)) {
        printf("Data de saída inválida. Cadastro cancelado.\n");
        return;
    }

    // 3. Calcular diárias
    nova_estadia.qtd_diarias = calcular_dias(nova_estadia.data_entrada, nova_estadia.data_saida);
    if (nova_estadia.qtd_diarias <= 0) {
        printf("Data de saída deve ser posterior à data de entrada. Cadastro cancelado.\n");
        return;
    }
    printf("Diárias calculadas: %d\n", nova_estadia.qtd_diarias);

    // Lógica para encontrar quarto disponível
    Quarto *quarto_disponivel = NULL;
    int melhor_capacidade_sobra = 9999; // Um número grande para iniciar a comparação
    FILE *fp_quartos = fopen(ARQUIVO_QUARTOS, "rb");
    if (fp_quartos == NULL) {
        perror("Erro ao abrir arquivo de quartos para busca");
        return;
    }

    Quarto temp_q;
    while (fread(&temp_q, sizeof(Quarto), 1, fp_quartos) == 1) {
        // Critérios de busca: desocupado e comporta a quantidade de hóspedes
        if (strcmp(temp_q.status, "desocupado") == 0 && temp_q.qtd_hospedes >= qtd_hospedes) {
            // TODO: Adicionar validação de período (não deve haver outra estadia no mesmo período)
            // Por enquanto, apenas o status "desocupado" é suficiente para a primeira iteração.
            int capacidade_sobra = temp_q.qtd_hospedes - qtd_hospedes;
            if (quarto_disponivel == NULL || capacidade_sobra < melhor_capacidade_sobra) {
                melhor_capacidade_sobra = capacidade_sobra;
                if (quarto_disponivel == NULL) {
                    quarto_disponivel = (Quarto *)malloc(sizeof(Quarto));
                    if (quarto_disponivel == NULL) {
                        fclose(fp_quartos);
                        perror("Erro de alocação de memória");
                        return;
                    }
                }
                *quarto_disponivel = temp_q;
            }
        }
    }
    fclose(fp_quartos);

    if (quarto_disponivel == NULL) {
        printf("Erro: Nenhum quarto disponível encontrado para %d hóspedes.\n", qtd_hospedes);
        return;
    }

    nova_estadia.numero_quarto = quarto_disponivel->numero;
    printf("Quarto disponível encontrado: %d (Diária: %.2f)\n", quarto_disponivel->numero, quarto_disponivel->valor_diaria);

    // Atualizar status do quarto para "ocupado"
    strcpy(quarto_disponivel->status, "ocupado");
    if (!atualizar_quarto(*quarto_disponivel)) {
        printf("Erro ao atualizar o status do quarto.\n");
        free(quarto_disponivel);
        return;
    }
    free(quarto_disponivel);

    // 4. Salvar no arquivo
    fp = fopen(ARQUIVO_ESTADIAS, "ab");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de estadias para escrita");
        return;
    }

    if (fwrite(&nova_estadia, sizeof(Estadia), 1, fp) != 1) {
        perror("Erro ao escrever estadia no arquivo");
    } else {
        printf("\nEstadia %d cadastrada com sucesso! Quarto: %d, Cliente: %d\n", 
               nova_estadia.codigo_estadia, nova_estadia.numero_quarto, nova_estadia.codigo_cliente);
    }

    fclose(fp);
}

// ====================================================================
// Funções de Operação (Implementação em fases posteriores)
// ====================================================================

void dar_baixa_estadia() {
    int codigo_estadia;
    printf("\n--- Baixa em Estadia ---\n");
    printf("Digite o código da estadia para dar baixa: ");
    if (scanf("%d", &codigo_estadia) != 1 || codigo_estadia <= 0) {
        printf("Código de estadia inválido.\n");
        return;
    }

    Estadia *estadia = buscar_estadia_por_codigo(codigo_estadia);
    if (estadia == NULL) {
        printf("Erro: Estadia com código %d não encontrada.\n", codigo_estadia);
        return;
    }

    // 1. Buscar o quarto
    Quarto *quarto = buscar_quarto_por_numero(estadia->numero_quarto);
    if (quarto == NULL) {
        printf("Erro: Quarto %d da estadia não encontrado.\n", estadia->numero_quarto);
        free(estadia);
        return;
    }

    // 2. Calcular o valor total
    float valor_total = estadia->qtd_diarias * quarto->valor_diaria;

    // 3. Mostrar o valor total
    printf("\n--- Detalhes da Baixa ---\n");
    printf("Estadia Código: %d\n", estadia->codigo_estadia);
    printf("Cliente Código: %d\n", estadia->codigo_cliente);
    printf("Quarto Número: %d\n", quarto->numero);
    printf("Diárias: %d\n", estadia->qtd_diarias);
    printf("Valor da Diária: R$ %.2f\n", quarto->valor_diaria);
    printf("VALOR TOTAL A SER PAGO: R$ %.2f\n", valor_total);

    // 4. Alterar o status do quarto para "desocupado"
    strcpy(quarto->status, "desocupado");
    if (!atualizar_quarto(*quarto)) {
        printf("Erro ao atualizar o status do quarto para desocupado.\n");
    } else {
        printf("Status do Quarto %d atualizado para 'desocupado'.\n", quarto->numero);
    }

    // 5. Marcar a estadia como "finalizada" (ou remover/mover, mas a atualização é mais simples)
    // Para fins de registro, podemos simplesmente não fazer nada com a estadia,
    // ou adicionar um campo 'status' na struct Estadia.
    // Como o requisito é "dar baixa", vamos assumir que a atualização do quarto é o suficiente
    // para a baixa, mantendo o registro da estadia para histórico.

    free(estadia);
    free(quarto);
}

void pesquisar_cliente_ou_funcionario() {
    int tipo_pesquisa, codigo;
    char nome[MAX_NOME];
    FILE *fp;

    printf("\n--- Pesquisa de Cliente ou Funcionário ---\n");
    printf("1. Pesquisar Cliente\n");
    printf("2. Pesquisar Funcionário\n");
    printf("Escolha o tipo de pesquisa: ");
    if (scanf("%d", &tipo_pesquisa) != 1 || (tipo_pesquisa != 1 && tipo_pesquisa != 2)) {
        printf("Opção inválida.\n");
        return;
    }

    printf("1. Pesquisar por Código\n");
    printf("2. Pesquisar por Nome\n");
    printf("Escolha o critério de pesquisa: ");
    int criterio;
    if (scanf("%d", &criterio) != 1 || (criterio != 1 && criterio != 2)) {
        printf("Opção inválida.\n");
        return;
    }

    if (tipo_pesquisa == 1) { // Cliente
        fp = fopen(ARQUIVO_CLIENTES, "rb");
        if (fp == NULL) {
            perror("Erro ao abrir arquivo de clientes");
            return;
        }
        Cliente c;
        int encontrado = 0;

        if (criterio == 1) { // Por Código
            printf("Digite o Código do Cliente: ");
            if (scanf("%d", &codigo) != 1) {
                printf("Código inválido.\n");
                fclose(fp);
                return;
            }
            while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
                if (c.codigo == codigo) {
                    printf("\n--- Cliente Encontrado ---\n");
                    printf("Código: %d\n", c.codigo);
                    printf("Nome: %s\n", c.nome);
                    printf("Endereço: %s\n", c.endereco);
                    printf("Telefone: %s\n", c.telefone);
                    encontrado = 1;
                    break;
                }
            }
        } else { // Por Nome
            printf("Digite o Nome do Cliente: ");
            while (getchar() != '\n');
            fgets(nome, MAX_NOME, stdin);
            nome[strcspn(nome, "\n")] = 0;

            while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
                if (strstr(c.nome, nome) != NULL) {
                    printf("\n--- Cliente Encontrado ---\n");
                    printf("Código: %d\n", c.codigo);
                    printf("Nome: %s\n", c.nome);
                    printf("Endereço: %s\n", c.endereco);
                    printf("Telefone: %s\n", c.telefone);
                    encontrado = 1;
                }
            }
        }
        fclose(fp);
        if (!encontrado) {
            printf("\nCliente não encontrado.\n");
        }

    } else { // Funcionário
        fp = fopen(ARQUIVO_FUNCIONARIOS, "rb");
        if (fp == NULL) {
            perror("Erro ao abrir arquivo de funcionários");
            return;
        }
        Funcionario f;
        int encontrado = 0;

        if (criterio == 1) { // Por Código
            printf("Digite o Código do Funcionário: ");
            if (scanf("%d", &codigo) != 1) {
                printf("Código inválido.\n");
                fclose(fp);
                return;
            }
            while (fread(&f, sizeof(Funcionario), 1, fp) == 1) {
                if (f.codigo == codigo) {
                    printf("\n--- Funcionário Encontrado ---\n");
                    printf("Código: %d\n", f.codigo);
                    printf("Nome: %s\n", f.nome);
                    printf("Telefone: %s\n", f.telefone);
                    printf("Cargo: %s\n", f.cargo);
                    printf("Salário: R$ %.2f\n", f.salario);
                    encontrado = 1;
                    break;
                }
            }
        } else { // Por Nome
            printf("Digite o Nome do Funcionário: ");
            while (getchar() != '\n');
            fgets(nome, MAX_NOME, stdin);
            nome[strcspn(nome, "\n")] = 0;

            while (fread(&f, sizeof(Funcionario), 1, fp) == 1) {
                if (strstr(f.nome, nome) != NULL) {
                    printf("\n--- Funcionário Encontrado ---\n");
                    printf("Código: %d\n", f.codigo);
                    printf("Nome: %s\n", f.nome);
                    printf("Telefone: %s\n", f.telefone);
                    printf("Cargo: %s\n", f.cargo);
                    printf("Salário: R$ %.2f\n", f.salario);
                    encontrado = 1;
                }
            }
        }
        fclose(fp);
        if (!encontrado) {
            printf("\nFuncionário não encontrado.\n");
        }
    }
}

void mostrar_estadias_cliente() {
    int codigo_cliente;
    printf("\n--- Estadias de Cliente ---\n");
    printf("Digite o Código do Cliente: ");
    if (scanf("%d", &codigo_cliente) != 1 || codigo_cliente <= 0) {
        printf("Código de cliente inválido.\n");
        return;
    }

    Cliente *cliente = buscar_cliente_por_codigo(codigo_cliente);
    if (cliente == NULL) {
        printf("Erro: Cliente com código %d não encontrado.\n", codigo_cliente);
        return;
    }
    printf("\nEstadias para o Cliente: %s (Código %d)\n", cliente->nome, cliente->codigo);
    free(cliente);

    FILE *fp = fopen(ARQUIVO_ESTADIAS, "rb");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de estadias");
        return;
    }

    Estadia e;
    int encontrado = 0;
    while (fread(&e, sizeof(Estadia), 1, fp) == 1) {
        if (e.codigo_cliente == codigo_cliente) {
            printf("----------------------------------------\n");
            printf("Código da Estadia: %d\n", e.codigo_estadia);
            printf("Quarto: %d\n", e.numero_quarto);
            printf("Entrada: %d/%d/%d\n", e.data_entrada.dia, e.data_entrada.mes, e.data_entrada.ano);
            printf("Saída: %d/%d/%d\n", e.data_saida.dia, e.data_saida.mes, e.data_saida.ano);
            printf("Diárias: %d\n", e.qtd_diarias);
            encontrado = 1;
        }
    }

    fclose(fp);
    if (!encontrado) {
        printf("Nenhuma estadia encontrada para este cliente.\n");
    }
}

void calcular_pontos_fidelidade() {
    int codigo_cliente;
    printf("\n--- Cálculo de Pontos de Fidelidade ---\n");
    printf("Digite o Código do Cliente: ");
    if (scanf("%d", &codigo_cliente) != 1 || codigo_cliente <= 0) {
        printf("Código de cliente inválido.\n");
        return;
    }

    Cliente *cliente = buscar_cliente_por_codigo(codigo_cliente);
    if (cliente == NULL) {
        printf("Erro: Cliente com código %d não encontrado.\n", codigo_cliente);
        return;
    }
    printf("\nCalculando pontos para o Cliente: %s (Código %d)\n", cliente->nome, cliente->codigo);
    free(cliente);

    FILE *fp = fopen(ARQUIVO_ESTADIAS, "rb");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de estadias");
        return;
    }

    Estadia e;
    int total_diarias = 0;
    while (fread(&e, sizeof(Estadia), 1, fp) == 1) {
        if (e.codigo_cliente == codigo_cliente) {
            total_diarias += e.qtd_diarias;
        }
    }

    fclose(fp);

    int pontos_fidelidade = total_diarias * 10;
    printf("\nTotal de Diárias Registradas: %d\n", total_diarias);
    printf("Pontos de Fidelidade Acumulados (10 pontos/diária): %d\n", pontos_fidelidade);
}
