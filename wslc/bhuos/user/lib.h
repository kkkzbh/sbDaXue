#ifndef LIB_H  // 头文件保护开始：防止重复包含
#define LIB_H  // 定义头文件保护宏
#include "fd.h"  // 引入文件描述符与设备抽象的声明
#include "pmap.h"  // 引入页表/虚拟内存管理相关声明
#include <mmu.h>  // 引入内存管理单元（MMU）常量与宏
#include <trap.h>  // 引入陷阱帧与中断/异常相关结构
#include <env.h>  // 引入环境（进程）结构体与常量
#include <args.h>  // 引入命令行参数解析宏/工具
#include <unistd.h>  // 引入基本类型与系统调用号等
// 运行时入口与退出接口声明（由用户程序/运行库使用）
extern void umain();  // 用户程序的主函数入口（由各应用定义）
extern void libmain();  // 运行库入口：负责初始化 env、调用 umain
extern void exit();  // 终止当前环境（进程）并返回内核

extern struct Env *env;  // 指向当前环境控制块的指针（由 libmain 设置）

#define USED(x) (void)(x)  // 抑制“未使用变量”告警的辅助宏

#include <stdarg.h>  // 可变参数支持（printf 系族使用）
// #define LP_MAX_BUF 80  // 打印缓冲区上限（禁用：采用实现文件中的定义）

// 低层 printf 实现：将格式化内容通过回调 output 输出
void user_lp_Print(void (*output)(void *, const char *, int),  // 输出回调（目标介质）
				   void *arg,  // 传递给回调的上下文指针
				   const char *fmt,  // 格式串
				   va_list ap);  // 变参列表

void writef(char *fmt, ...);  // 面向控制台的格式化输出（使用系统调用）

void _user_panic(const char *, int, const char *, ...)  // 终止前打印位置与信息
__attribute__((noreturn));  // 声明该函数不返回（便于编译器优化）

#define user_panic(...) _user_panic(__FILE__, __LINE__, __VA_ARGS__)  // 带源文件/行号的 panic 包装

// 进程创建与程序装载接口
int spawn(char *prog, char **argv);  // 按路径与参数创建并运行子环境
int spawnl(char *prot, char *args, ...);  // 变参版本的 spawn（以列表传参）
int fork(void);  // 复制当前环境，父子并发执行

void user_bcopy(const void *src, void *dst, size_t len);  // 内存拷贝（用户态实现）
void user_bzero(void *v, u_int n);  // 置零指定内存区域（用户态实现）

// 系统调用封装（见 syscall_lib.c）
extern int msyscall(int, int, int, int, int, int);  // 通用系统调用门（6 参数）

void syscall_putchar(char ch);  // 向控制台输出单个字符
u_int syscall_getenvid(void);  // 获取当前环境 ID
void syscall_yield(void);  // 主动让出 CPU
int syscall_env_destroy(u_int envid);  // 销毁指定环境
int syscall_set_pgfault_handler(u_int envid, void (*func)(void),  // 注册缺页处理入口与异常栈顶
								u_int xstacktop);
int syscall_mem_alloc(u_int envid, u_int va, u_int perm);  // 为环境在 va 分配一页（含权限）
int syscall_mem_map(u_int srcid, u_int srcva, u_int dstid, u_int dstva,  // 在不同环境间映射页
					u_int perm);
int syscall_mem_unmap(u_int envid, u_int va);  // 取消映射指定页

inline static int syscall_env_alloc(void)  // 分配新环境并返回 envid（内联包装）
{
    return msyscall(SYS_env_alloc, 0, 0, 0, 0, 0);  // 调用内核创建环境
}

int syscall_set_env_status(u_int envid, u_int status);  // 设置环境调度状态
int syscall_set_trapframe(u_int envid, struct Trapframe *tf);  // 设置陷阱帧（切换初始上下文）
void syscall_panic(char *msg);  // 内核态 panic（用于调试）
int syscall_ipc_can_send(u_int envid, u_int value, u_int srcva, u_int perm);  // 发送 IPC 消息
void syscall_ipc_recv(u_int dstva);  // 阻塞接收 IPC 消息（可接收页）
int syscall_cgetc();  // 从控制台非阻塞读取字符
int syscall_write_dev(u_int va,u_int dev,u_int offset);  // 向设备写（MMIO）
int syscall_read_dev(u_int va,u_int dev,u_int offset);   // 从设备读（MMIO）

// 字符串与内存工具（string.c）
int strlen(const char *s);  // 计算字符串长度（不含终止符）
char *strcpy(char *dst, const char *src);  // 复制字符串到目标缓冲区
const char *strchr(const char *s, char c);  // 查找字符首次出现的位置
void *memcpy(void *destaddr, void const *srcaddr, u_int len);  // 按字节拷贝指定长度
int strcmp(const char *p, const char *q);  // 按字典序比较两个字符串

// 进程间通信（ipc.c）
void	ipc_send(u_int whom, u_int val, u_int srcva, u_int perm);  // 发送 IPC（必要时让出 CPU）
u_int	ipc_recv(u_int *whom, u_int dstva, u_int *perm);  // 接收 IPC，并返回值/发送者/权限

// 进程等待（wait.c）
void wait(u_int envid);  // 等待指定子环境退出

// 控制台（console.c）
int opencons(void);  // 打开控制台，返回 fd
int iscons(int fdnum);  // 判断给定 fd 是否为控制台

// 管道（pipe.c）
int pipe(int pfd[2]);  // 创建匿名管道，返回读写两个 fd
int pipeisclosed(int fdnum);  // 判断管道另一端是否关闭

// 物理页引用计数查询（pageref.c）
int pageref(void *);  // 返回虚拟地址对应物理页的引用计数

// 缺页处理（pgfault.c）
void set_pgfault_handler(void (*fn)(u_int va));  // 注册用户态缺页处理回调

// 格式化输出到文件描述符（fprintf.c）
int fwritef(int fd, const char *fmt, ...);  // 向指定 fd 写入格式化字符串

// 文件系统 IPC（fsipc.c）
int	fsipc_open(const char*, u_int, struct Fd*);  // 请求打开文件/目录
int	fsipc_map(u_int, u_int, u_int);  // 请求将文件块映射到页
int	fsipc_set_size(u_int, u_int);  // 请求调整文件大小
int	fsipc_close(u_int);  // 请求关闭文件
int	fsipc_dirty(u_int, u_int);  // 标记文件块脏
int	fsipc_remove(const char*);  // 请求删除路径对应对象
int	fsipc_sync(void);  // 请求同步缓存到磁盘
int	fsipc_incref(u_int);  // 引用计数增加（若实现）

// 文件描述符层（fd.c）
int	close(int fd);  // 关闭文件描述符
int	read(int fd, void *buf, u_int nbytes);  // 从 fd 读取数据
int	write(int fd, const void *buf, u_int nbytes);  // 向 fd 写入数据
int	seek(int fd, u_int offset);  // 调整读写偏移
void	close_all(void);  // 关闭所有打开的 fd
int	readn(int fd, void *buf, u_int nbytes);  // 尝试读取指定字节数（可分多次）
int	dup(int oldfd, int newfd);  // 复制/重定向文件描述符
int fstat(int fdnum, struct Stat *stat);  // 获取 fd 对应对象的信息
int	stat(const char *path, struct Stat*);  // 获取路径对应对象的信息

// 文件层（file.c）
int	open(const char *path, int mode);  // 打开路径（返回 fd）
int	read_map(int fd, u_int offset, void **blk);  // 获取 offset 所在文件块的映射页地址
int	delete(const char *path);  // 删除给定路径（如实现）
int	ftruncate(int fd, u_int size);  // 调整已打开文件大小
int	sync(void);  // 同步文件系统缓存

// 断言宏：失败时打印表达式文本并终止（注意：反斜杠续行，勿在行尾加注释）
#define user_assert(x) \
	do { if (!(x)) user_panic("assertion failed: %s", #x); } while (0)

// 文件打开模式（与内核/文件服务器约定保持一致）
#define	O_RDONLY	0x0000		// 只读打开
#define	O_WRONLY	0x0001		// 只写打开
#define	O_RDWR		0x0002		// 读写打开
#define	O_ACCMODE	0x0003		// 访问模式掩码（用于提取 O_RDONLY/WRONLY/RDWR）

#define	O_CREAT		0x0100		// 不存在则创建
#define	O_TRUNC		0x0200		// 打开时截断为 0 长度
#define	O_EXCL		0x0400		// 与 O_CREAT 同用，若已存在则报错
#define O_MKDIR		0x0800		// 创建目录（而非普通文件）

#endif  // 头文件保护结束
