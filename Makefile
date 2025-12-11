# Makefile para o Sistema de Gerenciamento do Hotel Descanso Garantido

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Nome do executável
TARGET = hotel

# Arquivos fonte e objetos
SOURCES = main.c cliente.c funcionario.c quarto.c estadia.c fidelidade.c
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão
all: $(TARGET)

# Compilar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Compilação concluída! Execute com: ./$(TARGET)"

# Compilar arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos compilados e dados
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f *.dat
	@echo "Arquivos limpos!"

# Limpar apenas arquivos compilados (manter dados)
clean-build:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Arquivos de compilação removidos!"

.PHONY: all run clean clean-build
