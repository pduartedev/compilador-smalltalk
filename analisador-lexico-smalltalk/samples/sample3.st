Integer extend [

  "Traduzido da versão em C"
  isPerfectC [ |tot| tot := 1.
     (2 to: (self sqrt) + 1) do: [ :i |
        (self rem: i) = 0
        ifTrue: [ |q|
                  tot := tot + i.
                  q := self // i.
                  q > i ifTrue: [ tot := tot + q ]
        ]
     ].
     ^ tot = self
  ]

  "Outra maneira"
  isPerfect [
     ^ ( ( ( 2 to: self // 2 + 1) select: [ :a | (self rem: a) = 0 ] )
         inject: 1 into: [ :a :b | a + b ] ) = self
  ]
].