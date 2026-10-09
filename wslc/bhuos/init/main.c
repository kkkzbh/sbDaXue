/*
 * 许可证与来源说明（中文化）：
 * - 原始作者：Jun Sun（原注释中含邮箱标识）。
 * - 授权条款：遵循 GNU General Public License（GPL）第 2 版或更高版本的相同条款。
 * - 该头部为对原英文许可声明的中文化说明，便于阅读；实际授权条件以 GPL 正文为准。
 */

#include <printf.h>    // 引入内核态打印输出
#include <pmap.h>      // 引入内存与页表管理接口（mips_init 在其中完成初始化）

int main()                                 // 内核可执行的入口（实验框架下作为启动点）
{	// 函数体开始
	printf("main.c:\tmain is start ...\n"); // 启动提示：标记 main 已开始执行

	mips_init();                             // 进入系统初始化流程：内存、异常、进程等子系统初始化
	panic("main is over is error!");        // 正常情况下不应返回至此；若返回则触发内核恐慌

	return 0;                                // 按 C 约定保留返回值；理论上不会到达
}	// 函数体结束
