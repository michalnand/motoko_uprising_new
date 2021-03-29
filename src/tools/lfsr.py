


reg = 12345

tab_a = 23
tab_b = 18


for i in range(1000):
    reg = reg << 1

    va = (reg>>tab_a)&1
    vb = (reg>>tab_b)&1
    if va^vb:
        reg|= 1
    
    print(reg%2, end="")
    
    