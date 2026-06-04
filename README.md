# Compilador Smalltalk

> *"And we become night time dreamers*  
> *And street walkers, **small talk**ers*  
> *When we should be daydreamers*  
> *And moonwalkers and dream talkers"*  
> **- DayDreamer - Aurora**

## 🚀 Visão Geral

Este projeto implementa um protótipo de **compilador para a linguagem Smalltalk**, desenvolvido como parte da disciplina de Compiladores 2025. O compilador segue a arquitetura clássica com análise léxica, sintática e semântica, incluindo **geração de frames automática**, **representação intermediária** e **pipeline de compilação totalmente automatizado**.

**obs: Para fins de estudos, se você deseja montar um compilador de SmallTalk, o analisador léxico, sintático e semântico foram avaliados em nota máxima (100%) pelo professor, enquanto os laboratórios posteriores, de frames e representação intermediária EXIGEM alterações. Portanto, não se baseiem neles. Futuramente irei corrigir-los.**

## 📁 Estrutura do Projeto

```
compilador-smalltalk/
├── src/                           # Código fonte principal
│   ├── lexico-st/                 # 🔤 Analisador Léxico (JavaCC)
│   │   ├── main/jj/               # Gramática JavaCC (LAB 1)
│   │   ├── scripts/               # Scripts de compilação/execução
│   │   └── target/classes/        # Classes Java compiladas
│   ├── semantico-st/              # 🧠 Analisador Semântico C++ (LAB 3)
│   │   ├── src-gram-st/           # AST e comandos (LAB 2)
│   │   ├── frame-st/              # Sistema de frames (LAB 4)
│   │   ├── tree-st/               # Representação intermediária (LAB 5)
│   │   └── *.cpp                  # Parser LR1, tabelas, etc.
│   └── gramatica-st/              # 📋 Gramática e tabela LR1
├── ins-st/                        # 📝 Programas Smalltalk (30 arquivos)
├── ins-tokens-st/                 # 🎯 Tokens gerados
├── doc/                           # Enunciados e PDF de apoio
├── bin/                           # 🔧 Executáveis compilados
├── Makefile                       # 🤖 Pipeline automatizado
└── README.md                      # 📖 Este arquivo
```

## ⚡ Quick Start - Pipeline Automatizado

### 1️⃣ Setup Inicial (Execute uma vez)
```bash
make setup
```

### 2️⃣ Compilar um arquivo específico
```bash
make compile-1    # Compila 1.smalltalk
make compile-10   # Compila 10.smalltalk
make compile-N    # Compila N.smalltalk (1-30)
```

### 3️⃣ Compilar em lote
```bash
make compile-batch-5   # Compila arquivos 1-5
make compile-batch-10  # Compila arquivos 1-10
make compile-all       # Compila todos os 30 arquivos
```

### 4️⃣ Comandos auxiliares
```bash
make tokens-N     # Só gera tokens do arquivo N
make semantic-N   # Só análise semântica do arquivo N
make help         # Mostra todos os comandos
```

## 🎯 Funcionalidades Implementadas

### 🔤 Análise Léxica (JavaCC)
- ✅ Tokenização completa da linguagem Smalltalk
- ✅ Reconhecimento de 40+ tipos de tokens
- ✅ Suporte a números, strings, símbolos, operadores
- ✅ Integração automática com pipeline

### 🔍 Análise Sintática (LR1)
- ✅ Parser LR1 completo com 142 estados
- ✅ Gramática Smalltalk com 108 regras de produção
- ✅ AST (Árvore Sintática Abstrata) completa
- ✅ Detecção e tratamento de erros sintáticos

### 🧠 Análise Semântica + Geração de Frames
- ✅ **Sistema de tipos**: Object, Integer, Float, Boolean
- ✅ **Inferência de tipos automática**
- ✅ **Análise de escopo** e declaração de variáveis
- ✅ **Geração de frames** (Lab 4 completo):
  - Alocação de parâmetros e variáveis locais
  - Cálculo automático de tamanho de frames
  - Mapeamento de pseudo-registradores
  - Suporte a recursão e chamadas de função

### 🔥 Representação Intermediária (Lab 5)
- ✅ **Conversão AST → IR** baseada no Capítulo 7 de Appel
- ✅ **Árvore IR completa** com statements e expressions
- ✅ **Expressões booleanas** em lugar de comparadores relacionais
- ✅ **Estruturas IR implementadas**:
  - `SEQ` (sequências de statements)
  - `MOVE` (atribuições)
  - `BINOP` (operações binárias)
  - `CALL` (chamadas de função)
  - `CONST` (constantes)
  - `TEMP` (temporários)
  - `MEM` (acesso à memória)

### 🎮 Sistema de Execução
- ✅ **Avaliação de expressões** com precedência correta
- ✅ **Associatividade esquerda-direita** (padrão Smalltalk)
- ✅ **Controle de fluxo**: `ifTrue:`, `ifFalse:`
- ✅ **Chamadas de função** e recursão
- ✅ **Retorno de valores** tipados

## 📊 Exemplos de Funcionamento

### Exemplo 1: Expressão Matemática
```smalltalk
Object subclass: MinhaClasse [
    f [
        | a b c d |
        a := 10.
        b := 25.
        c := 17.
        d := b * b - 4 * a * c.
        ^d
    ]
]
```
**Resultado**: `105570` (associatividade esquerda-direita)

**Representação Intermediária gerada**:
```
SEQ(
  MOVE(a, 10),
  MOVE(b, 25),
  MOVE(c, 17),
  MOVE(d, BINOP(*, BINOP(*, BINOP(-, BINOP(*, b, b), 4), a), c)),
  MOVE(__return__, d)
)
```

### Exemplo 2: Função Recursiva (Fatorial)
```smalltalk
Object subclass: MinhaClasse [
    fact: n [
        n <= 1 ifTrue: [ ^1 ].
        ^n * (self fact: n - 1)
    ]
]
```
**Frame gerado**: 40 bytes, 1 parâmetro (`n` em FP+8), variáveis temporárias automáticas

**Representação Intermediária gerada**:
```
SEQ(
  MOVE(__temp__, BINOP(<=, n, 1)),
  MOVE(__return__, BINOP(*, n, CALL(fact:, n)))
)
```

## 🔧 Comandos do Makefile

| Comando | Descrição |
|---------|-----------|
| `make setup` | 🚀 Configuração inicial do projeto |
| `make compile-N` | 🎯 Compila arquivo N.smalltalk (1-30) |
| `make compile-batch-5` | 📦 Compila arquivos 1-5 |
| `make compile-batch-10` | 📦 Compila arquivos 1-10 |
| `make compile-all` | 📦 Compila todos os 30 arquivos |
| `make tokens-N` | 🔤 Só análise léxica do arquivo N |
| `make semantic-N` | 🧠 Só análise semântica do arquivo N |
| `make clean` | 🧹 Limpa binários |
| `make clean-tokens` | 🧹 Limpa tokens |
| `make help` | ❓ Mostra ajuda |

## 🏗️ Arquitetura Técnica

### Stack Tecnológico
- **🔤 JavaCC**: Geração automática do analisador léxico
- **🧠 C++20**: Parser LR1, análise semântica, frames e IR
- **📋 Make**: Sistema de build automatizado
- **🔧 Bash**: Scripts de automação e orquestração

### Pipeline de Compilação
```
📝 arquivo.smalltalk
    ↓ 🔤 Análise Léxica (JavaCC)
🎯 arquivo.tokens
    ↓ 🔍 Análise Sintática (Parser LR1)
🌳 AST (Árvore Sintática)
    ↓ 🧠 Análise Semântica + Frames
📊 Código analisado + informações de frame
    ↓ 🔥 Representação Intermediária (Lab 5)
🎯 Árvore IR baseada em Appel
```

## 📊 Estatísticas do Projeto

### Análise Léxica
- 🎯 **40+ tipos de tokens** suportados
- 🔤 **Literais**: números, strings, caracteres, símbolos
- ⚙️ **Operadores**: binários, unários, atribuição, retorno

### Análise Sintática
- 🔍 **142 estados LR1** na tabela de parsing
- 📋 **108 regras de produção** na gramática
- 🌳 **AST completa** com todos os nós sintáticos

### Análise Semântica
- 🧠 **4 tipos básicos**: Object, Integer, Float, Boolean
- 🔄 **Inferência automática** de tipos
- 📍 **Análise de escopo** completa
- 🎯 **30 programas de teste** incluídos

### Geração de Frames (Lab 4)
- 💾 **Frame header**: 40 bytes padrão
- 📝 **Mapeamento automático** de variáveis
- 🔧 **Pseudo-registradores**: T1, T2, T3...
- 📊 **Relatórios detalhados** de alocação

### Representação Intermediária (Lab 5)
- 🔥 **Conversão completa** AST → IR
- 🌳 **Árvore IR** baseada no Capítulo 7 de Appel
- 🎯 **Estruturas implementadas**: SEQ, MOVE, BINOP, CALL, CONST, TEMP, MEM
- ✅ **Expressões booleanas** substituindo comparadores

## 📚 Documentação Detalhada

### Lab 4 - Sistema de Frames Completo
O Lab 4 implementa um sistema sofisticado de análise e geração de frames para funções Smalltalk:

#### 🎯 Funcionalidades Principais
1. **Análise Multi-Função**: Processa múltiplas funções simultaneamente
2. **Frame Header**: 40 bytes de header organizacional automático
3. **Alocação Inteligente**: Decisão automática frame vs pseudo-registradores
4. **Mapeamento Preciso**: Endereçamento exato com offsets (FP+N, FP-N)

#### 📋 Regras de Alocação
- **Parâmetros de entrada**: Frame anterior (FP+8, FP+16, FP+24...)
- **Variáveis locais**: Frame atual após header (FP-40, FP-48...)
- **Regra artificial**: Variáveis em parâmetros de chamadas → frame obrigatório
- **Outras variáveis**: Pseudo-registradores para otimização

#### 🔧 Classes Principais
```cpp
// Sistema principal de frame
class FrameFuncao {
    int tamanho_frame;           // Bytes totais necessários
    int n_param_entrada;         // Parâmetros de entrada
    int n_maximo_param_saida;    // Máximo parâmetros de saída
    int n_pseudo_registradores;  // Total pseudo-registradores
    int n_variaveis_no_frame;    // Variáveis no frame
    map<string, FrameAcesso*> variaveis; // Mapeamento variáveis
};

// Sistema polimórfico de acesso
class FrameAcesso { /* classe base */ };
class FrameAcessoNoFrame : public FrameAcesso { /* pseudo-reg */ };
class FrameAcessoTemp : public FrameAcesso { /* temporárias */ };
```

### Lab 5 - Representação Intermediária Completa
O Lab 5 implementa conversão de AST para representação intermediária seguindo o Capítulo 7 de Appel:

#### 🎯 Funcionalidades Principais
1. **Conversão AST → IR**: Transformação completa da árvore sintática
2. **Expressões Booleanas**: Substituição de comparadores relacionais
3. **Árvore IR Tipada**: Statements e expressions com tipos específicos
4. **Suporte Completo**: Atribuições, operações, chamadas, condicionais

#### 🔧 Classes IR Implementadas
```cpp
// Base classes
class Stm { /* base para statements */ };
class Exp { /* base para expressions */ };

// Statements
class StmSeq : public Stm { /* sequências */ };
class StmMove : public Stm { /* atribuições */ };
class StmCJump : public Stm { /* jumps condicionais */ };
class StmLabel : public Stm { /* labels */ };

// Expressions
class ExpTemp : public Exp { /* temporários */ };
class ExpConst : public Exp { /* constantes */ };
class ExpBinop : public Exp { /* operações binárias */ };
class ExpCall : public Exp { /* chamadas de função */ };
class ExpMem : public Exp { /* acesso à memória */ };
```

## 🧪 Casos de Teste

### Programa 1: Expressão Matemática
```smalltalk
Object subclass: MinhaClasse [
    f [
        | a b c d |
        a := 10.
        b := 25.
        c := 17.
        d := b * b - 4 * a * c.
        ^d
    ]
]
```
**Resultado esperado**: `105570` (associatividade esquerda-direita)

### Programa 5: Condicional com ifTrue
```smalltalk
Object subclass: MinhaClasse [
    F5 [
        | x y |
        x := 5.
        y := 0.
        x > 2 ifTrue: [ y := 1 ]
    ]
]
```
**IR gerada**: Conversão de condicionais para expressões booleanas

### Programa 10: Função Recursiva (Fatorial)
```smalltalk
Object subclass: MinhaClasse [
    fact: n [
        n <= 1 ifTrue: [ ^1 ].
        ^n * (self fact: n - 1)
    ]
]
```
**Frame gerado**: 40 bytes, 1 parâmetro (`n` em FP+8), variáveis temporárias automáticas

## 🎯 Como Executar - Guia Completo

### Primeira Execução
```bash
# 1. Clone e navegue para o diretório
cd /caminho/para/compilador-smalltalk

# 2. Execute setup inicial (só uma vez)
make setup

# 3. Teste com um arquivo
make compile-1
```

### Uso Diário
```bash
# Compilar arquivo específico
make compile-10

# Compilar vários arquivos
make compile-batch-5

# Visualizar apenas tokens
make tokens-15

# Visualizar apenas análise semântica  
make semantic-15
```

### Verificação e Limpeza
```bash
# Ver todos os comandos disponíveis
make help

# Limpar arquivos compilados
make clean

# Limpar tokens gerados
make clean-tokens

# Limpar tudo
make clean-all
```

## 📋 Pré-requisitos

- **☕ Java 8+**: Para compilação do analisador léxico (JavaCC)
- **🔧 GCC/Clang**: Compilador C++20 para análise semântica
- **🐧 Make**: Sistema de build (disponível em Linux/macOS)
- **📁 Bash**: Shell script para automação

## 👥 Equipe de Desenvolvimento

- **Desenvolvimento**: Implementação completa do compilador Smalltalk
- **Arquitetura**: Pipeline automatizado, sistema de frames e IR
- **Testes**: 30 programas de teste cobrindo todas as funcionalidades

## 📝 Notas de Implementação

### Associatividade Smalltalk
O compilador implementa corretamente a associatividade **esquerda-para-direita** dos operadores binários em Smalltalk:

```smalltalk
# Expressão: a * b - c * d
# Avaliação: ((a * b) - c) * d  (não a * b - (c * d))
```

### Sistema de Tipos
- **Object**: Tipo base universal
- **Integer**: Números inteiros com operações aritméticas
- **Float**: Números com ponto flutuante
- **Boolean**: Valores lógicos (true/false)

### Inferência Automática
O compilador realiza inferência de tipos automática baseada em:
- Literais numéricos (1 → Integer, 1.5 → Float)
- Operações aritméticas (+ → Integer/Float)
- Operações relacionais (<= → Boolean)
- Chamadas de função (baseado no tipo de retorno)

### Representação Intermediária
- Baseada no **Capítulo 7 de Appel** (Modern Compiler Implementation)
- **Expressões booleanas** substituem comparadores relacionais
- **Árvore IR tipada** com statements e expressions
- **Conversão completa** de AST para IR

## Autor
- **Patrick Duarte Pimenta**  
- Disciplina: Compiladores 2025  
- Universidade: IFNMG - Campus Montes Claros

---

> *"Like dreamwalkers navigating through the syntax trees of imagination, we build compilers that transform human thoughts into machine understanding."*
