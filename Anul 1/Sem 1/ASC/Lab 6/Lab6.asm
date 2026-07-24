bits 32 ; assembling for the 32 bits architecture
;Se da un sir de octeti s. Sa se construiasca sirul de octeti d, care contine pe fiecare pozitie numarul de biti 1 ai octetului de pe pozitia corespunzatoare din s.
;Exemplu:
;s: 5, 25, 55, 127
;in binary:
;101, 11001,10111,1111111
;d: 2, 3, 5, 7
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s db 5, 25, 55, 127
    len equ $-s
    d times len db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        cld
        mov esi, s 
        mov edi, d
        mov ecx, len
        
        repeta:
            lodsb
            mov bl, al
            mov edx, 0; aici vom retine numarul de biti de 1 din fiecare numar din sir
            mov bh, 8; punem in bh 8 pentru a parcurge toti bitii din numar
        nr_biti:
            test bl, 1b; verifc daca ultimul bit e 1
            jz skip    
            inc edx
        skip:
            shr bl, 1
            dec bh
            jnz nr_biti
            
            mov [edi], dl
            inc edi
        loop repeta
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
