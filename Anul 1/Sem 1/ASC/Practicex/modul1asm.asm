bits 32 

global _special

segment data use32 class=data
    
segment code use32 class=code
   
_special:
    
    push ebp
    mov ebp, esp 
    
    push ebx
    push ecx
    push edx
    
    mov ebx, [ebp+8] ;n
    mov edx, [ebp+12] ;numarul
    mov ecx, [ebp+16] ;nr_cif
    
    
    test edx,1
    jz fin
    
    nr_cif:
    
        cmp ebx, ecx
        jnz fin 
        mov eax, 1
        
    fin:
    
    pop edx
    pop ecx
    pop ebx
    
    mov esp,ebp
    pop ebp
   
    ret