#ifndef UNISTD_H // 头文件防重包含开始
#define UNISTD_H // 定义本头文件的防重包含宏

#define __SYSCALL_BASE 9527 // 系统调用号基值
#define __NR_SYSCALLS 20   // 本系统提供的系统调用数量


#define SYS_putchar          ((__SYSCALL_BASE) + 0)  // 输出一个字符
#define SYS_getenvid         ((__SYSCALL_BASE) + 1)  // 获取当前环境 ID
#define SYS_yield            ((__SYSCALL_BASE) + 2)  // 主动让出 CPU
#define SYS_env_destroy      ((__SYSCALL_BASE) + 3)  // 销毁指定环境
#define SYS_set_pgfault_handler ((__SYSCALL_BASE) + 4) // 安装缺页处理例程
#define SYS_mem_alloc        ((__SYSCALL_BASE) + 5)  // 分配一页并映射
#define SYS_mem_map          ((__SYSCALL_BASE) + 6)  // 在两个环境间建立映射
#define SYS_mem_unmap        ((__SYSCALL_BASE) + 7)  // 解除映射
#define SYS_env_alloc        ((__SYSCALL_BASE) + 8)  // 创建新环境
#define SYS_set_env_status   ((__SYSCALL_BASE) + 9)  // 设置环境运行状态
#define SYS_set_trapframe    ((__SYSCALL_BASE) + 10) // 设置异常现场
#define SYS_panic            ((__SYSCALL_BASE) + 11) // 触发内核 panic
#define SYS_ipc_can_send     ((__SYSCALL_BASE) + 12) // 发送 IPC 消息
#define SYS_ipc_recv         ((__SYSCALL_BASE) + 13) // 接收 IPC 消息
#define SYS_cgetc            ((__SYSCALL_BASE) + 14) // 读取控制台输入
#define SYS_write_dev        ((__SYSCALL_BASE) + 15) // 设备写
#define SYS_read_dev         ((__SYSCALL_BASE) + 16) // 设备读

#endif // 结束防重包含
