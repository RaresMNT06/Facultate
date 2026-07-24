bits 32 ; assembling for the 32 bits architecture
;Prob 2 (b+b)+(c-a)+d a - byte, b - word, c - double word, d - qword - Interpretare fara semn
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
        ;b+b
        movzx eax , word [b]
        add eax, eax ;eax=b+b
        ;c-a
        mov edx , dword [c]
        movzx ecx , byte [a]
        sub edx , ecx ; edx= (c-a)
        ;(b+b) + (c-a)
        add eax , edx ; eax = (b+b)+ (c-a)
        ;(b+b) + (c-a) + d
        mov edx , 0
        add eax, [d]
        adc edx, [d+4];edx:eax=(b+b) + (c-a) + d
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
