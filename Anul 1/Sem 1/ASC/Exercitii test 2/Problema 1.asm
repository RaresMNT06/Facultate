bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf,fopen,fclose,               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir db "addccccdddddd", 0
    len equ $-sir
    format_afisare db "%s", 0
    descriptor_fisier dd 0
    mod_acces db "w", 0
    file_name db "output-0.txt", 0
    caracter db 0
    lungime_curenta db 0
    lungime_max db 0
    caracter_max db 0
    sir_sub_max times 100 db 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov esi, sir
        mov ecx, len
        mov al, byte[esi]
        mov byte [caracter], al
        
        bucla:
            lodsb
            cmp [caracter], al
            jne nu_sunt_egale
                inc byte[lungime_curenta]
                jmp modificare_maxim
                
            
            
            nu_sunt_egale:
                mov byte [lungime_curenta], 1
                mov [caracter], al
                jmp final_iteratie
            
            modificare_maxim:
                mov dl, byte [lungime_curenta]
                cmp dl, byte [lungime_max]
                jb lungime_curenta_mai_mica
                    mov [lungime_max] , dl
                    mov dl, [caracter]
                    mov byte [caracter_max] , dl
                lungime_curenta_mai_mica:
            final_iteratie:
                
        loop bucla
        
        mov cl  ,byte[lungime_max]
        mov edi, sir_sub_max
        mov al, byte[caracter_max]
        bucla_subsecventa:
            stosb
        loop bucla_subsecventa
        mov al, '0'
        add al, [lungime_max]
        mov [file_name+7], al
        
        push dword mod_acces
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [descriptor_fisier],eax
        
        push dword sir_sub_max
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp , 4*3
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
