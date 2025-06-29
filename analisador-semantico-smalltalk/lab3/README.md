# Analisador Semântico para Smalltalk

Este projeto implementa um analisador semântico para um subconjunto da linguagem Smalltalk, seguindo as especificações do Lab 3. O analisador foi adaptado para trabalhar com a **gramática completa** do Smalltalk fornecida em `gramatica.conf`.

## Uso da Gramática Completa

**IMPORTANTE**: Este analisador **NÃO** utiliza uma gramática simplificada. Ele trabalha diretamente com a gramática completa especificada em `gramatica-smallTalk/gramatica.conf`, mas ignora estruturas desnecessárias para a análise semântica.

### Estruturas da Gramática Completa Utilizadas:
- `Crate -> Item_List`
- `Item -> Class_Definition | Statement TOKEN_period`
- `Method_Definition -> Message_Pattern TOKEN_left_bracket Temporaries_Opt Statement_Opt TOKEN_right_bracket`
- `Message_Pattern -> Unary_Pattern | Binary_Pattern | Keyword_Pattern`
- `Statement -> Return_Statement | Expression`
- `Expression -> Assignment | Basic_Expression`
- `Primary -> TOKEN_identifier | Literal | TOKEN_true | TOKEN_false | TOKEN_nil | ...`
- `Number_Literal -> TOKEN_decimal_integer | TOKEN_radix_integer | TOKEN_float | TOKEN_scaled_decimal`

### Estruturas Ignoradas (presentes na gramática, mas não processadas):
- `Message_Sequence`, `Cascaded_Messages` (cadeias complexas de mensagens)
- `Block_Constructor` (blocos/closures)
- `String_Literal`, `Character_Literal`, `Symbol_Literal`, `Array_Literal` (literais complexos)
- `Class_Definition` completa (foco apenas em métodos individuais)

## Adaptações para a Gramática Smalltalk

O analisador foi adaptado para extrair informações da árvore sintática gerada pela gramática real do Smalltalk:

### Estrutura da Árvore Sintática
- **No_arv_parse**: Utiliza os campos `simb` (símbolo), `regra`, `dado_extra` (lexema) e `filhos`
- **Extração de Métodos**: Busca por `Method_Definition` na árvore sintática
- **Padrões de Mensagem**: Suporta `Unary_Pattern`, `Binary_Pattern` e `Keyword_Pattern`

### Estruturas Suportadas da Gramática

#### Definição de Métodos
```smalltalk
soma: a with: b [
    | resultado |
    resultado := a + b.
    ^ resultado
]
```

#### Elementos Extraídos:
- **Message_Pattern**: Nome do método e parâmetros
- **Temporaries_Opt**: Variáveis locais (temporárias) 
- **Statement_Opt**: Comandos e expressões do método

### Mapeamento da Gramática

#### Method_Definition
```
Method_Definition -> Message_Pattern TOKEN_left_bracket Temporaries_Opt Statement_Opt TOKEN_right_bracket
```

#### Message_Pattern (Tipos de Métodos)
- **Unary_Pattern**: `TOKEN_identifier` (métodos sem parâmetros)
- **Binary_Pattern**: `TOKEN_binary_selector TOKEN_identifier` (operadores)
- **Keyword_Pattern**: `TOKEN_keyword TOKEN_identifier` (métodos com palavras-chave)

#### Temporaries (Variáveis Locais)
```
Temporaries -> TOKEN_pipe TOKEN_identifier Variable_List TOKEN_pipe
```

#### Statements (Comandos)
- **Assignment**: `Assignment_Target TOKEN_assignment_operator Expression`
- **Return_Statement**: `TOKEN_return_operator Expression`

#### Primary (Valores e Expressões)
- **TOKEN_identifier**: Variáveis
- **Literal**: Números, strings, etc.
- **TOKEN_true/TOKEN_false**: Valores booleanos
- **TOKEN_nil**: Valor nulo

## Tipos de Dados Suportados

### Tipos Básicos
- **Integer**: Números inteiros (`TOKEN_decimal_integer`)
- **Float**: Números de ponto flutuante (`TOKEN_float`)
- **Boolean**: Valores booleanos (`TOKEN_true`, `TOKEN_false`)
- **Object**: Tipo padrão para Smalltalk

### Verificação Semântica

O analisador realiza as seguintes verificações:

1. **Declaração de variáveis**: Verifica se todas as variáveis usadas foram declaradas
2. **Compatibilidade de tipos**: Verifica se os operadores são aplicados a tipos compatíveis
3. **Operações inválidas**: Detecta operações como `! ponto_flutuante`, `booleano < inteiro`, etc.

## Limitações e Simplificações

Para focar no subconjunto solicitado, algumas partes da gramática Smalltalk são simplificadas:

- **Message Sequences**: Por simplicidade, focamos em expressões básicas
- **Block Constructors**: Não implementados completamente
- **Arrays e Symbols**: Não implementados
- **Cascaded Messages**: Não implementados

## Exemplos de Uso

### Exemplo 1: Método com Palavra-chave
```smalltalk
soma: a with: b [
    | resultado |
    resultado := a + b.
    ^ resultado
]
```

### Exemplo 2: Método Unário
```smalltalk
valor [
    ^ 42
]
```

### Exemplo 3: Método Binário
```smalltalk
+ outro [
    ^ self valor + outro valor
]
```

## Compilação e Execução

1. **Compilar o projeto**:
   ```bash
   make
   ```

2. **Executar com um programa**:
   ```bash
   cd lab3
   ```
   ```bash
   ./bin/analisador ./gramatica-st/gramatica.conf ./gramatica-st/tabela_lr1.conf < entrada_exemplo.txt
   ```

## Saída

O programa imprime:
- Informações de debug sobre a análise sintática
- Estrutura do método extraído
- Resultado da verificação semântica
- O último valor atribuído na execução simulada

Para valores:
- **Integer**: Impresso como número inteiro
- **Float**: Impresso com 2 casas decimais
- **Boolean**: Impresso como "true" ou "false"

## Arquivos Principais Adaptados

### Extração da Árvore Sintática
- **Funcao.cpp**: Adaptado para extrair `Method_Definition` da gramática Smalltalk
- **Comando.cpp**: Adaptado para extrair `Statement` e `Assignment`
- **Expressao.cpp**: Adaptado para extrair `Primary`, `Literal` e `Basic_Expression`

### Classes de Expressões
- **ExpressaoInt.cpp**: Extrai `TOKEN_decimal_integer`
- **ExpressaoFloat.cpp**: Extrai `TOKEN_float`
- **ExpressaoBoolean.cpp**: Extrai `TOKEN_true` e `TOKEN_false`

### Estrutura de Dados
- **Arvore.hpp**: Define `No_arv_parse` com campos `simb`, `regra`, `dado_extra`
- **Tipo.hpp**: Sistema de tipos adaptado para Smalltalk

## Tratamento de Erros

O analisador detecta e reporta:
- Métodos não encontrados na árvore sintática
- Variáveis não declaradas nas temporárias
- Tipos incompatíveis em operações
- Erros de execução (como divisão por zero)
