# Makefile para o projeto Hotel Descanso Garantido

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = 

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TARGET = $(BUILD_DIR)/hotel

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(TARGET)

# Cria o diretório de build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra para compilar o executável final
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Regra para compilar os arquivos .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -rf $(BUILD_DIR) *.dat

# Executa o programa
run: all
	./$(TARGET)
