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
    ; Modify the code to solve the given problem.
; Mark lines that were added/removed/changed with a comment.
;
; Given: a - word, b - word, c - double word,s
;
; Compute c as follows:
; - c[0-3] <- a[5-8]
; - c[4-10] <- b[0-6]
; - c[11-18] <- 1
; - c[19-31] <- b[3-15]
;
; NOTE: Ranges are 0-indexed and inclusive,
; e.g. [0-2] means first 3 bits.
;
; Compute in the signed representation:
; res = a * -2 + (a / b - c) - c


    res dd 0
    a dw 1234h
    b dw 4321h
    c dd 0
    d dw -2
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, word [a] 
        and ax, 0000000111100000b
        shr ax, 5
        or [c], ax   
        mov ax, word [b]
        and ax, 0000000001111111b
        shl ax, 4
        or [c], ax
        mov eax, 0
        mov eax, 11111111b
        shl eax, 11
        or [c], eax  
        mov ebx, 0
        movzx ebx, word [b]
        and ebx, 1111111111111000b
        shl ebx, 16
        or [c], ebx
        mov ebx, dword[c]
        ;calcul aritmetic
        mov eax, 0
        mov ax, word [a]
        imul word [d]; dx:ax= a*-2
        push dx
        push ax
        pop eax ; eax = a*-2
        mov ebx , eax ; ebx = a*-2
        mov ax, word [a]
        cwd
        idiv word [b]; ax = a/b
        movsx eax, ax
        sub eax, [c]
        add ebx, eax
        sub ebx, [c]
        mov [res], ebx        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program



