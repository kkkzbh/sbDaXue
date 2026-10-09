codes segment
    assume cs:codes

start:
    ; 打印字符'1'
    mov dl, '1'     ; 将字符'1'存入dl寄存器
    mov ah, 2       ; 2号功能调用：显示字符
    int 21h         ; 调用dos中断
    
    ; 等待按键
    mov ah, 1       ; 1号功能调用：等待键盘输入
    int 21h         ; 调用dos中断
    
    ; 程序结束
    mov ah, 4ch     ; 4ch功能调用：程序终止
    int 21h         ; 返回dos系统

codes ends
    end start