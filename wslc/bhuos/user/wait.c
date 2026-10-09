#include "lib.h"  // 基础库与系统调用
#include <env.h>   // 环境数组 envs 与状态枚举
void
wait(u_int envid)  // 等待目标环境退出
{
	struct Env *e;

	// writef("envid:%x  wait()~~~~~~~~~",envid);  // 调试输出
	e = &envs[ENVX(envid)];
	while(e->env_id == envid && e->env_status != ENV_FREE)  // 尚未退出则让出 CPU
		syscall_yield();
}

