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