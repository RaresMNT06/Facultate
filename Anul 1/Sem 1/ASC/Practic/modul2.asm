bits 32 

global _medie

segment data use32 class=data
    contor db 0
    
segment code use32 class=code
    
_medie:
    
    push ebp
    mov ebp,esp
    pushad
    
    mov esi,[ebp+8] ;sirul cu lungimi
    mov ebx,[ebp+12];lungime medie
    mov ecx,[ebp+16];n
    
    
    bucla:
        lodsb 
        cmp al,bl
        jbe nu_e_bun
        inc byte[contor]
        nu_e_bun:
        
    loop bucla
    
   
    
        
    pushad
    mov esp,ebp
    pop ebp
    movzx eax,  byte [contor]
    ret