;=========================================================================
; 文件名：s1.asm
; 功能：将AX中的无符号数以二进制形式输出显示
; 环境：16位DOS MASM
; 说明：包含BIN_DISPLAY子程序和主程序测试代码
;=========================================================================

.model small
.stack 100H

.data
    ; 此程序不需要数据变量

.code

main proc
    ; 主程序开始
    ; 测试数据：将不同数值加载到AX中进行测试

    ; 测试1：输出0的二进制形式
    mov ax, 0
    call bin_display           ; 调用二进制输出子程序
    call newline              ; 换行

    ; 测试2：输出1的二进制形式
    mov ax, 1
    call bin_display
    call newline

    ; 测试3：输出255的二进制形式 (0000000011111111)
    mov ax, 255
    call bin_display
    call newline

    ; 测试4：输出65535的二进制形式 (1111111111111111)
    mov ax, 65535
    call bin_display
    call newline

    ; 测试5：输出12345的二进制形式
    mov ax, 12345
    call bin_display
    call newline

    ; 程序结束，返回DOS
    mov ah, 4Ch
    int 21h
main endp

;=========================================================================
; 子程序名：bin_display
; 功能：将AX中的无符号数以二进制形式输出显示
; 入口参数：AX = 要显示的无符号数
; 出口参数：无
; 使用的寄存器：AX, CX, DX
;=========================================================================
bin_display proc
    ; 保存寄存器
    push cx                   ; 保存CX寄存器
    push dx                   ; 保存DX寄存器

    ; 设置循环计数器，共输出16位二进制数
    mov cx, 16                ; CX = 16，循环计数器

display_loop:
    ; 将AX的最高位移到CF标志位
    shl ax, 1                 ; AX逻辑左移1位，最高位进入CF

    ; 判断CF标志位
    jc display_one            ; 如果CF=1，跳转到输出'1'

    ; CF=0，输出字符'0'
    mov dl, '0'               ; DL = '0'
    jmp output_char           ; 跳转到字符输出

display_one:
    ; CF=1，输出字符'1'
    mov dl, '1'               ; DL = '1'

output_char:
    ; 调用DOS中断输出单个字符
    mov ah, 2                 ; AH = 2，DOS输出单字符功能
    int 21h                   ; 调用DOS中断21h

    ; 循环计数器减1，判断是否继续
    dec cx                    ; CX = CX - 1
    jnz display_loop          ; 如果CX≠0，继续循环

    ; 恢复寄存器
    pop dx                    ; 恢复DX寄存器
    pop cx                    ; 恢复CX寄存器

    ret                       ; 子程序返回
bin_display endp

;=========================================================================
; 子程序名：newline
; 功能：输出回车换行
; 入口参数：无
; 出口参数：无
;=========================================================================
newline proc
    push ax                   ; 保存AX
    push dx                   ; 保存DX

    ; 输出回车符CR (Carriage Return)
    mov dl, 0Dh               ; DL = 回车符ASCII码
    mov ah, 2                 ; AH = 2，输出单字符功能
    int 21h                   ; 调用DOS中断

    ; 输出换行符LF (Line Feed)
    mov dl, 0Ah               ; DL = 换行符ASCII码
    mov ah, 2                 ; AH = 2，输出单字符功能
    int 21h                   ; 调用DOS中断

    pop dx                    ; 恢复DX
    pop ax                    ; 恢复AX

    ret                       ; 子程序返回
newline endp

end main
