bits 32 
global _prelucrare
segment data use32 class=data
    sir times 31 db 0
segment code use32 class=code
    
_prelucrare:

    push ebp
    mov ebp,esp
    
    pushad
    
    mov ecx, [ebp+12]
    mov edi, [ebp+8]
    test ecx, 1
    jnz len_imp
    
    std
    mov esi, [ebp+8]
  
    bucla:
        movsb
    loop bucla
    
    len_imp:
    cld
    popad
    mov esp,ebp
    pop ebp 
    mov eax, edi
    ret