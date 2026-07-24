bits 32 

global start

extern printf            
import printf msvcrt.dll   

segment data use32 class=data
    sir dw 0ABCh,0FFCh,0D314h,1234h
    len equ ($-sir)/2
    cuv db "yranib"
    siro times len db 0
    
segment code use32 class=code
    start:
        mov ecx,len 
        mov ebx, sir 
        mov edx, siro
        repeta:
            mov al,0
            mov si, [ebx]
            push ecx
            mov ecx, 8
            bucla:
                shl si,1
                shl si,1
                adc al,0
                shl al,1
            loop bucla
            pop ecx 
            mov [edx], al 
            inc ebx
            inc edx 
        loop repeta
        
       
        
 
