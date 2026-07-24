bits 32 ; assembling for the 32 bits architecture
;Se dau doua siruri de octeti S1 si S2. Sa se construiasca sirul D prin concatenarea elementelor din sirul S1 1uate de la stanga spre dreapta si a elementelor din sirul S2 luate de la dreapta spre stanga.
;Exemplu:
;S1: 1, 2, 3, 4
;S2: 5, 6, 7
;D: 1, 2, 3, 4, 7, 6, 5
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 db 1, 2, 3, 4
    l1 equ $-s1
    s2 db 5, 6, 7
    l2 equ $-s2
    d times l1+l2 db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, l1
        mov ebx, 0
        
        jecxz fin1
        sir1:
            mov al,[s1+ebx]
            mov [d+ebx],al
            inc ebx
        loop sir1
        fin1:
        mov ecx, l2
        mov ebx, 0
        mov edx, l1
        jecxz fin2
        sir2:
            mov al,[s2+ecx-1]
            mov [d+edx+ebx],al
            inc ebx
        loop sir2
        fin2:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
