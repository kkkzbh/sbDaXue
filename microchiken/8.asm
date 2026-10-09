.MODEL SMALL
.STACK 100h

.DATA

.CODE
main PROC
    mov ax, @data
    mov ds, ax

    mov ah, 01h
    int 21h
    mov bl, al
    mov dl, 0Dh
    mov ah, 02h
    int 21h
    mov dl, 0Ah
    mov ah, 02h
    int 21h
    

    sub bl, '0'       
    mov ah, 0       

    call PrintDecimalAX

    mov ax, 4C00h
    int 21h
main ENDP

PrintDecimalAX PROC NEAR
    push ax
    push bx
    push cx
    push dx

collect:

    add bl, 48
    mov dl, bl
    mov ah, 02h
    int 21h

done:
    pop dx
    pop cx
    pop bx
    pop ax
    ret
PrintDecimalAX ENDP

END main

