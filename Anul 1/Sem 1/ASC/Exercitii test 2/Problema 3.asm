bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fclose,fopen,fprintf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
;se citesc la tastatura numere panda dam de 0 si se pune in fisierul pare_nr prare numerele pare si analog la impare
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir_pare times 100 dd 0
    sir_impare times 100 dd 0
    mod_acces dd "w",0
    descriptor_pare dd 0
    descriptor_impare dd 0
    nume_fisier_pare db "pare-0.txt", 0
    nume_fisier_impare db "impare-0.txt", 0
    format_print db "%d ", 0
    format_scan db "%d", 0
    index_pare db 0
    index_impare db 0
    numar dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        citire:
            push dword numar
            push dword format_scan
            call [scanf]
            add esp, 4*2
            
            cmp dword [numar], 0
            je scriere_fisier
            
            test dword [numar], 1b
            jz nr_par
                movzx edx, byte [index_impare]
                mov eax, dword [numar]
                mov dword [sir_impare+ edx*4] ,eax
                inc byte [index_impare]
                jmp citire
            
            nr_par:
                movzx edx, byte [index_pare]
                mov eax, dword [numar]
                mov dword [sir_pare+ edx*4] ,eax
                inc byte [index_pare]
                jmp citire
            
        scriere_fisier:
            mov cl, byte [index_pare]
            add cl, '0'
            mov byte [nume_fisier_pare+5] ,cl
            
            mov cl, byte [index_impare]
            add cl, '0'
            mov byte [nume_fisier_impare+7] ,cl
            
            
            push dword mod_acces
            push dword nume_fisier_impare
            call [fopen]
            add esp, 4*2
            
            mov [descriptor_impare],eax
            
            push dword mod_acces
            push dword nume_fisier_pare
            call [fopen]
            add esp, 4*2
            
            mov [descriptor_pare],eax
            
            cmp byte [index_impare], 0
            je scriere_pare
            
            mov ecx, 0
            mov cl, byte [index_impare]
            cld
            mov esi, sir_impare
            
            repeta_impare:
                mov eax, 0
                lodsd
                push ecx
                
                push dword eax
                push dword format_print
                push dword [descriptor_impare]
                call [fprintf]
                add esp, 4*3
                
                pop ecx
            
            loop repeta_impare
            
            scriere_pare:
            cmp byte [index_pare], 0
            je gata
            
            mov ecx, 0
            mov cl, byte [index_pare]
            cld
            mov esi, sir_pare
            
            repeta_pare:
                mov eax, 0
                lodsd
                push ecx
                
                push dword eax
                push dword format_print
                push dword [descriptor_pare]
                call [fprintf]
                add esp, 4*3
                
                pop ecx
            
            loop repeta_pare
            
            gata:
            
            push dword [descriptor_impare]
            call [fclose]
            add esp, 4
            
            push dword [descriptor_pare]
            call [fclose]
            add esp, 4
                
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
