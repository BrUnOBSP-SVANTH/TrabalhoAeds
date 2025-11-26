# TP AED I / FES - Hotel Descanso Garantido

**Alunos:**
* Bruno da Silva de Paulo
* João Pedro Bandeira Ribas
* Gabriel de Sousa Carvalho Ferreira

## Descrição do Projeto

Este projeto implementa um sistema de gerenciamento para o "Hotel Descanso Garantido" em linguagem C, conforme os requisitos do Trabalho Prático das disciplinas de Algoritmos e Estruturas de Dados I (AED I) e Fundamentos de Engenharia de Software (FES) da PUC Minas.

O sistema utiliza **arquivos binários** para persistência de dados (acesso direto), seguindo a exigência do trabalho.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
hotel_descanso_garantido/
├── include/
│   └── hotel.h         # Definições de estruturas (structs) e protótipos de funções.
├── src/
│   ├── main.c          # Função principal (main) e o loop do menu.
│   └── hotel.c         # Implementação de todas as funções do sistema.
└── Makefile            # Script para compilação e execução simplificada.
```

## Funcionalidades Implementadas

O sistema atende aos seguintes requisitos:

1.  **Cadastro de Cliente:** Código, nome, endereço, telefone. (Com geração automática de código e validação de unicidade).
2.  **Cadastro de Funcionário:** Código, nome, telefone, cargo, salário. (Com geração automática de código e validação de unicidade).
3.  **Cadastro de Quarto:** Número, quantidade de hóspedes, valor da diária, status ("ocupado" ou "desocupado"). (Com validação de unicidade do número).
4.  **Cadastro de Estadia:** Código, data de entrada/saída, código do cliente, número do quarto. (Com cálculo de diárias, validação de cliente existente e busca de quarto disponível).
5.  **Baixa em Estadia:** Calcula e mostra o valor total a ser pago e altera o status do quarto para "desocupado".
6.  **Pesquisa:** Permite pesquisar clientes e funcionários por código ou por nome.
7.  **Estadias de Cliente:** Mostra todas as estadias de um determinado cliente.
8.  **Pontos de Fidelidade:** Calcula a quantidade de pontos (10 pontos por diária).

## Como Compilar e Executar

**Pré-requisitos:**
É necessário ter o compilador GCC (ou similar) e o utilitário `make` instalados no seu sistema.

### 1. Compilação

Navegue até o diretório raiz do projeto (`hotel_descanso_garantido`) e execute o `make`:

```bash
cd hotel_descanso_garantido
make all
```

Isso criará o executável `hotel` dentro do diretório `build/`.

### 2. Execução

Após a compilação, execute o programa com o comando:

```bash
make run
```

Ou diretamente:

```bash
./build/hotel
```

Os arquivos de dados (`clientes.dat`, `funcionarios.dat`, `quartos.dat`, `estadias.dat`) serão criados automaticamente na primeira execução.

### 3. Limpeza

Para remover os arquivos de objeto, o executável e os arquivos de dados, use:

```bash
make clean
```
