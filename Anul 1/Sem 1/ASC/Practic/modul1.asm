bits 32 
;extern _printf
global _lungime


segment data use32 class=data
    verif_cuv db 0
    format db "%d ", 0

segment code use32 class=code
   
_lungime:

    push ebp
    mov ebp,esp
    
    pushad
    cld
    mov ecx, [ebp+8] ; lungimea cuvantului
    mov edx, [ebp+12] ; lungimea de verificare
    mov esi, [ebp+16] ; cuvantul
    
    jecxz fin
    
    cmp ecx, edx
    jb afisare_0
    
    
    bucla:
    
        lodsb 
        cmp al,'!'
        je e_bun
        cmp al,'#'
        je e_bun
        cmp al,'@'
        je e_bun
        cmp al,'&'
        je e_bun
        cmp al,'%'
        je e_bun
        
    loop bucla
    
    cmp byte [verif_cuv], 0
    je afisare_0
    
    e_bun:
        mov byte [verif_cuv],1
        ;push dword [verif_cuv]
        ;push dword format
        ;call _printf
        ;add esp ,8
        jmp fin
    
        
    
    afisare_0:
        ;push dword [verif_cuv]
        ;push dword format
        ;call _printf
        ;add esp ,8
    
    
    fin:
    
    popad
    mov esp,ebp
    pop ebp
    ret