bits 32 ; assembling for the 32 bits architecture
; Problema 1 c-(a+d)+(b+d) a - byte, b - word, c - double word, d - qword - Interpretare fara semn
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 2
    b dw 3
    c dd 10
    d dq 4
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, [a]
        mov ah, 0 
        mov dx, 0
        push dx
        push ax
        pop eax
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
