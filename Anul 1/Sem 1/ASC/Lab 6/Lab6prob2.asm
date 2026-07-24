bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
;Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii superiori ai
;cuvitelor superioare din elementele sirului de dublucuvinte care sunt divizibili cu 3.
;Exemplu:
;Se da sirul de dublucuvinte:
;s DD 12345678h, 1A2B3C4Dh, FE98DC76h
;Sa se obtina sirul
;d DB 12h.
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s DD 12345678h, 1A2B3C4Dh, 0F98DC76h
    len equ $-s
    d times len db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        cld
        mov esi, s
        mov edi, d
        mov ecx, len
        repeta:
            lodsd    
            mov ebx, eax
            shr eax, 24         
            mov bl, 3
            div bl                 
            cmp ah, 0
            jne next   ;daca nu e div cu 3 trecem la urm numar
            shr ebx, 24
            mov [edi], bl
            inc edi
        next:  
            loop repeta
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
