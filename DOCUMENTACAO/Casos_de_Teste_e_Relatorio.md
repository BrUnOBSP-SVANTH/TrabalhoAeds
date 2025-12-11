# Planejamento de Casos de Teste e Relatório de Execução

**Alunos:** Bruno da Silva de Paulo, João Pedro Bandeira Ribas, Gabriel de Sousa Carvalho Ferreira

## 1. Planejamento de Casos de Teste

| ID | Módulo | Entrada | Saída Esperada |
| :--- | :--- | :--- | :--- |
| **CT-001** | Cadastrar Cliente | Nome: "João Silva", Endereço: "Rua A, 123", Telefone: "(31) 9999-8888" | Cliente cadastrado com sucesso com código gerado automaticamente. |
| **CT-002** | Pesquisar Cliente | Código: 1 | Exibir dados completos do Cliente "João Silva" com pontos de fidelidade. |
| **CT-003** | Pesquisar Cliente | Nome: "joão silva" (case-insensitive) | Exibir dados completos do Cliente "João Silva". |
| **CT-004** | Cadastrar Funcionário | Nome: "Maria Santos", Telefone: "(31) 8888-7777", Cargo: "Recepcionista", Salário: 2500.00 | Funcionário cadastrado com sucesso com código gerado automaticamente. |
| **CT-005** | Pesquisar Funcionário | Código: 1 | Exibir dados completos do Funcionário "Maria Santos". |
| **CT-006** | Pesquisar Funcionário | Nome: "MARIA SANTOS" (case-insensitive) | Exibir dados completos do Funcionário "Maria Santos". |
| **CT-007** | Cadastrar Quarto | Número: 101, Capacidade: 2, Diária: 150.00 | Quarto 101 cadastrado com sucesso, Status: "DESOCUPADO". |
| **CT-008** | Cadastrar Quarto | Número: 102, Capacidade: 4, Diária: 250.00 | Quarto 102 cadastrado com sucesso, Status: "DESOCUPADO". |
| **CT-009** | Cadastrar Quarto | Tentar cadastrar Quarto com Número: 101 (duplicado) | Mensagem de erro: "ERRO: Esse quarto ja existe!" |
| **CT-010** | Listar Quartos | - | Exibir lista de todos os quartos cadastrados com seus dados e status. |
| **CT-011** | Cadastrar Estadia | Cliente: 1, Hóspedes: 2, Entrada: 01/12/2025, Saída: 03/12/2025 | Estadia cadastrada com sucesso no Quarto 101, 2 diárias calculadas. Status do Quarto 101: "OCUPADO". |
| **CT-012** | Cadastrar Estadia | Cliente: 1, Hóspedes: 4, Entrada: 05/12/2025, Saída: 08/12/2025 | Estadia cadastrada com sucesso no Quarto 102, 3 diárias calculadas. Status do Quarto 102: "OCUPADO". |
| **CT-013** | Cadastrar Estadia | Cliente: 1, Hóspedes: 2, Entrada: 02/12/2025, Saída: 04/12/2025 (conflito com CT-011) | Mensagem: "Nenhum quarto disponivel para estas datas!" (verificação de conflito de datas). |
| **CT-014** | Cadastrar Estadia | Cliente inexistente (código 999) | Mensagem de erro: "Cliente nao encontrado!" |
| **CT-015** | Dar Baixa em Estadia | Código da Estadia: 1 (CT-011) | Valor Total: R$ 300.00 (2 diárias × R$ 150.00). Status do Quarto 101: "DESOCUPADO". Pontos adicionados ao cliente. |
| **CT-016** | Dar Baixa em Estadia | Código da Estadia: 2 (CT-012) | Valor Total: R$ 750.00 (3 diárias × R$ 250.00). Status do Quarto 102: "DESOCUPADO". Pontos adicionados ao cliente. |
| **CT-017** | Dar Baixa em Estadia | Código inexistente (999) | Mensagem de erro: "Estadia nao encontrada!" |
| **CT-018** | Listar Estadias de Cliente | Código Cliente: 1 | Exibir todas as estadias do cliente com datas, quartos e diárias. Mostrar pontos acumulados. |
| **CT-019** | Pontos de Fidelidade | Código Cliente: 1 (após CT-015 e CT-016) | Pontos: 50 (2 diárias do CT-011 + 3 diárias do CT-012) × 10 pontos por diária. |
| **CT-020** | Persistência de Dados | Sair do sistema e executar novamente | Todos os dados cadastrados devem ser carregados corretamente dos arquivos .dat |

## 2. Relatório de Execução de Testes

| ID | Saída Retornada (Real) | Passou? | Observações |
| :--- | :--- | :--- | :--- |
| **CT-001** | Cliente cadastrado com sucesso! Codigo: 1 | ✅ SIM | Código gerado automaticamente pela função `gerar_codigo_cliente()`. |
| **CT-002** | Exibiu: Codigo: 1, Nome: João Silva, Endereco: Rua A, 123, Telefone: (31) 9999-8888, Pontos: 0 | ✅ SIM | Pesquisa por código funcionando corretamente. |
| **CT-003** | Exibiu dados completos do cliente | ✅ SIM | Pesquisa case-insensitive por nome usando `strcasecmp()`. |
| **CT-004** | Funcionario cadastrado com sucesso! Codigo: 1 | ✅ SIM | Código gerado automaticamente pela função `gerar_codigo_funcionario()`. |
| **CT-005** | Exibiu dados completos do funcionário | ✅ SIM | Pesquisa por código funcionando corretamente. |
| **CT-006** | Exibiu dados completos do funcionário | ✅ SIM | Pesquisa case-insensitive por nome usando função customizada `stricmp_custom()`. |
| **CT-007** | Quarto cadastrado com sucesso! | ✅ SIM | Quarto criado com status inicial "DESOCUPADO" (status = 0). |
| **CT-008** | Quarto cadastrado com sucesso! | ✅ SIM | Segundo quarto cadastrado sem problemas. |
| **CT-009** | ERRO: Esse quarto ja existe! | ✅ SIM | Validação de unicidade do número do quarto funcionando. |
| **CT-010** | Lista exibida corretamente com todos os quartos | ✅ SIM | Função `listar_quartos()` mostra número, capacidade, valor e status. |
| **CT-011** | Estadia cadastrada! Codigo: 1, Quarto: 101 | ✅ SIM | Cálculo de diárias (2 dias) e atualização de status do quarto funcionando. |
| **CT-012** | Estadia cadastrada! Codigo: 2, Quarto: 102 | ✅ SIM | Sistema encontrou quarto com capacidade adequada (4 hóspedes). |
| **CT-013** | Nenhum quarto disponivel para estas datas! | ✅ SIM | **IMPLEMENTADO:** Verificação de conflito de datas usando `verificar_quarto_disponivel_com_datas()`. |
| **CT-014** | Cliente nao encontrado! | ✅ SIM | Validação de existência do cliente antes de cadastrar estadia. |
| **CT-015** | Baixa realizada! Valor a pagar: R$ 300.00 | ✅ SIM | Cálculo correto (2 × 150.00), status do quarto alterado para "DESOCUPADO", pontos adicionados. |
| **CT-016** | Baixa realizada! Valor a pagar: R$ 750.00 | ✅ SIM | Cálculo correto (3 × 250.00), status do quarto alterado, pontos adicionados. |
| **CT-017** | Estadia nao encontrada! | ✅ SIM | Validação de código de estadia funcionando. |
| **CT-018** | Lista de estadias exibida com dados completos e pontos acumulados | ✅ SIM | Função `listar_estadias_cliente()` mostra todas as estadias e calcula pontos. |
| **CT-019** | Pontos acumulados: 50 | ✅ SIM | Sistema de fidelidade integrado: 10 pontos por diária, adicionados ao dar baixa. |
| **CT-020** | Todos os dados foram carregados corretamente | ✅ SIM | Persistência em arquivos binários (.dat) funcionando com `carregar_*()` e `salvar_*()`. |

## 3. Funcionalidades Implementadas e Validadas

### 3.1 Módulo Cliente
- ✅ Cadastro com geração automática de código
- ✅ Persistência em arquivo binário (`clientes.dat`)
- ✅ Pesquisa por código
- ✅ Pesquisa por nome (case-insensitive)
- ✅ Sistema de pontos de fidelidade integrado

### 3.2 Módulo Funcionário
- ✅ Cadastro com geração automática de código
- ✅ Persistência em arquivo binário (`funcionarios.dat`)
- ✅ Pesquisa por código
- ✅ Pesquisa por nome (case-insensitive com função customizada)
- ✅ Validação de limite de cadastros (100 funcionários)

### 3.3 Módulo Quarto
- ✅ Cadastro com validação de unicidade do número
- ✅ Persistência em arquivo binário (`quartos.dat`)
- ✅ Listagem de todos os quartos
- ✅ Controle de status (ocupado/desocupado)
- ✅ Verificação de disponibilidade por capacidade

### 3.4 Módulo Estadia
- ✅ Cadastro com geração automática de código
- ✅ Cálculo automático de diárias entre datas
- ✅ Validação de cliente existente
- ✅ Verificação de disponibilidade de quarto por capacidade
- ✅ **Verificação de conflito de datas** (evita dupla reserva)
- ✅ Atualização automática do status do quarto para "OCUPADO"
- ✅ Persistência em arquivo binário (`estadias.dat`)
- ✅ Baixa em estadia com cálculo do valor total
- ✅ Liberação do quarto ao dar baixa
- ✅ Adição automática de pontos de fidelidade (10 pontos/diária)
- ✅ Listagem de estadias por cliente

### 3.5 Sistema de Fidelidade
- ✅ Cálculo automático: 10 pontos por diária
- ✅ Pontos adicionados ao cliente ao dar baixa na estadia
- ✅ Pontos armazenados persistentemente no cadastro do cliente
- ✅ Exibição de pontos acumulados na pesquisa de cliente
- ✅ Exibição de pontos ao listar estadias de um cliente

## 4. Melhorias Implementadas em Relação à Versão Anterior

1. **Verificação de Conflito de Datas:** A função `verificar_quarto_disponivel_com_datas()` foi implementada para verificar se um quarto está disponível em um período específico, evitando dupla reserva.

2. **Arquitetura Modular:** O código foi organizado em módulos separados (cliente, funcionario, quarto, estadia), facilitando manutenção e expansão.

3. **Sistema de Fidelidade Integrado:** Os pontos de fidelidade são calculados e armazenados automaticamente ao dar baixa em uma estadia, sem necessidade de módulo separado.

4. **Pesquisa Case-Insensitive:** Tanto clientes quanto funcionários podem ser pesquisados por nome sem distinção entre maiúsculas e minúsculas.

5. **Validações Robustas:** O sistema valida existência de clientes, unicidade de quartos, disponibilidade de quartos e conflitos de datas.

## 5. Conclusão

Todas as funcionalidades especificadas no trabalho foram implementadas e testadas com sucesso. O sistema está totalmente funcional, com persistência de dados em arquivos binários, validações adequadas e um sistema de fidelidade integrado. A arquitetura modular facilita futuras expansões e manutenções do código.

**Status Final:** ✅ **TODOS OS TESTES APROVADOS**
