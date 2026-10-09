; main.asm - 64位 MASM 程序
.code

ExitProcess PROTO

main PROC
    ; 简单的退出程序
    mov rcx, 0          ; 退出代码 0
    call ExitProcess    ; 调用 Windows API
main ENDP

END