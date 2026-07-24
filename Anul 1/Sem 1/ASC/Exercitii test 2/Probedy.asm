                
                
   bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf, fopen, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
             
                
                
                
      import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
                          
; se da un sir si sa se afiseze in fisierul output-{lungimea subsecventei maxime cu caractere identice}.txt subsecventa in sine de lungime maxima

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir db "addddccccddddd", 0
    lungime equ $ - sir
    format_afisare db "%s", 0
    lungime_maxima db 0
    caracter_lungime_maxima db 0
    descriptor dd 0
    file_properties db "w", 0
    file_name db "Output-0.txt", 0
    caracter_cautare db 0
    lungime_curenta db 0
    sir_subsecventa_maxima times 100 db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov esi, sir
        mov ecx, lungime
            
            mov al, byte [esi]
            mov byte [caracter_cautare], al
            bucla:
                lodsb
                cmp [caracter_cautare], al
                jne nu_sunt_egale
                    inc byte [lungime_curenta]
                    jmp modificare_maxim
                nu_sunt_egale:
                    mov byte [lungime_curenta], 1
                    mov [caracter_cautare], al
                    jmp final_iteratie
          
                
                modificare_maxim:
                    mov dl, byte [lungime_curenta]
                    cmp dl, byte [lungime_maxima]
                    jb lungime_curenta_mai_mica
                        mov byte [lungime_maxima], dl
                        mov dl, byte [caracter_cautare]
                        mov byte [caracter_lungime_maxima], dl
                    lungime_curenta_mai_mica:
                final_iteratie:
            loop bucla
            
            mov cl, byte [lungime_maxima]
            mov edi, sir_subsecventa_maxima ;posibil sa nu mearga
            mov al, [caracter_lungime_maxima]
            bucla_creat_sir_subsecventa_maxima:
                stosb
            loop bucla_creat_sir_subsecventa_maxima
            
            mov al, '0'
            add al, [lungime_maxima]
            mov byte [file_name + 7], al
            
            push dword file_properties
            push dword file_name
            call [fopen]
            add esp, 4 * 2
            
            mov dword [descriptor], eax
            
            push dword sir_subsecventa_maxima
            push dword format_afisare
            push dword [descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            push dword [descriptor]
            call [fclose]
            add esp, 4

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program