#include "lib.h"    // 用户态系统调用封装接口
#include <unistd.h>  // 基本类型/系统调用号
#include <mmu.h>     // MMU 常量/宏
#include <env.h>     // 环境（进程）结构体
#include <trap.h>    // 陷阱号等定义

void syscall_putchar(char ch)  // 向控制台输出一个字符
{
	msyscall(SYS_putchar, (int)ch, 0, 0, 0, 0);  // 仅第一个参数有效
}


u_int
syscall_getenvid(void)  // 获取当前环境 ID
{
	return msyscall(SYS_getenvid, 0, 0, 0, 0, 0);  // 无附加参数
}

void
syscall_yield(void)  // 主动让出 CPU，进入调度
{
	msyscall(SYS_yield, 0, 0, 0, 0, 0);
}


int
syscall_env_destroy(u_int envid)  // 销毁给定 envid 的环境
{
	return msyscall(SYS_env_destroy, envid, 0, 0, 0, 0);
}
int
syscall_set_pgfault_handler(u_int envid, void (*func)(void), u_int xstacktop)  // 注册缺页处理
{
	return msyscall(SYS_set_pgfault_handler, envid, (int)func, xstacktop, 0, 0);
}

int
syscall_mem_alloc(u_int envid, u_int va, u_int perm)  // 分配一页并映射到 va
{
	return msyscall(SYS_mem_alloc, envid, va, perm, 0, 0);
}

int
syscall_mem_map(u_int srcid, u_int srcva, u_int dstid, u_int dstva, u_int perm)  // 跨进程映射页
{
	return msyscall(SYS_mem_map, srcid, srcva, dstid, dstva, perm);
}

int
syscall_mem_unmap(u_int envid, u_int va)  // 取消映射给定虚拟地址处的页
{
	return msyscall(SYS_mem_unmap, envid, va, 0, 0, 0);
}

int
syscall_set_env_status(u_int envid, u_int status)  // 设置环境的运行状态
{
	return msyscall(SYS_set_env_status, envid, status, 0, 0, 0);
}

int
syscall_set_trapframe(u_int envid, struct Trapframe *tf)  // 设置陷阱帧（上下文）
{
	return msyscall(SYS_set_trapframe, envid, (int)tf, 0, 0, 0);
}

void
syscall_panic(char *msg)  // 触发内核态 panic（调试）
{
	msyscall(SYS_panic, (int)msg, 0, 0, 0, 0);
}

int
syscall_ipc_can_send(u_int envid, u_int value, u_int srcva, u_int perm)  // 非阻塞尝试发送 IPC
{
	return msyscall(SYS_ipc_can_send, envid, value, srcva, perm, 0);
}

void
syscall_ipc_recv(u_int dstva)  // 阻塞接收 IPC，并可在 dstva 接收一页
{
	msyscall(SYS_ipc_recv, dstva, 0, 0, 0, 0);
}

int
syscall_cgetc()  // 从控制台读取一个字符（无则返回 0）
{
	return msyscall(SYS_cgetc, 0, 0, 0, 0, 0);
}
int syscall_write_dev(u_int va,u_int dev,u_int offset)  // 设备写：把用户缓冲区映射给驱动
{
    return msyscall(SYS_write_dev,va,dev,offset,0,0);
}

int syscall_read_dev(u_int va,u_int dev,u_int offset)  // 设备读：把驱动数据读入用户缓冲区
{
    return msyscall(SYS_read_dev, va , dev , offset ,0,0);
}
