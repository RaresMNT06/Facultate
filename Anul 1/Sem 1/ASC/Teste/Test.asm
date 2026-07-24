;Se considera urmatoarea problema si solutia propusa(codul sursa). Este solutia corecta?
;Daca considerati ca este necesar, modificati codul pentru a rezolva problema.
;Asigurati-va ca codul se asambleaza fara erori sau advertismente.
;--------------------------------------------------------------------------------------------------
; Se dau cuvantul A si octetul B. Se cere dublucuvantul C:
; bitii 0-2 ai lui C coincid cu bitii 5-7 ai lui B
; bitii 3-7 ai lui C coincid cu bitii 0-4 ai lui A
; bitii 8-9 ai lui C sunt egali cu 1
; bitii 10-15 ai lui C coincid cu bitii 6-11 ai lui A
; bitii 16-31 ai lui C sunt bitii coincid cu bitii negati lui A
;Sa se calculeze in interpretare cu semn(d-e+g)/f -e*2, unde d-byte, e-word, f=doubleword, g=qword
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
    a dw 1101001010010110b
    b db 10011011b
    c dd 0
    d db 10
    e dw 3
    f dd 4
    g dq 2
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov bx,0
        mov al, [b]
        shr al, 5 ;ca sa ducem pe pozitia 0-2 pentru a pune in c ar trebui sa shiftam spre dreapta cu 5
        and al, 07h
        or  bl,al ;punem in bl pe al nu pe ax iar bl= 0000 0100
        mov ax, [a]
        shl ax, 3 ; bitii 0-4 a lui o o sa fie pe pozitiile 7-3
        and ax, 0000000011111000b ; aici facem and nu or
        or bx, ax ; bx= 0000 0000 1011 0100
        or bh, 03h
        mov ax, [a]
        shl ax, 4 ; pentru a adauga la c urmatorii bitii 6 11 a lui a se vor muta spre stanga
        and ax, 1111110000000000b
        or bx, ax
        or [c], bx 
        movzx eax, word[a]; a nu este dword este word
        rol eax, 16 
        not eax
        and eax, 0FFFF0000h
        or [c], eax ; c= 2D692BB4h
        mov al, [d]
        cbw ; AL devine AX
        sub ax, [e] ;e este word si nu putem face scaderea
        cwde ; modifica din cwd in cwde pentru a converti dupa in qword
        cdq 
        add eax, dword[g]
        add edx, dword[g+2] ; - 0,50
        idiv dword [f] ; lui f trebuie declarata dimensiunea
        mov ebx, eax
        mov al, 2
        mul word[e] ; -0,50
        push dx
        push ax
        pop eax ;nu dam pop la al, dam pop la eax
        sub ebx, eax
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
