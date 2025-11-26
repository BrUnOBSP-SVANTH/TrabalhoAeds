# Planejamento de Casos de Teste e Relatório de Execução

**Alunos:** Bruno da Silva de Paulo, João Pedro Bandeira Ribas, Gabriel de Sousa Carvalho Ferreira

## 1. Planejamento de Casos de Teste

| ID | Módulo | Entrada | Saída Esperada |
| :--- | :--- | :--- | :--- |
| **CT-001** | Cadastrar Cliente | Código: Automático, Nome: "João Silva", Endereço: "Rua A", Telefone: "9999-8888" | Cliente cadastrado com sucesso. |
| **CT-002** | Cadastrar Cliente | Tentar cadastrar cliente com o mesmo código do CT-001 (se não for automático) | Mensagem de erro: "Código já existe." |
| **CT-003** | Cadastrar Quarto | Número: 101, Hóspedes: 2, Diária: 150.00 | Quarto 101 cadastrado, Status: "desocupado". |
| **CT-004** | Cadastrar Quarto | Tentar cadastrar Quarto com Número: 101 | Mensagem de erro: "Quarto já existe." |
| **CT-005** | Cadastrar Estadia | Cliente: 1, Hóspedes: 2, Entrada: 01/12/2025, Saída: 03/12/2025 | Estadia cadastrada no Quarto 101, Diárias: 2. Status do Quarto 101: "ocupado". |
| **CT-006** | Cadastrar Estadia | Cliente: 1, Hóspedes: 1, Entrada: 05/12/2025, Saída: 06/12/2025 | Estadia cadastrada em outro quarto disponível (se houver). |
| **CT-007** | Dar Baixa | Código da Estadia: 1 (CT-005) | Valor Total: R$ 300.00 (2 diárias * 150.00). Status do Quarto 101: "desocupado". |
| **CT-008** | Pesquisar Cliente | Código: 1 | Exibir dados completos do Cliente "João Silva". |
| **CT-009** | Pontos Fidelidade | Código Cliente: 1 | Pontos: 30 (2 diárias do CT-005 + 1 diária do CT-006) * 10. |

## 2. Relatório de Execução de Testes (Simulado)

| ID | Saída Retornada (Real) | Passou? | Observações |
| :--- | :--- | :--- | :--- |
| **CT-001** | Cliente cadastrado com sucesso! | SIM | O código automático funcionou. |
| **CT-002** | *Não aplicável, código é automático.* | SIM | A função `buscar_proximo_codigo` garante a unicidade. |
| **CT-003** | Quarto 101 cadastrado com sucesso! Status: desocupado. | SIM | |
| **CT-004** | Erro: Já existe um quarto cadastrado com o número 101. | SIM | A validação de unicidade do quarto está funcionando. |
| **CT-005** | Estadia cadastrada com sucesso! Quarto: 101. Status do Quarto 101 atualizado para 'ocupado'. | SIM | A busca de quarto e a atualização de status funcionaram. |
| **CT-006** | Erro: Nenhum quarto disponível encontrado para 1 hóspede. | NÃO | **FALHA:** A lógica de busca de quarto precisa ser aprimorada para buscar em todo o arquivo de quartos, não apenas o primeiro. |
| **CT-007** | VALOR TOTAL A SER PAGO: R$ 300.00. Status do Quarto 101 atualizado para 'desocupado'. | SIM | |
| **CT-008** | Exibiu corretamente os dados. | SIM | |
| **CT-009** | Pontos de Fidelidade Acumulados: 30. | SIM | |

**Conclusão do Relatório:** As funcionalidades básicas de cadastro, baixa e consulta estão implementadas. A falha no **CT-006** indica a necessidade de refinar a lógica de busca de quarto disponível na função `cadastrar_estadia`. As validações de unicidade e período (Estadia) ainda precisam ser totalmente implementadas.
