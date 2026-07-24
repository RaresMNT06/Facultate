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
    res dd 0
    a dw 1234h
    b dw 6543h
    c dd 0
    d dw -3
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, 0
        mov ax, word [a]
        and ax, 0000000111111000b
        shr ax, 3
        mov bx, 0
        mov bx, [b]
        and bx, 0000000000011100b
        shr bx, 4
        or ax, bx
        mov bx,  0
        mov bx, [a]
        and bx, 0001111111000000b
        shl bx, 3
        or ax, bx
        mov ebx, 0
        not ebx
        shl ebx, 16
        or eax, ebx
        mov [c], eax
        mov eax, 0
        ;(a + b) / (a * -3 + c) + c
        mov bx, [a]
        add bx, [b];(a+b)
        mov ax, [a]
        imul word [d] ;dx:ax= a*-3
        movsx ecx, dx
        shl ecx, 16
        or eax,ecx ;eax= a*-3
        add eax, [c];eax=(a * -3 + c)
        mov ecx, eax
        mov ax, bx
        cwde
        cdq
        idiv ecx
        add eax, dword [c]
        mov [res], eax
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


    


    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
