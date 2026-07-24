bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,fclose,fopen,fprintf,fread; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll

    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    fisier db "text.txt", 0
    mod_acces dd "w",0
    format db "%d ", 0
    frecventa_cifra dd 0
    cifra dd 0 
    descriptor dd 0
    text times 2 db 0
    sir_frecventa times 11 dd 0
    maxim dd 0
    frecventa_cifra_max dd 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mod_acces
        push dword fisier
        call [fopen]
        add esp,4*2
        
        mov [descriptor], eax
        cmp eax, 0
        je fin
        
        citire:
            push dword [descriptor]
            push dword 1
            push dword 1
            push dword text
            call [fread]
            add esp ,4*4
            
            cmp eax, 1
            jne gata_citire
            
            cmp byte [text], '0'
            jb citire
            
            cmp byte [text], '0'
            ja citire
            
            mov eax, 0
            movzx eax, byte [text]
            add eax, '0'
            
            mov dword [cifra], eax
            
            inc dword [sir_frecventa+eax*4]
            
            jmp citire
            
            
        gata_citire:   
            mov ecx, 0
            mov ecx, 10
            
            bucla_fecv:
            
            mov eax, dword [sir_frecventa + ecx * 4]
            
            cmp eax, [frecventa_cifra_max]
            jb mai_mic
                mov dword [frecventa_cifra_max], eax
                mov al, cl
                add al, '0'
                mov [cifra],al
            mai_mic:
            
            loop bucla_fecv
            
        push dword [cifra]
        push dword format
        call [printf]
        add esp, 4*2
        
        push dword [frecventa_cifra_max]
        push dword format
        call [printf]
        add esp, 4*2
        
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        
        fin:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
