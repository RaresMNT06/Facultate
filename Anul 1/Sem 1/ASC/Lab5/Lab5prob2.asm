bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s db 1, 2, 3, 4
    l equ $-s
    d times l dw 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, l-1
        mov ebx, 0
        mov esi, 0
        jecxz fin
        bucla:
            mov al,[s+ebx]
            mul byte [s+ebx+1]
            mov [d+ebx], al
            inc ebx
            inc esi
        loop bucla
        fin:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
