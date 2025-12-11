# TP AED I / FES - Hotel Descanso Garantido

**Alunos:**
* Bruno da Silva de Paulo
* João Pedro Bandeira Ribas
* Gabriel de Sousa Carvalho Ferreira

## Descrição do Projeto

Este projeto implementa um sistema de gerenciamento para o "Hotel Descanso Garantido" em linguagem C, conforme os requisitos do Trabalho Prático das disciplinas de Algoritmos e Estruturas de Dados I (AED I) e Fundamentos de Engenharia de Software (FES) da PUC Minas.

O sistema utiliza **arquivos binários** para persistência de dados (acesso direto), seguindo a exigência do trabalho.

## Estrutura do Projeto

O projeto está organizado em um único arquivo fonte:

```
TrabalhoAeds/
├── hotel.c             # Código-fonte completo do sistema
├── Makefile            # Script para compilação e execução
└── DOCUMENTACAO/       # Documentação do projeto
    ├── Backlog_e_Sprints.md
    └── Casos_de_Teste_e_Relatorio.md
```

## Funcionalidades Implementadas

O sistema atende aos seguintes requisitos:

1.  **Cadastro de Cliente:** Código, nome, endereço, telefone e pontos de fidelidade. (Com geração automática de código e validação de unicidade).
2.  **Cadastro de Funcionário:** Código, nome, telefone, cargo e salário. (Com geração automática de código e validação de unicidade).
3.  **Cadastro de Quarto:** Número, quantidade de hóspedes, valor da diária e status ("ocupado" ou "desocupado"). (Com validação de unicidade do número).
4.  **Cadastro de Estadia:** Código, data de entrada/saída, código do cliente, número do quarto. (Com cálculo automático de diárias, validação de cliente existente e verificação de disponibilidade do quarto nas datas solicitadas).
5.  **Baixa em Estadia:** Calcula e mostra o valor total a ser pago, altera o status do quarto para "desocupado" e adiciona pontos de fidelidade ao cliente (10 pontos por diária).
6.  **Pesquisa:** Permite pesquisar clientes e funcionários por código ou por nome (case-insensitive).
7.  **Estadias de Cliente:** Mostra todas as estadias de um determinado cliente e seus pontos de fidelidade acumulados.
8.  **Pontos de Fidelidade:** Sistema integrado que calcula e armazena automaticamente 10 pontos por diária ao dar baixa em uma estadia.

## Arquivos de Dados

O sistema gera automaticamente os seguintes arquivos binários para persistência:

- `clientes.dat` - Armazena dados dos clientes
- `funcionarios.dat` - Armazena dados dos funcionários
- `quartos.dat` - Armazena dados dos quartos
- `estadias.dat` - Armazena dados das estadias

## Como Compilar e Executar

**Pré-requisitos:**
É necessário ter o compilador GCC (ou similar) e o utilitário `make` instalados no seu sistema.

### 1. Compilação

Navegue até o diretório raiz do projeto e execute o `make`:

```bash
cd TrabalhoAeds
make all
```

Isso criará o executável `hotel` no diretório atual.

### 2. Execução

Após a compilação, execute o programa com o comando:

```bash
make run
```

Ou diretamente:

```bash
./hotel
```

Os arquivos de dados serão criados automaticamente na primeira execução.

### 3. Limpeza

Para remover o executável e os arquivos de dados, use:

```bash
make clean
```

Para remover apenas o executável (mantendo os dados):

```bash
make clean-build
```

## Menu do Sistema

O sistema oferece um menu interativo com as seguintes opções:

1. Cadastrar Cliente
2. Pesquisar Cliente
3. Cadastrar Funcionário
4. Pesquisar Funcionário
5. Cadastrar Quarto
6. Listar Quartos
7. Cadastrar Estadia
8. Dar Baixa em Estadia
9. Listar Estadias de um Cliente
0. Sair

## Destaques da Implementação

- **Código Unificado:** Todo o sistema implementado em um único arquivo `hotel.c` para facilidade de distribuição e compilação
- **Persistência de Dados:** Uso de arquivos binários com funções de carregar/salvar para cada módulo
- **Validação de Disponibilidade:** O sistema verifica conflitos de datas ao cadastrar estadias, evitando dupla reserva
- **Geração Automática de Códigos:** Códigos únicos são gerados automaticamente para clientes, funcionários e estadias
- **Sistema de Fidelidade Integrado:** Pontos são calculados e armazenados automaticamente (10 pontos por diária)
- **Pesquisa Flexível:** Busca por código ou nome (case-insensitive) para clientes e funcionários
- **Cálculo Automático de Diárias:** Utiliza funções de tempo da biblioteca padrão C para calcular diferença entre datas
