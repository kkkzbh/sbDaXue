#include <env.h> // 中文注释：环境（进程）管理接口
#include <pmap.h> // 中文注释：物理内存与页表操作接口
#include <printf.h> // 中文注释：内核打印接口

// 中文注释：实现简单的时间片轮转调度；从就绪队列按队列轮转选择下一个环境运行
void sched_yield(void)
{
	static int index = 0; // 中文注释：当前使用的就绪队列索引（0/1 双队列）
	static int time = 0; // 中文注释：当前运行环境剩余时间片
	static struct Env * e; // 中文注释：被选中的下一个环境
	struct Env * temp; // 中文注释：用于插入队尾的临时指针

	if (curenv == NULL && LIST_EMPTY(&env_sched_list[0]) && LIST_EMPTY(&env_sched_list[1])) { // 中文注释：系统中没有可调度的环境
		printf("There is no env to sched\n"); // 中文注释：提示无可运行环境
	}

	if (time == 0 || curenv == NULL) { // 中文注释：时间片用尽或当前无运行环境时需要切换
		if (LIST_EMPTY(&env_sched_list[index])) { // 中文注释：若当前队列为空，切换到另一个队列
			index = 1 - index; // 中文注释：0 与 1 在两个队列间取反
		} 
		if (!LIST_EMPTY(&env_sched_list[index])) { // 中文注释：从非空就绪队列取队头
			e = LIST_FIRST(&env_sched_list[index]); // 中文注释：获取队头环境
			LIST_REMOVE(e, env_sched_link); // 中文注释：从就绪队列移除
			time = e->env_pri; // 中文注释：按优先级设定时间片
			temp = LIST_FIRST(&env_sched_list[1 - index]); // 中文注释：准备将当前环境放到另一队列的队尾

			if (temp != NULL) { // 中文注释：另一队列非空则插入到其尾部
				LIST_FOREACH(temp, &env_sched_list[1 - index], env_sched_link) // 中文注释：遍历到队尾
                                	if(LIST_NEXT(temp, env_sched_link)==NULL) break; // 中文注释：到达尾节点则停止
                                LIST_INSERT_AFTER(temp, e, env_sched_link); // 中文注释：插入到尾节点之后
			} else { // 中文注释：另一队列为空则作为队头插入
				LIST_INSERT_HEAD(&env_sched_list[1 - index], e, env_sched_link); // 中文注释：插入为空队列的表头
			}
		}
	}

	if (time > 0) { // 中文注释：减少剩余时间片（用于下次调度判断）
		time--; // 中文注释：时间片减一
	}
	e->env_runs++; // 中文注释：统计该环境运行次数
	env_run(e); // 中文注释：切换到选中的环境运行
	return; // 中文注释：不返回（切换到新环境），语义上保留
}
