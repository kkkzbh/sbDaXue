#include "lib.h"  // 基础库与文件系统接口

int flag[256];  // 命令行选项标记表（按字符索引）

void lsdir(char*, char*);  // 列出目录内容
void ls1(char*, u_int, u_int, char*);  // 打印单个条目

void
ls(char *path, char *prefix)  // 对路径执行 ls：若为目录则遍历
{
	int r;
	struct Stat st;

	if ((r=stat(path, &st)) < 0)
		user_panic("stat %s: %e", path, r);
	if (st.st_isdir && !flag['d'])  // 非 -d 时目录展开
		lsdir(path, prefix);
	else
		ls1(0, st.st_isdir, st.st_size, path);
}

void
lsdir(char *path, char *prefix)  // 遍历目录并逐项打印
{
	int fd, n;
	struct File f;

	if ((fd = open(path, O_RDONLY)) < 0)
		user_panic("open %s: %e", path, fd);
	while ((n = readn(fd, &f, sizeof f)) == sizeof f)  // 逐个读取目录项
		if (f.f_name[0])
			ls1(prefix, f.f_type==FTYPE_DIR, f.f_size, f.f_name);
	if (n > 0)
		user_panic("short read in directory %s", path);
	if (n < 0)
		user_panic("error reading directory %s: %e", path, n);
}

void
ls1(char *prefix, u_int isdir, u_int size, char *name)  // 打印单个条目（可带前缀）
{
	char *sep;

	if(flag['l'])  // -l：长格式
		fwritef(1, "%11d %c ", size, isdir ? 'd' : '-');
	if(prefix) {  // 打印前缀路径
		if (prefix[0] && prefix[strlen(prefix)-1] != '/')
			sep = "/";
		else
			sep = "";
		fwritef(1, "%s%s", prefix, sep);
	}
	fwritef(1, "%s", name);
	if(flag['F'] && isdir)
		fwritef(1, "/");
	fwritef(1, " ");
}

void
usage(void)  // 使用方法提示
{
	fwritef(1, "usage: ls [-dFl] [file...]\n");
	exit();
}

void
umain(int argc, char **argv)  // 命令入口：解析选项并列出路径
{
	int i;

	ARGBEGIN{  // 处理 -d/-F/-l 选项
	default:
		usage();
	case 'd':
	case 'F':
	case 'l':
		flag[(u_char)ARGC()]++;
		break;
	}ARGEND

	if (argc == 0)
		ls("/", "");
	else {
		for (i=0; i<argc; i++)
			ls(argv[i], argv[i]);
	}
}

