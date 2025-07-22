# --- Variáveis do Compilador ---
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# --- Variáveis do Projeto ---
# Nome do arquivo executável final
TARGET = scheduler
# Lista de todos os arquivos objeto (.o) necessários
OBJS = main.o broker.o client.o property.o

# --- Regras do Makefile ---

# Regra padrão: compila o executável final
all: $(TARGET)

# Regra para linkar os arquivos objeto e criar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regras de compilação para cada arquivo fonte

main.o: main.cpp broker.h client.h property.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

broker.o: broker.cpp broker.h property.h
	$(CXX) $(CXXFLAGS) -c broker.cpp -o broker.o

client.o: client.cpp client.h
	$(CXX) $(CXXFLAGS) -c client.cpp -o client.o

property.o: property.cpp property.h
	$(CXX) $(CXXFLAGS) -c property.cpp -o property.o

# Regra 'clean' para limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Declara que 'all' e 'clean' não são nomes de arquivos
.PHONY: all clean
