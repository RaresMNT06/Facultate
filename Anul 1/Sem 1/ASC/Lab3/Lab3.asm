bits 32 ; assembling for the 32 bits architecture
;p roblema 5 [d-2*(a-b)+b*c]/2   a,b,c byte d word
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 10
    b db 5
    c db 2
    d dw 20
    e db 2
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AL, [a]
        sub AL, [b]
        mul byte [e] ;Ax= 2*(a-b)
        mov CX, AX; cx= 2*(a-b)
        mov AL, [b]
        mul byte [c]  ;ax=b*c
        mov DX, [d]
        sub DX, CX
        add DX, AX ; DX=[d-2*(a-b)+b*c]
        MOV AX, DX
        div byte [e] ; AX/BYTE[e]
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
