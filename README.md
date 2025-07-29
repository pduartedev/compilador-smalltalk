# Compilador Smalltalk

> *"And we become night time dreamers*  
> *And street walkers, **small talk**ers*  
> *When we should be daydreamers*  
> *And moonwalkers and dream talkers"*  
> **- DayDreamer - Aurora**

## Visão Geral

Este projeto implementa um compilador completo para a linguagem Smalltalk, desenvolvido como parte da disciplina de Compiladores 2025. O compilador é construído em fases incrementais, seguindo a arquitetura clássica de compiladores com análise léxica, sintática e semântica.

## Estrutura do Projeto

```
compilador-smalltalk/
├── analisador-lexico-smalltalk/     # Fase 1: Análise Léxica
├── analisador-semantico-smalltalk/  # Fase 3: Análise Semântica
├── frames-smalltalk/                # Fase 4: Geração de Frames
│   ├── lab4/                        # Implementação completa do Lab 4
│   │   ├── src/                     # Código fonte C++
│   │   ├── gramatica-st/            # Gramática e tabela LR1
│   │   ├── entradas/                # Arquivos de teste
│   │   └── bin/                     # Executáveis
│   └── doc/                         # Documentação
└── README.md                        # Este arquivo
```

## Fases Implementadas

### 📖 Fase 1: Analisador Léxico

**Localização:** `analisador-lexico-smalltalk/`

O analisador léxico foi implementado utilizando JavaCC (Java Compiler Compiler) e é responsável por:

- **Tokenização completa** da linguagem Smalltalk
- **Reconhecimento de palavras reservadas**: `nil`, `true`, `false`, `self`, `super`
- **Identificação de literais**: números inteiros, floats, strings, caracteres
- **Detecção de operadores**: binários, atribuição, retorno
- **Análise de símbolos especiais**: colchetes, parênteses, chaves, pontuação

#### Tokens Suportados:
- Identificadores e palavras-chave
- Números (decimal, radix, float, scaled decimal)
- Strings e caracteres quotados
- Seletores e operadores binários
- Símbolos de pontuação e delimitadores

#### Como usar:
```bash
cd analisador-lexico-smalltalk/
./scripts/compile.sh
./scripts/run.sh samples/exemploC.st
```

### 🔍 Fase 2: Analisador Sintático

**Localização:** `analisador-sintatico-smalltalk/`

O analisador sintático implementa um parser LR(1) para Smalltalk, composto por:

#### Definição Gramatical (`lab2/`)
- **Gramática formal** baseada no ANSI Smalltalk Standard
- **Estruturas suportadas**:
  - Definições de classe e métodos
  - Padrões de mensagem (unária, binária, palavra-chave)
  - Instruções e expressões
  - Literais e estruturas de bloco
  - Precedência de operadores

#### Parser LR(1) (`parserLR/`)
- **Tabela LR(1)** para análise sintática
- **Estruturas de dados** para representação da gramática
- **Engine de parsing** com suporte a:
  - Operações shift/reduce
  - Detecção de conflitos
  - Tratamento de erros sintáticos

#### Características da Gramática:
- Símbolos não-terminais em "camelCase"
- Suporte a estruturas opcionais (`?`)
- Operadores Kleene (`*`, `+`)
- Precedência de mensagens: Unária > Binária > Palavra-chave

### 🧠 Fase 3: Análise Semântica

**Localização:** `analisador-semantico-smalltalk/`

A análise semântica implementa verificação de tipos e contexto para Smalltalk.

### 🎯 Fase 4: Geração de Frames (LAB 4)

**Localização:** `frames-smalltalk/lab4/`

A geração de frames implementa um sistema completo de análise de alocação de memória para funções Smalltalk, incluindo:

#### Características Principais:
- **Análise de múltiplas funções** simultaneamente
- **Sistema de frames** com header de 40 bytes
- **Alocação inteligente** de variáveis (frame vs pseudo-registradores)
- **Regra artificial** para otimização de alocação
- **Suporte completo** a chamadas de função com parâmetros

#### Funcionalidades Implementadas:
- **FrameFuncao**: Objeto principal com todos os campos obrigatórios
- **FrameAcesso**: Sistema polimórfico para acesso a variáveis
- **Análise de parâmetros**: Detecção automática de entrada e saída
- **Mapeamento de memória**: Endereçamento preciso (FP+offset, FP-offset)
- **Relatórios detalhados**: Informações completas sobre uso de memória

#### Regras de Alocação:
- **Frame header**: 40 bytes para organização interna
- **Parâmetros**: Posicionados no frame anterior (FP+8, FP+16, ...)
- **Variáveis**: Alocadas após header (FP-40, FP-48, ...)
- **Regra artificial**: Variáveis em parâmetros de chamadas → frame
- **Outras variáveis**: Pseudo-registradores (T1, T2, T3, ...)

#### Estrutura de Dados:
```cpp
class FrameFuncao {
    int tamanho_frame;           // Total de bytes necessários
    int n_param_entrada;         // Número de parâmetros de entrada
    int n_maximo_param_saida;    // Máximo de parâmetros de saída
    int n_pseudo_registradores;  // Total de pseudo-registradores
    int n_variaveis_no_frame;    // Variáveis armazenadas no frame
};
```

## Exemplos de Código Suportado

O compilador consegue processar código Smalltalk complexo, incluindo:

### Definição de Classes:
```smalltalk
Object subclass: Ponto [
    | x y |
    
    x: valorX y: valorY [
        x := valorX.
        y := valorY.
        ^self
    ]
]
```

### Estruturas de Controle:
```smalltalk
n <= 0 ifTrue: [
    ^1.0
].

[ i >= 1 ] whileTrue: [
    temp := ((v at: i) y * (v at: i) x) \\ 123.
    i := i - 1
].
```

### Expressões Complexas:
```smalltalk
res := res + (res * 0.3e3 + (self func: v n: (n - 2)) * temp).
```

## Arquitetura Técnica

### Tecnologias Utilizadas:
- **JavaCC**: Geração do analisador léxico
- **C++20**: Implementação do parser LR(1) e sistema de frames
- **Bash**: Scripts de automação
- **Make**: Sistema de compilação

### Padrões de Design:
- **Separação de responsabilidades** entre fases
- **Modularização** em componentes independentes
- **Reutilização** de estruturas entre fases
- **Polimorfismo** para sistema de acesso a variáveis
- **Análise semântica** integrada ao sistema de frames

## Como Executar

### Pré-requisitos:
- Java 8+
- JavaCC
- G++ com suporte a C++20
- Bash
- Make

### Execução Completa:
```bash
# Fase 1: Análise Léxica
cd analisador-lexico-smalltalk/
./scripts/compile.sh
./scripts/run.sh samples/exemploC.st

# Fase 2: Análise Sintática
cd ../analisador-sintatico-smalltalk/parserLR/
make
./parser < ../lab2/adaptacoes-lab-1/exemploC.st

# Fase 4: Geração de Frames (LAB 4)
cd ../../frames-smalltalk/lab4/
make
./bin/analisador gramatica-st/gramatica.conf gramatica-st/tabela_lr1.conf < entradas/entrada_teste_regra.txt
```

### Exemplos de Saída do LAB 4:
```
=== ENCONTRADAS 2 FUNÇÕES ===

=== PROCESSANDO FUNÇÃO 1 ===
=== INFORMAÇÕES DO FRAME ===
Tamanho total do frame: 56 bytes
Número de parâmetros de entrada: 1
Número máximo de parâmetros de saída: 2
Número de pseudo-registradores: 0
Número de variáveis no frame: 2

=== MAPEAMENTO DE VARIÁVEIS ===
Parâmetros de entrada:
  x: FP+8
Variáveis locais:
  resultado: FP-40 (no frame)
  temp: FP-48 (no frame)
```

## Roadmap Futuro

### 🔮 Próximas Fases:
- **✅ FRAMES (LAB 4)**: ✅ **CONCLUÍDO** - Sistema completo de geração de frames com alocação inteligente de variáveis
- **Geração de Código**: Conversão para linguagem assembly/máquina
- **Otimizações**: Análise de fluxo de dados e otimizações de código
- **Debugging**: Sistema de depuração integrado
- **IDE Integration**: Plugin para editores/IDEs

### 🏆 Conquistas do LAB 4:
- ✅ **Análise de múltiplas funções** simultaneamente
- ✅ **Sistema de frames** com alocação automática (40+ bytes)
- ✅ **Regra artificial** implementada e funcionando
- ✅ **Polimorfismo** para acesso a variáveis (Frame vs Pseudo-registradores)
- ✅ **Relatórios detalhados** de uso de memória
- ✅ **Parsing completo** de chamadas de função com parâmetros
- ✅ **100% conformidade** com especificações do enunciado

## Autor

**Patrick Duarte Pimenta**  
Disciplina: Compiladores 2025  
Universidade: IFNMG - Campus Montes Claros

---

> *"Like dreamwalkers navigating through the syntax trees of imagination, we build compilers that transform human thoughts into machine understanding."*
