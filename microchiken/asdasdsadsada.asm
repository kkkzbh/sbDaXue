.MODEL SMALL
.STACK 100h

.DATA
a1 DW ?

.CODE
main PROC
    mov ax, @data
    mov ds, ax

    call ReadDecimal        ; AX <- user input integer
    mov bx, OFFSET a1
    mov [bx], ax            ; store the integer into a1

    mov ax, 4C00h
    int 21h
main ENDP

ReadDecimal PROC
    push bx
    push cx
    push dx
    
    xor bx, bx
    mov cx, 10
    
read_loop:
    mov ah, 01h
    int 21h
    
    cmp al, '0'
    jb read_done
    cmp al, '9'
    ja read_done
    
    sub al, '0'
    xor ah, ah
    
    push ax
    mov ax, bx
    mul cx
    mov bx, ax
    pop ax
    add bx, ax
    
    jmp read_loop
    
read_done:
    mov ax, bx
    
    pop dx
    pop cx
    pop bx
    ret
ReadDecimal ENDP

END main

