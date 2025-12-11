# Makefile para o Sistema de Gerenciamento do Hotel Descanso Garantido

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Nome do executável
TARGET = hotel

# Arquivo fonte
SOURCE = hotel.c

# Regra padrão
all: $(TARGET)

# Compilar o executável
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compilação concluída! Execute com: ./$(TARGET)"

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos compilados e dados
clean:
	rm -f $(TARGET)
	rm -f *.dat
	@echo "Arquivos limpos!"

# Limpar apenas arquivos compilados (manter dados)
clean-build:
	rm -f $(TARGET)
	@echo "Executável removido!"

.PHONY: all run clean clean-build
