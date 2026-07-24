bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose, printf,fread
import exit msvcrt.dll
import fread msvcrt.dll  
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll 
import printf msvcrt.dll
  ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    fisier db "fisier.txt", 0
    mod_acces db "r", 0 
    format db "%d", 0                                              
    text times 100 db 0 
    cnt_pare dd 0
    descriptor_fis dd -1 
    lungime_sir dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push mod_acces
        push fisier
        call [fopen]
        add esp,4*2
        
        mov [descriptor_fis], eax
        
        push dword [descriptor_fis]
        push dword 100
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        mov [lungime_sir], eax
        mov ecx, [lungime_sir]
        mov ebx, 0
        jecxz fin
        repeta:
            mov eax,[text+ebx]
            sub eax, '0'
            test eax, 1b
            jnz nu_e_par
                inc dword [cnt_pare]
            nu_e_par:
            inc ebx
            loop repeta
        
        fin:
        
        push dword [cnt_pare]
        push dword format
        call [printf]
        add esp, 4*2
        
        
        
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
