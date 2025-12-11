# Backlog do Produto e Planejamento de Sprints - Hotel Descanso Garantido

**Alunos:** Bruno da Silva de Paulo, João Pedro Bandeira Ribas, Gabriel de Sousa Carvalho Ferreira

## Backlog do Produto

| ID | Funcionalidade | Requisito (PDF) | Responsável | Status |
| :--- | :--- | :--- | :--- | :--- |
| 1 | Cadastrar Cliente | 1 | Bruno | ✅ Concluído |
| 2 | Cadastrar Funcionário | 2 | João Pedro | ✅ Concluído |
| 3 | Cadastrar Quarto | 3 | Gabriel | ✅ Concluído |
| 4 | Cadastrar Estadia | 4 | Bruno | ✅ Concluído |
| 5 | Dar Baixa em Estadia | 5 | João Pedro | ✅ Concluído |
| 6 | Pesquisar Cliente/Funcionário | 6 | Gabriel | ✅ Concluído |
| 7 | Mostrar Estadias de Cliente | 7 | Bruno | ✅ Concluído |
| 8 | Calcular Pontos de Fidelidade | 8 | João Pedro | ✅ Concluído |
| 9 | Menu Principal e Loop | `main()` | Gabriel | ✅ Concluído |
| 10 | Manipulação de Arquivos Binários | Geral | Todos | ✅ Concluído |
| 11 | Validação de Unicidade (Cliente/Funcionário/Quarto) | Restrições | Todos | ✅ Concluído |
| 12 | Validação de Período (Estadia) | Restrições | Todos | ✅ Concluído |
| 13 | Listar Quartos | Consulta | Gabriel | ✅ Concluído |
| 14 | Arquitetura Modular | Qualidade | Todos | ✅ Concluído |

## Planejamento de Sprints

O projeto foi desenvolvido em 3 sprints principais, seguindo a metodologia Scrum.

### Sprint 1: Estrutura e Cadastros Básicos

**Objetivo:** Criar a estrutura modular do projeto e implementar os cadastros básicos de todas as entidades.

| Tarefa | Responsável | Status |
| :--- | :--- | :--- |
| Estrutura do Projeto (Arquivos .h e .c modulares) | Gabriel | ✅ Concluído |
| Implementação das Estruturas de Dados (structs) | Bruno | ✅ Concluído |
| Funções de Utilidade (Menu, Cálculo de Datas) | João Pedro | ✅ Concluído |
| Funções de Manipulação de Arquivos (carregar/salvar) | Gabriel | ✅ Concluído |
| Implementação: Cadastrar Cliente (Funcionalidade 1) | Bruno | ✅ Concluído |
| Implementação: Cadastrar Funcionário (Funcionalidade 2) | João Pedro | ✅ Concluído |
| Implementação: Cadastrar Quarto (Funcionalidade 3) | Gabriel | ✅ Concluído |
| Geração Automática de Códigos Únicos | Todos | ✅ Concluído |

**Entregáveis:**
- Módulos cliente.c/h, funcionario.c/h, quarto.c/h
- Sistema de persistência em arquivos binários (.dat)
- Geração automática de códigos para cliente, funcionário e estadia

### Sprint 2: Estadia e Operações Essenciais

**Objetivo:** Implementar o módulo de estadias com todas as validações e regras de negócio.

| Tarefa | Responsável | Status |
| :--- | :--- | :--- |
| Implementação: Cadastrar Estadia (Funcionalidade 4) | Bruno | ✅ Concluído |
| Cálculo Automático de Diárias entre Datas | Bruno | ✅ Concluído |
| Verificação de Disponibilidade por Capacidade | Gabriel | ✅ Concluído |
| **Verificação de Conflito de Datas** | Bruno | ✅ Concluído |
| Implementação: Dar Baixa em Estadia (Funcionalidade 5) | João Pedro | ✅ Concluído |
| Implementação: Pesquisar Cliente/Funcionário (Funcionalidade 6) | Gabriel | ✅ Concluído |
| Pesquisa Case-Insensitive por Nome | Gabriel | ✅ Concluído |
| **Validação de Unicidade** (Cliente, Funcionário, Quarto) | Todos | ✅ Concluído |
| **Validação de Período** (Estadia - Conflito de Datas) | Todos | ✅ Concluído |

**Entregáveis:**
- Módulo estadia.c/h completo
- Função `verificar_quarto_disponivel_com_datas()` para evitar dupla reserva
- Função `calcular_diarias()` usando estruturas de tempo
- Validações de unicidade para quartos
- Pesquisa por código e por nome (case-insensitive)

### Sprint 3: Consultas, Fidelidade e Finalização

**Objetivo:** Implementar sistema de fidelidade, consultas avançadas e finalizar documentação.

| Tarefa | Responsável | Status |
| :--- | :--- | :--- |
| Implementação: Mostrar Estadias de Cliente (Funcionalidade 7) | Bruno | ✅ Concluído |
| Implementação: Calcular Pontos de Fidelidade (Funcionalidade 8) | João Pedro | ✅ Concluído |
| Integração do Sistema de Fidelidade (10 pontos/diária) | João Pedro | ✅ Concluído |
| Implementação: Listar Quartos | Gabriel | ✅ Concluído |
| Testes de Integração e Depuração | Gabriel | ✅ Concluído |
| Criação do Makefile | Todos | ✅ Concluído |
| Planejamento de Casos de Teste | Todos | ✅ Concluído |
| Execução e Documentação de Testes | Todos | ✅ Concluído |
| Documentação Final (README, Backlog, Casos de Teste) | Todos | ✅ Concluído |

**Entregáveis:**
- Sistema de pontos de fidelidade integrado (adicionado automaticamente ao dar baixa)
- Função `listar_estadias_cliente()` com cálculo de pontos
- Função `listar_quartos()` com exibição de status
- Makefile para compilação simplificada
- Documentação completa de casos de teste
- README atualizado com estrutura modular

## Resumo de Funcionalidades Implementadas

### ✅ Funcionalidades Principais
1. **Cadastro de Cliente** - com geração automática de código e pontos de fidelidade
2. **Cadastro de Funcionário** - com geração automática de código
3. **Cadastro de Quarto** - com validação de unicidade do número
4. **Cadastro de Estadia** - com cálculo de diárias e verificação de disponibilidade
5. **Baixa em Estadia** - com cálculo de valor total e adição de pontos
6. **Pesquisa de Cliente** - por código ou nome (case-insensitive)
7. **Pesquisa de Funcionário** - por código ou nome (case-insensitive)
8. **Listar Quartos** - com status de ocupação
9. **Listar Estadias de Cliente** - com cálculo de pontos acumulados
10. **Sistema de Pontos de Fidelidade** - 10 pontos por diária, adicionados automaticamente

### ✅ Validações Implementadas
- Geração automática de códigos únicos (cliente, funcionário, estadia)
- Validação de unicidade de número de quarto
- Validação de existência de cliente ao cadastrar estadia
- Verificação de capacidade do quarto
- **Verificação de conflito de datas** (evita dupla reserva do mesmo quarto)
- Validação de código de estadia ao dar baixa

### ✅ Recursos Técnicos
- Arquitetura modular (cliente, funcionario, quarto, estadia)
- Persistência em arquivos binários (.dat)
- Funções de carregar/salvar para cada módulo
- Cálculo de datas usando estruturas `tm` e funções `mktime()` e `difftime()`
- Menu interativo com loop principal
- Makefile para compilação simplificada

## Conclusão

**Status do Projeto:** ✅ **100% CONCLUÍDO**

Todas as funcionalidades especificadas no trabalho foram implementadas e testadas com sucesso. O sistema está totalmente funcional, com validações robustas, persistência de dados e uma arquitetura modular que facilita manutenção e expansão futura.

**Destaques:**
- ✅ Todas as 8 funcionalidades principais implementadas
- ✅ Todas as validações de unicidade e período implementadas
- ✅ Sistema de fidelidade totalmente integrado
- ✅ Arquitetura modular e bem organizada
- ✅ Documentação completa de casos de teste
- ✅ 20 casos de teste executados e aprovados
