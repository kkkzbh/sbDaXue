#include "lib.h"  // 基础库与进程/文件接口
#include <args.h>  // 命令行参数解析宏

int debug = 0;  // 调试日志开关

// 词法分析：从字符串 s 中取下一个 token。
// 输出：*p1 指向 token 起始，*p2 指向其后一个位置。
// 返回：0 结束；'>' 重定向；'|' 管道；'w' 单词。
// 最终会把 token 末尾写入 NUL 作为终止符。
#define WHITESPACE " \t\r\n"  // 空白字符集合
#define SYMBOLS "<|>&;()"      // 特殊符号集合

int
_gettoken(char *s, char **p1, char **p2)  // 低层 token 获取
{
	int t;

	if (s == 0) {
		//if (debug > 1) writef("GETTOKEN NULL\n");
		return 0;
	}

	// if (debug > 1) writef("GETTOKEN: %s\n", s);

	*p1 = 0;
	*p2 = 0;

	while(strchr(WHITESPACE, *s))
		*s++ = 0;
	if(*s == 0) {
	// 	if (debug > 1) writef("EOL\n");
		return 0;
	}
	if(strchr(SYMBOLS, *s)){
		t = *s;
		*p1 = s;
		*s++ = 0;
		*p2 = s;
		// if (debug > 1) writef("TOK %c\n", t);
		return t;
	}
	*p1 = s;
	while(*s && !strchr(WHITESPACE SYMBOLS, *s))
		s++;
	*p2 = s;
	if (debug > 1) {
		t = **p2;
		**p2 = 0;
		// writef("WORD: %s\n", *p1);
		**p2 = t;
	}
	return 'w';
}

int
gettoken(char *s, char **p1)
{
	static int c, nc;
	static char *np1, *np2;

	if (s) {
		nc = _gettoken(s, &np1, &np2);
		return 0;
	}
	c = nc;
	*p1 = np1;
	nc = _gettoken(np2, &np1, &np2);
	return c;
}

#define MAXARGS 16  // 命令允许的最大参数个数
void
runcmd(char *s)  // 解析并运行命令（支持重定向与管道）
{
	char *argv[MAXARGS], *t;
	int argc, c, i, r, p[2], fd, rightpipe;
	int fdnum;
	rightpipe = 0;
	gettoken(s, 0);
writef("in runcmd\n");  // 调试：进入 runcmd
again:
	argc = 0;
	for(;;){
		c = gettoken(0, &t);
		switch(c){
		case 0:
			goto runit;
		case 'w':
			if(argc == MAXARGS){
				writef("too many arguments\n");
				exit();
			}
			argv[argc++] = t;
			break;
		case '<':  // 输入重定向
			if(gettoken(0, &t) != 'w'){
				writef("syntax error: < not followed by word\n");
				exit();
			}
			// 打开 t 用于读取
			r = open(t, O_RDONLY);
			if (r < 0) {
				writef("cannot open the path followed <\n");
				exit();
			}
			fdnum = r;
			// 将其 dup 到 fd 0，然后关闭原 fd
			r = dup(fdnum, 0);
			if (r < 0) {
				writef("cannot dup in <\n");
				exit();
			}
			r = close(fdnum);
			if (r < 0) {
				writef("cannot close fd in <\n");
				exit();
			}
			goto runit;
			//user_panic("< redirection not implemented");
			break;
		case '>':  // 输出重定向（覆盖）
			if(gettoken(0, &t) != 'w'){
				writef("syntax error: > not followed by word\n");
				exit();
			}
			// 打开 t 用于写出
			r = open(t, O_WRONLY);
			if (r < 0) {
				writef("cannot open the path followed >\n");
				exit();
			}
			fdnum = r;
			// 将其 dup 到 fd 1，然后关闭原 fd
			r = dup(fdnum, 1);
			if (r < 0) {
				writef("cannot dup in >\n");
				exit();
			}
			r = close(fdnum);
			if (r < 0) {
				writef("cannot close fd in >\n");
				exit();
			}
			goto runit;
			user_panic("> redirection not implemented");
			break;
		case '|':
				// 管道处理步骤：
				//   1) 创建管道；
				//   2) fork 子进程；
				//   子进程（右侧命令）：dup 管道读端到 0，关闭读/写端，跳转 again 解析余下命令；
				//   父进程（左侧命令）：dup 管道写端到 1，关闭写/读端，记录 rightpipe 为子进程 envid，
				//                      跳转 runit 执行左侧命令，随后等待右侧结束。
			if ((i = pipe(p)) < 0) {
				user_panic("sh.c pipe: %e", i);
			}
			if ((i = fork()) < 0) {
				user_panic("sh.c fork: %e", i);
			}

			if (i == 0) {	// 子进程（右侧）
				dup(p[0], 0);
				close(p[0]);
				close(p[1]);
// writef("son will goto again\n");
				goto again;
			} else {	// 父进程（左侧）
				rightpipe = i;
				dup(p[1], 1);
				close(p[1]);
				close(p[0]);
//writef("father will goto runit, rightpipe = %x\n", rightpipe);
				goto runit;
			}
			
			user_panic("| not implemented");
			break;
		}
	}

runit:  // 执行命令
	if(argc == 0) {
		if (debug) writef("EMPTY COMMAND\n");
		return;
	}
	argv[argc] = 0;
	if (1) {  // 打印即将执行的命令
		writef("[%08x] SPAWN:", env->env_id);
		for (i=0; argv[i]; i++)
			writef(" %s", argv[i]);
		writef("\n");
	}

	if ((r = spawn(argv[0], argv)) < 0)
		writef("spawn %s: %e\n", argv[0], r);
	close_all();
	if (r >= 0) {
		if (debug) writef("[%08x] WAIT %s %08x\n", env->env_id, argv[0], r);
		wait(r);
	}
	if (rightpipe) {
		if (debug) writef("[%08x] WAIT right-pipe %08x\n", env->env_id, rightpipe);
writef("father wait son\n");  // 父进程等待右侧子进程
		wait(rightpipe);
	}

	exit();
}

void
readline(char *buf, u_int n)  // 读取一行用户输入
{
	int i, r;
	// writef("in sh.c readline\n");
	r = 0;
	for(i=0; i<n; i++){
		if((r = read(0, buf+i, 1)) != 1){
			if(r < 0)
				writef("read error: %e", r);
			exit();
		}
		if(buf[i] == '\b' || buf[i] == 127){
			if(i > 0)
				i -= 2;
			else
				i = 0;
		}
		if(buf[i] == '\r' || buf[i] == '\n'){
			buf[i] = 0;
			return;
		}
	}
	writef("line too long\n");
	while((r = read(0, buf, 1)) == 1 && buf[0] != '\n')
		;
	buf[0] = 0;
}	

char buf[1024];

void
usage(void)  // 用法提示
{
	writef("usage: sh [-dix] [command-file]\n");
	exit();
}

void
umain(int argc, char **argv)  // Shell 主程序入口
{
	int r, interactive, echocmds;
	interactive = '?';
	echocmds = 0;
	writef("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	writef("::                                                         ::\n");
	writef("::              Super Shell  V0.0.0_1                      ::\n");
	writef("::                                                         ::\n");
	writef(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	ARGBEGIN{  // 处理 -d（调试）-i（交互）-x（回显）
	case 'd':
		debug++;
		break;
	case 'i':
		interactive = 1;
		break;
	case 'x':
		echocmds = 1;
		break;
	default:
		usage();
	}ARGEND

	if(argc > 1)
		usage();
	if(argc == 1){
		close(0);
		if ((r = open(argv[1], O_RDONLY)) < 0)
			user_panic("open %s: %e", r);
		user_assert(r==0);
	}
	if(interactive == '?')
		interactive = iscons(0);
	for(;;){
		if (interactive)
			fwritef(1, "\n$ ");
writef("before readline\n");
		readline(buf, sizeof buf);
writef("after readline\n");		
		if (buf[0] == '#')
			continue;
		if (echocmds)
			fwritef(1, "# %s\n", buf);
writef("debug0\n");
		if ((r = fork()) < 0)
			user_panic("fork: %e", r);
writef("debug1\n");
		if (r == 0) {
			runcmd(buf);
			exit();
			return;
		} else
			wait(r);
	}
}
