#include "lib.h"  // 引入用户态运行库接口与全局 env 指针
#include <mmu.h>   // 引入内存管理单元常量/宏
#include <env.h>   // 引入环境（进程）相关结构与宏

void
exit(void)  // 终止当前环境（进程），并回到内核调度
{
	// close_all();  // 可选：关闭全部文件描述符（此处保持注释，仅说明用途）
	syscall_env_destroy(0);  // 传 0 表示销毁当前环境
}


struct Env *env;  // 指向当前环境控制块的全局指针（由 libmain 初始化）

void
libmain(int argc, char **argv)  // 运行库入口：初始化 env 并调用用户主函数
{
	// 将 env 指向 envs[] 中当前环境对应的结构体
	env = 0;  // 先清零（占位初始化）
	// writef("xxxxxxxxx %x  %x  xxxxxxxxx\n",argc,(int)argv);  // 调试输出示例
	int envid;  // 临时变量保存内核返回的环境 ID
	envid = syscall_getenvid();  // 获取当前环境的 32 位 ID（高位含类型）
	envid = ENVX(envid);  // 提取索引（去除高位标志）
	env = &envs[envid];  // 取出 envs 数组中的该环境描述符地址
	// 调用用户主函数入口（传递命令行参数）
	umain(argc,argv);  // 执行完毕视为程序正常返回
	// 以“优雅退出”的方式结束当前环境
	exit();  // 不会返回
	// syscall_env_destroy(0);  // 等价于 exit，保留注释供参考
}
