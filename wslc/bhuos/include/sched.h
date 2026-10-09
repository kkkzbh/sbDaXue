#ifndef __SCHED_H__ // 头文件防重包含开始
#define __SCHED_H__ // 定义本头文件的防重包含宏

void sched_init(void);     // 初始化调度器
void sched_yield(void);    // 主动让出 CPU
void sched_intr(int);      // 中断触发的调度入口

#endif // 结束防重包含
