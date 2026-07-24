%ifndef _LAB_8_ASM_
%define _LAB_8_ASM_


calcul:
    mov eax, [esp+4]   
    mov ecx, [esp+8]   
    mov edx, [esp+12]  

    add eax, ecx
    sub eax, edx

    ret 
    
%endif