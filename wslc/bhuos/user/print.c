/*
 *  低层 printf 实现（用户态轻量版）
 *  说明：本文件实现了格式化输出的核心逻辑（数字/字符串/宽度/左对齐等），
 *        并通过回调函数将结果输出到目标介质。仅添加中文注释，未改动代码语义。
 */

#include	<print.h>  // 打印接口头文件（提供 LP_MAX_BUF 等）

/* 宏工具 */
#define		IsDigit(x)	( ((x) >= '0') && ((x) <= '9') )  // 判断是否数字字符
#define		Ctod(x)		( (x) - '0')                        // 字符转十进制数值

/* 前置声明 */
extern int user_PrintChar(char *, char, int, int);
extern int user_PrintString(char *, char *, int, int);
extern int user_PrintNum(char *, unsigned long, int, int, int, int, char, int);

/* 私有常量：缓冲区越界时输出的致命错误信息 */
static const char user_theFatalMsg[] = "fatal error in user_lp_Print!";

/* 低层 printf() 主函数（通过回调输出） */
void
user_lp_Print(void (*output)(void *, char *, int), 
	 void * arg,
	 char *fmt, 
	 va_list ap)
{

#define 	OUTPUT(arg, s, l)  \
  { if (((l) < 0) || ((l) > LP_MAX_BUF)) { \
       (*output)(arg, (char*)user_theFatalMsg, sizeof(user_theFatalMsg)-1); for(;;); \
    } else { \
      (*output)(arg, s, l); arg+= l;\
    } \
  }  /* 输出宏：长度越界则报错并停机，否则输出并推进 arg */
    
    char buf[LP_MAX_BUF];  // 临时输出缓冲区

    char c;         // 临时字符
    char *s;        // 临时字符串
    long int num;   // 临时数字

    int longFlag;  // 是否长整型
    int negFlag;   // 是否负数
    int width;     // 字段宽度
    int prec;      // 精度
    int ladjust;   // 左对齐标志
    char padc;     // 填充字符

    int length;    // 实际输出长度

    for(;;) {
	{ 
	    /* 扫描直到下一个 '%' */
	    char *fmtStart = fmt;
	    while ( (*fmt != '\0') && (*fmt != '%')) {
		fmt ++;
	    }

	    /* 输出此前累积的普通字符串 */
	    OUTPUT(arg, fmtStart, fmt-fmtStart);

	    /* 若到达结尾则退出 */
	    if (*fmt == '\0') break;
	}

	/* 发现一个 '%' 标记，进入格式处理 */
	fmt ++;
	
	/* 处理 'l' 前缀（长整型） */
	if (*fmt == 'l') {
	    longFlag = 1;
	    fmt ++;
	} else {
	    longFlag = 0;
	}

	/* 处理其他前缀（对齐、宽度、精度、填充） */
	width = 0;
	prec = -1;
	ladjust = 0;
	padc = ' ';

	if (*fmt == '-') {
	    ladjust = 1;
	    fmt ++;
	}

	if (*fmt == '0') {
	    padc = '0';
	    fmt++;
	}

	if (IsDigit(*fmt)) {
	    while (IsDigit(*fmt)) {
		width = 10 * width + Ctod(*fmt++);
	    }
	}

	if (*fmt == '.') {
	    fmt ++;
	    if (IsDigit(*fmt)) {
		prec = 0;
		while (IsDigit(*fmt)) {
		    prec = prec*10 + Ctod(*fmt++);
		}
	    }
	}


	/* 分派格式化类型 */
	negFlag = 0;
	switch (*fmt) {
	 case 'b':
	    if (longFlag) { 
		num = va_arg(ap, long int); 
	    } else { 
		num = va_arg(ap, int);
	    }
	    length = user_PrintNum(buf, num, 2, 0, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'd':
	 case 'D':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    if (num < 0) {
		num = - num;
		negFlag = 1;
	    }
	    length = user_PrintNum(buf, num, 10, negFlag, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'o':
	 case 'O':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = user_PrintNum(buf, num, 8, 0, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'u':
	 case 'U':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = user_PrintNum(buf, num, 10, 0, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;
	    
	 case 'x':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = user_PrintNum(buf, num, 16, 0, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'X':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = user_PrintNum(buf, num, 16, 0, width, ladjust, padc, 1);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'c':
	    c = (char)va_arg(ap, int);
	    length = user_PrintChar(buf, c, width, ladjust);
	    OUTPUT(arg, buf, length);
	    break;

	 case 's':
	    s = (char*)va_arg(ap, char *);
	    length = user_PrintString(buf, s, width, ladjust);
	    OUTPUT(arg, buf, length);
	    break;

	 case '\0':
	    fmt --;
	    break;

		 default:
		    /* 非格式字符：按原样输出 */
		    OUTPUT(arg, fmt, 1);
		}	/* switch (*fmt) 结束 */

	fmt ++;
	    }		/* for(;;) 循环结束 */

    /* 结束信号：输出一个空字符通知上层停止 */
    OUTPUT(arg, "\0", 1);
}


/* --------------- local help functions --------------------- */
int
user_PrintChar(char * buf, char c, int length, int ladjust)
{
    int i;
    
    if (length < 1) length = 1;
    if (ladjust) {
	*buf = c;
	for (i=1; i< length; i++) buf[i] = ' ';
    } else {
	for (i=0; i< length-1; i++) buf[i] = ' ';
	buf[length - 1] = c;
    }
    return length;
}

int
user_PrintString(char * buf, char* s, int length, int ladjust)
{
    int i;
    int len=0;
    char* s1 = s;
    while (*s1++) len++;
    if (length < len) length = len;

    if (ladjust) {
	for (i=0; i< len; i++) buf[i] = s[i];
	for (i=len; i< length; i++) buf[i] = ' ';
    } else {
	for (i=0; i< length-len; i++) buf[i] = ' ';
	for (i=length-len; i < length; i++) buf[i] = s[i-length+len];
    }
    return length;
}

int
user_PrintNum(char * buf, unsigned long u, int base, int negFlag, 
	 int length, int ladjust, char padc, int upcase)
{
    /* 算法说明：
     *  1) 先把数值按进制逐位取模，逆序写入缓冲区；
     *  2) 若需要补齐长度，用 padc 补足（左对齐时强制使用空格）；
     *     注意：负数且右对齐并以 '0' 填充时，'-' 号应位于前缀与数字之间；
     *  3) 若(!ladjust) 需反转整个缓冲区（含填充）；
     *  4) 否则仅反转实际数字部分。
     */

    int actualLength =0;
    char *p = buf;
    int i;

    do {
	int tmp = u %base;
	if (tmp <= 9) {
	    *p++ = '0' + tmp;
	} else if (upcase) {
	    *p++ = 'A' + tmp - 10;
	} else {
	    *p++ = 'a' + tmp - 10;
	}
	u /= base;
    } while (u != 0);

    if (negFlag) {
	*p++ = '-';
    }

    /* figure out actual length and adjust the maximum length */
    actualLength = p - buf;
    if (length < actualLength) length = actualLength;

    /* add padding */
    if (ladjust) {
	padc = ' ';
    }
    if (negFlag && !ladjust && (padc == '0')) {
	for (i = actualLength-1; i< length-1; i++) buf[i] = padc;
	buf[length -1] = '-';
    } else {
	for (i = actualLength; i< length; i++) buf[i] = padc;
    }
	    

    /* prepare to reverse the string */
    {
	int begin = 0;
	int end;
	if (ladjust) {
	    end = actualLength - 1;
	} else {
	    end = length -1;
	}

	while (end > begin) {
	    char tmp = buf[begin];
	    buf[begin] = buf[end];
	    buf[end] = tmp;
	    begin ++;
	    end --;
	}
    }

    /* adjust the string pointer */
    return length;
}
