#include <trap.h> // 中文注释：引入陷阱与异常相关的定义
#include <env.h> // 中文注释：引入进程/环境结构体与管理接口
#include <printf.h> // 中文注释：引入内核打印接口

extern void handle_int(); // 中文注释：中断入口（硬件中断）
extern void handle_reserved(); // 中文注释：保留/未实现异常入口
extern void handle_tlb(); // 中文注释：TLB 异常入口（缺页/不一致）
extern void handle_sys(); // 中文注释：系统调用入口
extern void handle_mod(); // 中文注释：修改型异常入口（如写保护等）
unsigned long exception_handlers[32]; // 中文注释：异常向量表，保存各异常的处理例程地址

void trap_init() // 中文注释：初始化异常向量表
{
    int i; // 中文注释：循环变量

    for (i = 0; i < 32; i++) { // 中文注释：将所有异常向量初始化为保留处理例程
        set_except_vector(i, handle_reserved); // 中文注释：设置第 i 项为默认处理入口
    }

    set_except_vector(0, handle_int); // 中文注释：外部硬件中断入口
    set_except_vector(1, handle_mod); // 中文注释：修改型异常入口
    set_except_vector(2, handle_tlb); // 中文注释：TLB 加载异常入口
    set_except_vector(3, handle_tlb); // 中文注释：TLB 存储异常入口
    set_except_vector(8, handle_sys); // 中文注释：系统调用异常入口
}
void *set_except_vector(int n, void *addr) // 中文注释：设置异常向量表第 n 项，并返回旧值
{
    unsigned long handler = (unsigned long)addr; // 中文注释：新处理例程地址（保存为无符号长整型）
    unsigned long old_handler = exception_handlers[n]; // 中文注释：保留旧的处理例程地址
    exception_handlers[n] = handler; // 中文注释：写回新的处理例程地址
    return (void *)old_handler; // 中文注释：以指针形式返回旧入口
}


struct pgfault_trap_frame { // 中文注释：用户态缺页异常时在异常栈上的软件帧格式（用于传参）
    u_int fault_va; // 中文注释：发生缺页的虚拟地址
    u_int err; // 中文注释：错误码/原因（按实验自定义）
    u_int sp; // 中文注释：异常发生时的用户栈指针
    u_int eflags; // 中文注释：标志寄存器/状态
    u_int pc; // 中文注释：异常发生时的程序计数器（EPC）
    u_int empty1; // 中文注释：保留字段
    u_int empty2; // 中文注释：保留字段
    u_int empty3; // 中文注释：保留字段
    u_int empty4; // 中文注释：保留字段
    u_int empty5; // 中文注释：保留字段
};


void 
page_fault_handler(struct Trapframe *tf) // 中文注释：内核缺页处理入口，切换到用户自定义缺页处理
{
    // 中文注释：将当前 Trapframe 复制到用户异常栈（若已在异常栈则在其上继续压栈）
    struct Trapframe PgTrapFrame; // 中文注释：临时保存的 Trapframe
    extern struct Env *curenv; // 中文注释：当前环境指针

    bcopy(tf, &PgTrapFrame, sizeof(struct Trapframe)); // 中文注释：复制现场到临时变量

    if (tf->regs[29] >= (curenv->env_xstacktop - BY2PG) && // 中文注释：检测当前是否已位于用户异常栈页内
        tf->regs[29] <= (curenv->env_xstacktop - 1)) {
            tf->regs[29] = tf->regs[29] - sizeof(struct  Trapframe); // 中文注释：在异常栈上为 Trapframe 预留空间
            bcopy(&PgTrapFrame, (void *)tf->regs[29], sizeof(struct Trapframe)); // 中文注释：写入 Trapframe 到异常栈
        } else {
            tf->regs[29] = curenv->env_xstacktop - sizeof(struct  Trapframe); // 中文注释：首次进入异常栈，从栈顶往下放置 Trapframe
            bcopy(&PgTrapFrame,(void *)curenv->env_xstacktop - sizeof(struct  Trapframe),sizeof(struct Trapframe)); // 中文注释：写入 Trapframe
        }
    tf->cp0_epc = curenv->env_pgfault_handler; // 中文注释：跳转到用户注册的缺页处理函数入口

    return; // 中文注释：函数返回，后续由异常返回路径继续执行
}
