# Compilador Smalltalk

> *"And we become night time dreamers*  
> *And street walkers, **small talkers***  
> *When we should be daydreamers*  
> *And moonwalkers and dream talkers"*  
> **- DayDreamer - Aurora**

## Visão Geral

Este projeto implementa um compilador completo para a linguagem Smalltalk, desenvolvido como parte da disciplina de Compiladores 2025. O compilador é construído em fases incrementais, seguindo a arquitetura clássica de compiladores com análise léxica, sintática e semântica.

## Estrutura do Projeto

```
compilador-smalltalk/
├── analisador-lexico-smalltalk/     # Fase 1: Análise Léxica
├── analisador-sintatico-smalltalk/  # Fase 2: Análise Sintática
│   ├── lab2/                        # Definições gramaticais
│   └── parserLR/                    # Parser LR(1)
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
- **C++**: Implementação do parser LR(1)
- **Bash**: Scripts de automação

### Padrões de Design:
- **Separação de responsabilidades** entre fases
- **Modularização** em componentes independentes
- **Reutilização** de estruturas entre fases

## Como Executar

### Pré-requisitos:
- Java 8+
- JavaCC
- G++ (para compilação do parser)
- Bash

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
```

## Roadmap Futuro

### 🔮 Próximas Fases:
- **FRAMES**:
- ...

## Autor

**Patrick Duarte Pimenta**  
Disciplina: Compiladores 2025  
Universidade: IFNMG - Campus Montes Claros

---

> *"Like dreamwalkers navigating through the syntax trees of imagination, we build compilers that transform human thoughts into machine understanding."*
