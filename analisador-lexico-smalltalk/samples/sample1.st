"Este é um exemplo de programa Smalltalk para testar o analisador léxico"

"Definição de classe"
Object subclass: #ExemploLexical
    instanceVariableNames: 'valor nome'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'ExemplosLexical'!

"Método de instância com diferentes tokens"
ExemploLexical >> inicializar
    | variavelLocal outroValor |

    "Tokens reservados"
    valor := nil.
    variavelLocal := true.
    outroValor := false.

    "Números em vários formatos"
    valor := 42.
    valor := 16r2A.       "Inteiro radix (hex)"
    valor := 3.14159.     "Float"
    valor := 3.14e2.      "Float com expoente"
    valor := 123s2.       "Scaled decimal"
    valor := 123.45s2.    "Scaled decimal com ponto"

    "Operadores"
    valor := valor + 1.   "Operador binário"
    valor := valor * 2.
    valor > 100
        ifTrue: [ valor := 100 ]
        ifFalse: [ valor := valor - 10 ].

    "Characters"
    nome := $A.
    nome := $1.
    nome := $ .          "Caractere de espaço"
    nome := $+.

    "Strings"
    nome := 'Este é um texto de exemplo'.
    nome := 'String com ''aspas simples'' dentro'.

    "Hashed strings e selectors"
    self perform: #nome.
    self perform: #+.
    self perform: #at:put:.

    ^self   "Operador de retorno"
!

"Método com keyword message"
ExemploLexical >> calcular: umValor com: outroValor
    | resultado |
    resultado := umValor + outroValor.
    self verificar: resultado.
    ^resultado
!

"Método para testar mensagens binárias"
ExemploLexical >> + umObjeto
    ^valor + umObjeto
!

"Criando e usando instância da classe"
| exemplo valor1 valor2 |
exemplo := ExemploLexical new.
exemplo inicializar.
valor1 := #'Símbolo com espaço'.  "Hashed string"
valor2 := exemplo calcular: 10 com: 20.