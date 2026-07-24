bits 32 ; assembling for the 32 bits architecture
;Problema3 (b+b+d)-(c+a) a - byte, b - word, c - double word, d - qword - Interpretare cu semn
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 1
    b dw 2
    c dd 3
    d dq 4
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;(b+b+d)
        movsx eax, word [b]
        add eax, eax
        add eax, [d]
        adc edx, [d+4] ;edx:eax =(b+b+d)
        ;(c+a)
        mov ebx, dword [c]
        movsx ecx, byte [a]
        add ebx , ecx ; ebx = (c+a)
        ;(b+b+d)-(c+a)
        sub eax, ebx              
        sbb edx, 0   ;exd:eax=(b+b+d)-(c+a)
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
