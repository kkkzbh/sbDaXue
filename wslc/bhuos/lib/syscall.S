#include <asm/regdef.h> // 中文注释：寄存器别名
#include <asm/cp0regdef.h> // 中文注释：CP0 寄存器定义
#include <asm/asm.h> // 中文注释：汇编辅助宏
#include <stackframe.h> // 中文注释：Trapframe/寄存器上下文布局
#include <unistd.h> // 中文注释：系统调用号等常量

NESTED(handle_sys,TF_SIZE, sp) // 中文注释：系统调用异常处理入口（保存现场并分发调用）
    SAVE_ALL                            // 中文注释：保存全部通用寄存器到 Trapframe
    CLI                                 // 中文注释：关闭中断避免嵌套
    nop
    .set at                             // 中文注释：允许使用保留寄存器 $at

    lw	    t1, TF_EPC(sp) // 中文注释：取出 EPC（异常返回地址）
    addiu   t1, t1, 4 // 中文注释：系统调用为延迟槽后继续执行，EPC 前移一条指令
    sw	    t1, TF_EPC(sp) // 中文注释：写回更新后的 EPC

    lw	    a0, TF_REG4(sp) // 中文注释：a0 保存系统调用号（来自用户态）
    
    addiu   a0, a0, -__SYSCALL_BASE     // 中文注释：转换为相对系统调用号
    sll     t0, a0, 2                   // 中文注释：索引*4 得到表项偏移
    la      t1, sys_call_table          // 中文注释：加载系统调用表基址
    addu    t1, t1, t0                  // 中文注释：定位具体调用的表项
    lw      t2, 0(t1)                   // 中文注释：取出对应的内核处理函数入口

    lw      t0, TF_REG29(sp)            // 中文注释：t0 取用户态 sp
    lw      t3, 16(t0)                  // 中文注释：取第 5 个参数
    lw      t4, 20(t0)                  // 中文注释：取第 6 个参数

    // 中文注释：在内核栈为 6 个参数开辟空间，并填入 a0~a3 与 t3,t4
    lw	    a0, TF_REG4(sp) // 中文注释：第 1 个参数
    lw	    a1, TF_REG5(sp) // 中文注释：第 2 个参数
    lw	    a2, TF_REG6(sp) // 中文注释：第 3 个参数
    lw	    a3, TF_REG7(sp) // 中文注释：第 4 个参数
    addiu    sp, sp, -24 // 中文注释：为栈上传参预留空间（仅存放第 5、第 6 个）
    sw	    t3, 16(sp) // 中文注释：写入第 5 个参数
    sw	    t4, 20(sp) // 中文注释：写入第 6 个参数
    
    jalr    t2                          // 中文注释：间接跳转调用具体 sys_* 处理函数
    nop
    
    addiu    sp, sp, 24 // 中文注释：恢复内核栈指针
    
    sw      v0, TF_REG2(sp)             // 中文注释：将返回值写回 Trapframe 的 v0 位置
   move a0, sp // 中文注释：可选：将 tf 指针传参（调试用）
   addiu sp, sp, -16 // 中文注释：预留调用日志函数的栈空间（当前未启用）
   nop // 中文注释：占位
   addiu sp, sp, 16 // 中文注释：恢复栈

    j       ret_from_exception          // 中文注释：跳转至通用异常返回路径
    nop
END(handle_sys)

sys_call_table:                         // 中文注释：系统调用分发表
.align 2
    .word sys_putchar // 中文注释：打印字符
    .word sys_getenvid // 中文注释：获取环境 ID
    .word sys_yield // 中文注释：让出 CPU
    .word sys_env_destroy // 中文注释：销毁环境
    .word sys_set_pgfault_handler // 中文注释：设置缺页处理入口
    .word sys_mem_alloc // 中文注释：分配物理页并映射
    .word sys_mem_map // 中文注释：共享页映射
    .word sys_mem_unmap // 中文注释：解除映射
    .word sys_env_alloc // 中文注释：创建新环境
    .word sys_set_env_status // 中文注释：设置环境状态
    .word sys_set_trapframe // 中文注释：设置 Trapframe
    .word sys_panic // 中文注释：触发内核恐慌
    .word sys_ipc_can_send // 中文注释：IPC 发送
    .word sys_ipc_recv // 中文注释：IPC 接收
    .word sys_cgetc // 中文注释：从控制台读取字符
     .word sys_write_dev // 中文注释：写设备寄存器
     .word sys_read_dev // 中文注释：读设备寄存器
