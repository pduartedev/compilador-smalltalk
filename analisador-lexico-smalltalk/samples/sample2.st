Numeros subclass: #Primos
 instanceVariableNames: ''
 classVariableNames: ''
 poolDictionaries: ''
 category: 'Numeros'

Initialize
 super initialize.

verificaSeEPrimo: temp "a funcao isPrime ja existe na classe Integer"
 Transcript show: temp isPrime.

imprime
 Transcript show:'sobrescrevi o metodo imprime da classe pai(Numeros). Isso mostra que Smalltalk suporta
polimorfismo universal por inclusao'.