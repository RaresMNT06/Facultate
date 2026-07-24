bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose, printf,fread,scanf
import exit msvcrt.dll
import fread msvcrt.dll  
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll 
import printf msvcrt.dll
import scanf msvcrt.dll
  ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s db "abcabAAbcbb", 0
    len equ $-s
    filename times 128 db 0        
    file_name_scanf db "%s", 0   
    file_name_read db "w", 0           ; creăm fișierul cu scriere
    file_pointer dd 0               ; aici salvăm pointerul FILE*
    mesaj_cerere_nume db "Introdu numele fisierului: ", 0
    frecv times 256 dd 0
    linie_noua db "%c %d", 10, 0    ; 10 vine de la \n pentru a scrie pe o alta linie

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mesaj_cerere_nume
        call [printf]
        add esp, 4
        
        ; !!! scanf(format, buffer) – formatul se pune ultimul pe stivă
        push dword filename
        push dword file_name_scanf
        call [scanf]
        add esp, 8
        
        push dword file_name_read
        push dword filename
        call [fopen]
        add esp, 8
        
        mov [file_pointer], eax
        cmp eax, 0
        je inchide_fisier          ; daca nu s-a deschis fisierul, iesim
        
        ; ---------------- NUMARARE CARACTERE ----------------
        mov ebx, 0                 ; ebx = index in sirul s

    numara_caractere:
            mov al, [s + ebx]      ; luam caracterul de pe pozitia ebx
            cmp al, 0              ; daca este terminatorul de sir, ne oprim
            je scriere_rezultate

            movzx edx, al          ; EDX = codul caracterului (0..255)
            inc dword [frecv + edx*4] ; frecv[caracter]++

            inc ebx                ; trecem la urmatorul caracter
            jmp numara_caractere

            
scriere_rezultate:
    xor ecx, ecx                   ; ECX = caracterul (0..255)

scrie_loop:
    cmp ecx, 256
    jge inchide_fisier

    mov eax, [frecv + ecx*4]
    cmp eax, 0
    je continua

    ; fprintf(file_pointer, "%c %d\n", ecx, eax)
    push eax                       ; frecventa
    push ecx                       ; caracter
    push dword linie_noua          ; "%c %d\n"
    push dword [file_pointer]      ; fisierul
    call [fprintf]
    add esp, 16 

continua:
    inc ecx
    jmp scrie_loop

            
inchide_fisier:
    push dword [file_pointer]
    call [fclose]
    add esp, 4

    ; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program