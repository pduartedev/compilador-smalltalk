# Analisador Léxico para Smalltalk

Este projeto implementa um analisador léxico para a linguagem Smalltalk utilizando JavaCC (Java Compiler Compiler) para o LABORATÓRIO 1 DA DISCIPLINA DE COMPILADORES 2025. O analisador identifica todos os tokens padrão da linguagem Smalltalk conforme a especificação fornecida.

## Estrutura do Projeto

```
/

├── doc/ # Documentação e enunciado do projeto
├── output/ # Saída gerada pelo analisador
├── samples/ # Exemplos de código Smalltalk para testes
├── scripts/ # Scripts para compilação e execução 
│   ├── compile.sh
│   └── run.sh
├── src/
│   └── main/
│       ├── jj/
│       │   └── SmallTalk.jj # Definição do analisador léxico em JavaCC
|       └── java/
|           └── lexical/ # Arquivos Java gerados pelo JavaCC
|
└── README.md                     # Arquivo README
``` 

## Tokens Reconhecidos

O analisador léxico reconhece os seguintes tipos de tokens:

- **NIL, TRUE, FALSE, SELF, SUPER**: Palavras reservadas 
- **IDENTIFIER**: Identificadores (variáveis, nomes de classes)
- **KEYWORD**: Identificadores seguidos de dois-pontos (ex: `at:`, `put:`)
- **DECIMAL_INTEGER**: Números inteiros decimais (ex: `42`)
- **RADIX_INTEGER**: Números inteiros em outras bases (ex: `16r2A`)
- **FLOAT**: Números de ponto flutuante (ex: `3.14159`, `3.14e2`)
- **SCALED_DECIMAL**: Decimais com escala definida (ex: `123s2`, `123.45s2`)
- **QUOTED_CHARACTER**: Caracteres precedidos por $ (ex: `$a`)
- **QUOTED_STRING**: Strings delimitadas por aspas simples (ex: `'texto'`)
- **HASHED_STRING**: Strings precedidas por # (ex: `#'string'`)
- **QUOTED_SELECTOR**: Seletores precedidos por # (ex: `#size`, `#+`, `#at:put:`)
- **BINARY_SELECTOR**: Operadores binários (ex: `+`, `-`, `*`, `/`, `=`, `>`)
- **RETURN_OPERATOR**: Operador de retorno (`^`)
- **ASSIGNMENT_OPERATOR**: Operador de atribuição (`:=`)
- **Símbolos de pontuação**:
  - **PERIOD**: Ponto (`.`)
  - **COLON**: Dois-pontos (`:`)
  - **HASH**: Cerquilha (`#`)
  - **LEFT/RIGHT_BRACKET**: Colchetes (`[` `]`)
  - **LEFT/RIGHT_PAREN**: Parênteses (`(` `)`)
  - **LEFT/RIGHT_BRACE**: Chaves (`{` `}`)
  - **PIPE**: Barra vertical (`|`)
  - **SEMICOLON**: Ponto e vírgula (`;`)
  - **COMMA**: Vírgula (`,`)

## Como compilar o projeto

Para compilar o analisador léxico, execute o script de compilação:

```
bash
chmod +x scripts/compile.sh
./scripts/compile.sh
```


Se necessário, utilize o comando `chmod` para solicitar permissão

Este script executa o JavaCC para gerar os arquivos Java a partir do arquivo `.jj` e então compila os arquivos Java gerados.

## Como executar o analisador

Para executar o analisador léxico em um arquivo de entrada, utilize o script de execução:

```bash
chmod +x scripts/run.sh
./scripts/run.sh src/test/resources/input_samples/sample1.st
```

O analisador processará o arquivo de entrada e exibirá os tokens identificados no formato:

```
TOKEN_tipo_do_token valor_do_token
```

## Exemplo de saída

Para um input como `x := 10`, a saída será:

```
ID x
ASSIGNMENT :=
INTEGER 10
```

## Autor

Patrick Duarte Pimenta
