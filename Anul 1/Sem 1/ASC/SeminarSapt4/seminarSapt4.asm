bits 32 ; assembling for the 32 bits architecture
;Problema2
;Se dau cuvintele A si B. Se cere dublucuvantul C:
;bitii 0-3 ai lui C coincid cu bitii 5-8 ai lui B
;bitii 4-8 ai lui C coincid cu bitii 0-4 ai lui A
;bitii 9-15 ai lui C coincid cu bitii 6-12 ai lui A
;bitii 16-31 ai lui C coincid cu bitii lui B
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    A dw 1011011110100001b
    B dw 0101111011010111b
    C dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, 0 ;aici vom calcula rezultatul
        mov bx, [B]; izolam bitii 5-8 a lui B
        and bx, 0000000111100000b; bx=0000 0000 1100 0000
        ror bx, 5; bx=0000 0000 0000 0110
        movzx ecx, bx; ecx= 0000 0000 0000 0000 0000 0000 0000 0110 punem in rezultat bitii 5-8 a lui B pe poztiile 0 3 a lui C
        mov ax, [A] 
        and ax, 0000000000011111b; ax=0000 0000 0000 0001
        shl ax, 4; ax=0000 0000 0001 0000
        or ax,bx ; ax=0000 0000 0001 0110
        movzx ecx, ax; ecx= 0000 0000 0000 0000 0000 0000 0001 0110
        mov bx, 0; golim bx ul pentru a lucra cu bitii 6-12 a lui A
        mov bx, [A]; izolam bitii 6-12 a lui A
        and bx, 0001111111000000b; bx=0001 0111 1000 0000
        shl bx, 3; bx=1011 1100 0000 0000
        or bx,ax ; bx=1011 1100 0001 0110
        movzx ecx, bx; ecx=0000 0000 0000 0000 1011 1100 0001 0110b ecx=0000BC16h
        mov ax,0;aici vom izola bitii lui B
        mov ax, [B];
        movzx eax,ax;eax= 0000 0000 0000 0000 0101 1110 1101 0111
        shl eax, 16;eax = 0101 1110 1101 0111 0000 0000 0000 0000
        or ecx,eax;ecx 0101 1110 1101 0111 1011 1100 0001 0110 ecx=5ED7BC16h
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
