"SMALLTALK: CONVERSÃO DE UM PROGRAMA EM ESCRITO EM C (.c) PARA SMALLTALK (.st)"

" Definição da classe Ponto com variáveis de instância x e y "
Object subclass: Ponto [
    | x y |

    "SIMILAR AO GETTER DE UMA LINGUAGEM OO moderna"
    x [
        ^x
    ]

    "SIMILAR AO SETTER"
    x: anInteger [
        x := anInteger
    ]

    y [
        ^y
    ]

    y: anInteger [
        y := anInteger
    ]
]

"Classe utilitária #Utils para conter o método func: n:"
Object subclass: Utils [
    | dummy |
]

Utils class extend [
    func: pontoArray n: n [
        | res i temp point |

        "If (caso base): n <= 0"
        n <= 0 ifTrue: [ ^ 1.0 ].

        "If (caso base): n = 1"
        n = 1 ifTrue: [
            "Acesso a primeira posição do array"
            point := pontoArray at: 1.

            ^ 1.01
                + (point x / 1.0e2)
                + (point y / 0.1e-2)
        ].

        "Inicializa a variável res com valor double"
        res := 0.25e-13.

        "Representacao de um loop decrescente:"
        "i = n - 1 ... 0, interrompe se ponto.x <= 0"
        i := n.

        [
            (i >= 1)
                and: [ (pontoArray at: i) x > 0]
        ]

        whileTrue: [
            point := pontoArray at: i.

            "Calcula temp = (y * x) rem 123"
            temp := (point y * point x) \\ 123.

            temp < 0.0
                ifTrue: [
                    res := res - (res * 2.0e-2 + (self func: pontoArray n: n - 1) * temp)
                ]
                ifFalse: [
                    res := res + (res * 0.3e3 + (self func: pontoArray n: n - 2) * temp).
                    Transcript show: 'Estranho, ne?'; cr.
                ].

            i := i - 1.
        ].

        ^res
    ]
]

"CÓDIGO DE TESTE"
Transcript show: 'Programa carregado com sucesso.'; cr.

| p1 p2 p3 pontos resultado |
p1 := Ponto new.
p1 x: 10; y: 20.

p2 := Ponto new.
p2 x: 5; y: 15.

p3 := Ponto new.
p3 x: 8; y: 12.

"Criar um array com as instâncias de Ponto"
pontos := Array with: p1 with: p2 with: p3.

"Chamar o método func:n:"
resultado := Utils func: pontos n: 3.

"Imprimir o resultado"
Transcript show: 'Resultado: ', resultado printString; cr.