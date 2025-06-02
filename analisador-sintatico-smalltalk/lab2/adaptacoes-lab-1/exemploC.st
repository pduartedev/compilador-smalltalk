"Implementação equivalente ao programa C fornecido"

"Definição da classe Ponto (equivalente à estrutura ponto_t)"
Object subclass: Ponto [
    | x y |
    
    "Métodos de acesso"
    x [
        ^x
    ]
    
    x: umValor [
        x := umValor
    ]
    
    y [
        ^y
    ]
    
    y: umValor [
        y := umValor
    ]
    
    "Inicialização"
    x: valorX y: valorY [
        x := valorX.
        y := valorY.
        ^self
    ]
]

"Definição da classe Programa para conter os métodos principais"
Object subclass: Programa [
    func: v n: n [
        "Equivalente à função func no código C"
        | res temp i |
        
        "Caso base 1: n <= 0"
        n <= 0 ifTrue: [
            ^1.0
        ].
        
        "Caso base 2: n = 1"
        n = 1 ifTrue: [
            ^1.01 + ((v at: 1) x / 1.0e2) + ((v at: 1) y / 0.1e-2)
        ].
        
        "Caso recursivo"
        res := 0.25e-13.
        
        "Loop while (Nota: índices em Smalltalk começam em 1)"
        i := n.
        [ i >= 1 ] whileTrue: [
            ((v at: i) x > 0) 
                ifTrue: [
                    temp := ((v at: i) y * (v at: i) x) \\ 123.
                    
                    temp < 0.0
                        ifTrue: [
                            res := res - (res * 2.0e-2 + (self func: v n: (n - 1)) * temp)
                        ]
                        ifFalse: [
                            res := res + (res * 0.3e3 + (self func: v n: (n - 2)) * temp).
                            Transcript show: 'Estranho, ne?'; cr
                        ].
                    i := i - 1  "Decrementar o índice"
                ]
                ifFalse: [ ^res ]
        ].
        
        ^res
    ]
    
    "Método para testar o programa"
    executarTeste [
        | pontos resultado |
        
        "Criar array com alguns pontos de teste"
        pontos := Array new: 3.
        pontos at: 1 put: (Ponto new x: 10 y: 20).
        pontos at: 2 put: (Ponto new x: 5 y: 15).
        pontos at: 3 put: (Ponto new x: 8 y: 25).
        
        "Chamar a função"
        resultado := self func: pontos n: 3.
        
        "Mostrar resultado"
        Transcript show: 'Resultado da função: '; show: resultado printString; cr.
    ]
]

"Executar uma demonstração do programa"
Transcript cr; show: '===== Executando programa ====='; cr.

"Testar o programa"
programa := Programa new.
programa executarTeste.

Transcript cr; show: '===== Fim da execução ====='; cr.