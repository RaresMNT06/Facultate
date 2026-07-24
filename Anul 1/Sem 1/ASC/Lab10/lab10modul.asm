bits 32 

global _numara

segment data public data use32
    contor dd 0


segment code public code use32


_numara:

        push ebp
        mov ebp, esp
        mov esi, [ebp+8]
        
        pushad
        
        mov dword [contor], 0
        
        bucla:
        
            lodsb
            cmp al, 0
            je fin
            cmp al, `A`
            jb nu_e_litera
            cmp al, `Z`
            jbe e_litera
            cmp al, `a`
            jb nu_e_litera
            cmp al, `z`
            jbe e_litera
            
            
            
            e_litera:
                inc dword [contor]
                
            nu_e_litera:
            
            jmp bucla
                
                
        fin:
        
        
        
        popad
        mov esp,ebp
        pop ebp
        mov eax, dword[contor]
        ret