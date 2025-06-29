CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

# Diretórios
SRC_DIR = src
GRAM_DIR = $(SRC_DIR)/src-gram-st
BIN_DIR = bin

# Arquivos fonte
MAIN_SOURCES = $(SRC_DIR)/sol.cpp \
               $(SRC_DIR)/Arvore.cpp \
               $(SRC_DIR)/Gramatica.cpp \
               $(SRC_DIR)/Parser.cpp \
               $(SRC_DIR)/TabelaLR1.cpp \
               $(SRC_DIR)/matriz-util.cpp \
               $(SRC_DIR)/debug-util.cpp

GRAM_SOURCES = $(GRAM_DIR)/Analisador.cpp \
               $(GRAM_DIR)/Comando.cpp \
               $(GRAM_DIR)/ComandoAtribuicao.cpp \
               $(GRAM_DIR)/ComandoLista.cpp \
               $(GRAM_DIR)/ComandoIf.cpp \
               $(GRAM_DIR)/ComandoWhile.cpp \
               $(GRAM_DIR)/Expressao.cpp \
               $(GRAM_DIR)/ExpressaoBoolean.cpp \
               $(GRAM_DIR)/ExpressaoFloat.cpp \
               $(GRAM_DIR)/ExpressaoInt.cpp \
               $(GRAM_DIR)/ExpressaoLogica.cpp \
               $(GRAM_DIR)/ExpressaoRelacional.cpp \
               $(GRAM_DIR)/ExpressaoCondicional.cpp \
               $(GRAM_DIR)/ExpressaoNumero.cpp \
               $(GRAM_DIR)/ExpressaoVariavel.cpp \
               $(GRAM_DIR)/ExpressaoSoma.cpp \
               $(GRAM_DIR)/ExpressaoSubtracao.cpp \
               $(GRAM_DIR)/ExpressaoMultiplicacao.cpp \
               $(GRAM_DIR)/ExpressaoDivisao.cpp \
               $(GRAM_DIR)/ExpressaoMod.cpp \
               $(GRAM_DIR)/ExpressaoBinaria.cpp \
               $(GRAM_DIR)/ExpressaoSelf.cpp \
               $(GRAM_DIR)/Funcao.cpp \
               $(GRAM_DIR)/ID.cpp \
               $(GRAM_DIR)/NUM.cpp \
               $(GRAM_DIR)/Tipo.cpp \
               $(GRAM_DIR)/Variavel.cpp

ALL_SOURCES = $(MAIN_SOURCES) $(GRAM_SOURCES)

# Arquivo executável
TARGET = $(BIN_DIR)/analisador

# Regra padrão
all: $(TARGET)

# Criar diretório bin se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compilar o executável
$(TARGET): $(ALL_SOURCES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Limpar arquivos compilados
clean:
	rm -rf $(BIN_DIR)
