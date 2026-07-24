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
    ; - c[0-5] <- a[3-8]
    ; - c[6-8] <- b[2-4]
    ; - c[9-15] <- a[6-12]
    ; - c[16-31] <- 1
    ;
    ; NOTE: Ranges are 0-indexed and inclusive,
    ; e.g. [0-2] means first 3 bits.
    ;
    ; Compute in the signed representation:
    ; res = (a + b) / (a * -3 + c) + c
    res dd 0
    a dw 1234
    b dw 6543
    c dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, dword [a]
        and ax, 000111111b
        shr ax, 3
        or [c], ax
        mov ax, [b]
        and ax, 11100b
        shr ax, 4
        or [c], ax
        mov ax, [a]
        and ax, 1111111000000b
        shr ax, 3
        or [c], ax
        mov eax, 0
        not eax
        shl eax, 31
        mov [c], eax
        mov bx, [a]
        sub bx, [b]
        mov ax, [a]
        imul -3
        cwd
        add eax, [c]
        mov ecx, eax
        mov ax, bx
        cwde
        cdq
        div ecx
        add eax, word [c]
        mov res, eax
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
