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
    a dw 1234h	
	b db 5Bh	
	c dd 1	
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;Fie următoarea problemă și soluția propusă (codul sursă), este soluția corectă? 
        ;Dacă considerați că este necesar, modificați codul pentru a rezolva problema. 
        ;Asigurați-vă că codul se asamblează fără erori sau avertismente.
        ;-----------------------------------------------------------------------------------
        ;Se dau cuvantul a si octetul b. Dublucuvantul c se formează astfel:
        ;- bitii 0-2 ai lui c au valoarea 1
        ;- bitii 3-5 ai lui c au valoarea 0
        ;- bitii 6-9 ai lui c coincid cu bitii 11-14 ai lui a
        ;- bitii 10-15 ai lui c coincid cu bitii 1-6 ai lui b
        ;- bitii 16-31 ai lui c au valoarea lui a
        ;Să se efectueze în interpretarea cu semn operația ((a+c)/b+c)*2-a
        ;-----------------------------------------------------------------------------------
		MOV dword [c], 0000_0000_0000_0000_0000_0000_0000_0111b 	
		MOV AX,[a]
		;AND AX,7800b greseala s 7 si 8 nu sunt numere din baza 2
        and AX, 0111_1000_0000_0000b ; luam bitii 14-11 a lui a
		;SAR AX,5	greseala pentru un numar care are bitul de semn 1 muta gresit spre dreapta
        shr AX, 5
		OR [c],AX	; c =  0000 0000 0000 0000 0000 0000 1000 0111		
		MOV AL,byte[b]
		MOV AH,0
		AND AX,0000_0000_0111_1110b
		SHL AX,9	
		;AND [c],AX daca facem and riscam sa pierdem valoarea anterioara a lui c
        or [c], AX  ;c = 0000 0000 0000 0000 1011 0100 1000 0111   
        mov eax,0
        mov ax,[a]
        shl eax,16
        OR [c],eax
        ; ((a+c)/b+c)*2-a
        mov eax, 0 ;doar de asigurare ca eax este gol
		movsx ax,byte [a];ax = a			
		cwde ;eax = a	
		add eax,[c];eax = a+c			
		mov edx,0					
		;movsx ebx,word[b] greseala b este de tip byte 
        movsx ebx, byte[b]
		;idiv [b]	greseala nu este determinata dimensiunea lui b
        idiv ebx ; edx:eax= (a+c)/b
		add eax,[c] ;eax =(a+c)/b+c
		;imul 2		greseala, 2 trebuie pus intr un registru sau o variabila
        mov ecx, 2
        imul ecx ;  edx:eax= ((a+c)/b+c)*2
		;mov eax,ebx	stricam eax unde calculam rezultatul	
		mov ecx,edx		
		;movsx eax, word[a] in eax avem rezultatul
        movsx ebx, word[a]
		;cdq	ebx	greseala, nu trebuie scris registrul
        cdq
		sub eax,ebx
		sbb edx,ecx	
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

