bits 32
global start

extern exit, scanf, printf

import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll
%include "Lab_8.asm"
segment data use32
    a dd 0
    b dd 0
    c dd 0
    format db "%d", 0

segment code use32
start:
    push dword a
    push dword format
    call [scanf]
    add esp, 8

    push dword b
    push dword format
    call [scanf]
    add esp, 8

    push dword c
    push dword format
    call [scanf]
    add esp, 8

    
    push dword [c]
    push dword [b]
    push dword [a]
    call calcul
    add esp, 12

    push eax
    push dword format
    call [printf]
    add esp, 8

    push dword 0
    call [exit]