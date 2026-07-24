bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fprintf,fopen,fclose            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir db "Priveste cerul frumos ", 0
    len equ $-sir
    mod_acces db "w",0
    format db "%d",0
    descriptor_fisier dd 0
    nume_fisier times 100 db 0
    numar_litere dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ebx, 0
        mov esi, sir
        mov ecx, len
        mov edi, nume_fisier
        bucla:
            lodsb
            cmp al, 0
            je gata
            
            cmp al, ' '
            je fisier
                stosb           ;edi/nume_fisier numele fisierului
                inc ebx                 ;numarul de litere
                jmp bucla
            
            fisier:
                mov byte [edi],"."
                mov byte [edi+1],"t"
                mov byte [edi+2],"x"
                mov byte [edi+3],"t"
                mov byte [edi+4],0
                
                push dword mod_acces
                push dword nume_fisier
                call [fopen]
                add esp,4*2
                
                mov [descriptor_fisier], eax
                
                mov [numar_litere], bl
                
                push dword [numar_litere]
                push dword format
                push dword [descriptor_fisier]
                call [fprintf]
                add esp, 4*3
                
                push dword [descriptor_fisier]
                call [fclose]
                add esp, 4
                
                mov edi, nume_fisier
                mov ebx, 0
                
                
                
                
        
        loop bucla
        
        gata:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
