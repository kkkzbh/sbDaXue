
#ifndef _ENV_H_ // 头文件防重包含开始
#define _ENV_H_ // 定义本头文件的防重包含宏

#include "types.h" // 基础类型
#include "queue.h" // 链表宏
#include "trap.h"  // Trapframe 定义
#include "mmu.h"   // 页表相关类型

#define LOG2NENV 10                    // 环境数量的对数（以 2 为底）
#define NENV     (1 << LOG2NENV)       // 最大环境数量
#define ENVX(envid) ((envid) & (NENV - 1))      // 从 envid 取索引
#define GET_ENV_ASID(envid) (((envid) >> 11) << 6) // 生成 MIPS ASID（示意）

#define ENV_FREE        0 // 空闲
#define ENV_RUNNABLE    1 // 就绪可运行
#define ENV_NOT_RUNNABLE 2 // 存在但不可运行

struct Env { // 进程/环境控制块
    struct Trapframe env_tf;         // 最近一次陷入时的现场
    LIST_ENTRY(Env) env_link;        // 全局空闲/就绪链表链接
    u_int env_id;                    // 唯一标识符
    u_int env_parent_id;             // 父环境 ID
    u_int env_status;                // 运行状态
    Pde*  env_pgdir;                 // 页目录基址
    u_int env_cr3;                   // CR3/页表基物理地址或等价字段
    LIST_ENTRY(Env) env_sched_link;  // 调度队列链接
    u_int env_pri;                   // 调度优先级

    u_int env_ipc_value;   // IPC 传递的值
    u_int env_ipc_from;    // IPC 发送方 envid
    u_int env_ipc_recving; // 是否正在接收
    u_int env_ipc_dstva;   // IPC 映射目标 VA
    u_int env_ipc_perm;    // IPC 映射权限

    u_int env_pgfault_handler; // 用户态缺页处理函数入口
    u_int env_xstacktop;       // 用户异常栈顶

    u_int env_runs; // 被调度运行的次数
    u_int env_nop;  // 预留字段
}; // 结构体结束

LIST_HEAD(Env_list, Env);                 // 环境链表头类型
extern struct Env* envs;                  // 全部环境数组
extern struct Env* curenv;                // 当前正在运行的环境
extern struct Env_list env_sched_list[2]; // 就绪队列（按优先级等划分）

void env_init(void);                                   // 初始化环境数组与空闲链
int  env_alloc(struct Env** e, u_int parent_id);       // 分配并初始化一个环境
void env_free(struct Env*);                            // 释放环境
void env_create_priority(u_char* binary, int size, int priority); // 以优先级创建
void env_create(u_char* binary, int size);             // 创建一个默认优先级环境
void env_destroy(struct Env* e);                       // 销毁环境

int  envid2env(u_int envid, struct Env** penv, int checkperm); // ID 到指针（可检查权限）
void env_run(struct Env* e);                           // 切换到目标环境运行

#define ENV_CREATE2(x, y)         \
{                                 \
    extern u_char x[], y[];       \
    env_create(x, (int)y);        \
} // 使用两个符号创建环境

#define ENV_CREATE_PRIORITY(x, y)                 \
{                                                 \
    extern u_char binary_##x##_start[];           \
    extern u_int  binary_##x##_size;              \
    env_create_priority(binary_##x##_start,       \
                        (u_int)binary_##x##_size, \
                        y);                       \
} // 使用链接符号创建并指定优先级

#define ENV_CREATE(x)                              \
{                                                  \
    extern u_char binary_##x##_start[];            \
    extern u_int  binary_##x##_size;               \
    env_create(binary_##x##_start,                 \
               (u_int)binary_##x##_size);          \
} // 使用链接符号创建环境

#endif // 结束防重包含
