Integer fibonacci Integer n {
    Integer a;
    Integer b;
    Integer temp;
    Integer i;
    
    a := 0;
    b := 1;
    i := 0;
    
    while (i < n) {
        temp := a + b;
        a := b;
        b := temp;
        i := i + 1;
    }
    
    a := a;
}
