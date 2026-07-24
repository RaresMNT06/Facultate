bits 32
global  _citire     

segment data use32 class=data

segment code use32 class=code
    
_citire:

    push ebp
    mov ebp,esp
    
    
    mov esp,ebp
    pop ebp
    ret