bits 32 
global _determinare

segment data use32 class=data
    min dd 999999 
    max dd 0
    cnt_max dd 0
    cnt_min dd 0
segment code use32 class=code
  
_determinare:

    push ebp
    mov ebp,esp
    
    mov ecx, [ebp+8]
    mov esi, [ebp+12]
    
    loop
        lodsd
        cmp eax, [max]
        jl next
        mov dword[max], eax
        inc dword[cnt_max]
        
        
        
    
    
    mov esp,ebp
    pop ebp
    
    ret 
    