// 用户态 IPC 辅助函数集

#include "lib.h"#include <mmu.h>  // 注意：原始代码将两个 include 放在一行，这里保持不改动
#include <env.h>  // 引入环境数组与字段定义

extern struct Env *env;  // 当前环境的指针（由 libmain 设置）

// 发送值给目标 whom。若对方尚未准备好接收（-E_IPC_NOT_RECV），则循环尝试并让出 CPU。
// 其他任何错误都触发 user_panic。
void
ipc_send(u_int whom, u_int val, u_int srcva, u_int perm)
{
	int r;  // 返回码

	while ((r=syscall_ipc_can_send(whom, val, srcva, perm)) == -E_IPC_NOT_RECV)
	{
		syscall_yield();  // 让出 CPU，避免忙等
		// writef("QQ");  // 调试输出
	}
	if(r == 0)
		return;  // 成功发送
	user_panic("error in ipc_send: %d", r);  // 其他错误一律异常退出
}

// 接收一个值并返回，同时在 whom 中写入发送者 envid、在 perm 中写入接收页权限（如有）。
u_int
ipc_recv(u_int *whom, u_int dstva, u_int *perm)
{
	// printf("ipc_recv:come 0\n");  // 调试日志（保留为注释）
	syscall_ipc_recv(dstva);  // 阻塞直到收到消息（并可在 dstva 接收一页）
	
	if (whom)
		*whom = env->env_ipc_from;  // 记录发送者
	if (perm)
		*perm = env->env_ipc_perm;  // 记录接收页权限
	return env->env_ipc_value;  // 返回收到的整型值
}
