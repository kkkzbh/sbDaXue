/* 中文说明：内核底层格式化输出实现（lp_Print），统一采用中文注释。*/

#include	<print.h> // 中文注释：对外部可见的格式化接口声明

// 中文注释：是否为数字字符的判定
#define		IsDigit(x)	( ((x) >= '0') && ((x) <= '9') )
// 中文注释：字符转十进制数值
#define		Ctod(x)		( (x) - '0')

// 中文注释：前置声明（字符、字符串与数字的具体格式化函数）
extern int PrintChar(char *, char, int, int);
extern int PrintString(char *, char *, int, int);
extern int PrintNum(char *, unsigned long, int, int, int, int, char, int);

// 中文注释：致命错误提示字符串（缓冲越界等）
static const char theFatalMsg[] = "fatal error in lp_Print!";

// 中文注释：底层 printf 的实现，输出由回调函数提供
void
lp_Print(void (*output)(void *, char *, int), 
	 void * arg,
	 char *fmt, 
	 va_list ap)
{

#define 	OUTPUT(arg, s, l)  \
  { if (((l) < 0) || ((l) > LP_MAX_BUF)) { \
       (*output)(arg, (char*)theFatalMsg, sizeof(theFatalMsg)-1); for(;;); \
    } else { \
      (*output)(arg, s, l); \
    } \
  }
    
    char buf[LP_MAX_BUF]; // 中文注释：临时输出缓冲

    char c; // 中文注释：字符临时变量
    char *s; // 中文注释：字符串临时变量
    long int num; // 中文注释：整数临时变量

    int longFlag; // 中文注释：长整型标志
    int negFlag; // 中文注释：负号标志
    int width; // 中文注释：最小宽度
    int prec; // 中文注释：精度
    int ladjust; // 中文注释：左对齐标志
    char padc; // 中文注释：填充字符

    int length; // 中文注释：本次输出长度

    for(;;) { // 中文注释：主循环，逐段处理格式串
	{ 
	    // 中文注释：扫描到下一个 '%'，在此之前的普通字符直接输出
	    while (*fmt != '\0' && *fmt != '%') {
	    	OUTPUT(arg, fmt, 1); // 中文注释：输出单个普通字符
		fmt++; // 中文注释：前进到下一个字符
	    }
	    
	    // 中文注释：格式串结束则退出
	    if (*fmt == '\0') {
		break; // 中文注释：跳出外层 for 循环
	    }
	}

	// 中文注释：处理格式化说明符
	if (*fmt == '%') {
	    fmt++; // 中文注释：跳过 '%'
	    ladjust = 0; // 中文注释：默认右对齐
	    padc = ' '; // 中文注释：默认空格填充
	    if (*fmt == '-') { // 中文注释：左对齐
		ladjust = 1;
		fmt++;
	    }	
	    else if (*fmt == '0') { // 中文注释：使用 '0' 作为填充
		padc = '0';
		fmt++;
	    }

	    width = 0; // 中文注释：解析最小宽度
	    while (IsDigit(*fmt)) {
		width *= 10; // 中文注释：累积位数
		width += Ctod(*fmt); // 中文注释：转换为数字
		fmt++; // 中文注释：继续读取宽度
	    }

	    if (*fmt == '.') { // 中文注释：解析精度
		prec = 0;
		fmt++;
		while (IsDigit(*fmt)) {
		    prec *= 10; // 中文注释：累积精度
		    prec += Ctod(*fmt);
		    fmt++;
		}
	    }
	    // 中文注释：可选长整型前缀
	    if (*fmt == 'l') {
		longFlag = 1;
		fmt++;
	    }
	
	    // 中文注释：根据格式字符分发
	negFlag = 0;
	switch (*fmt) {
	 case 'b': // 中文注释：二进制输出
	    if (longFlag) { 
		num = va_arg(ap, long int); 
	    } else { 
		num = va_arg(ap, int);
	    }
	    length = PrintNum(buf, num, 2, 0, width, ladjust, padc, 0); // 中文注释：基数 2
	    OUTPUT(arg, buf, length);
	    break;

	 case 'd': // 中文注释：有符号十进制
	 case 'D':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    if (num < 0) { // 中文注释：处理负号
		num = - num;
		negFlag = 1;
	    }
	    length = PrintNum(buf, num, 10, negFlag, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'o': // 中文注释：八进制
	 case 'O':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = PrintNum(buf, num, 8, 0, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'u': // 中文注释：无符号十进制
	 case 'U':
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = PrintNum(buf, num, 10, 0, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;
	    
	 case 'x': // 中文注释：小写十六进制
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = PrintNum(buf, num, 16, 0, width, ladjust, padc, 0);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'X': // 中文注释：大写十六进制
	    if (longFlag) { 
		num = va_arg(ap, long int);
	    } else { 
		num = va_arg(ap, int); 
	    }
	    length = PrintNum(buf, num, 16, 0, width, ladjust, padc, 1);
	    OUTPUT(arg, buf, length);
	    break;

	 case 'c': // 中文注释：字符
	    c = (char)va_arg(ap, int);
	    length = PrintChar(buf, c, width, ladjust);
	    OUTPUT(arg, buf, length);
	    break;

	 case 's': // 中文注释：字符串
	    s = (char*)va_arg(ap, char *);
	    length = PrintString(buf, s, width, ladjust);
	    OUTPUT(arg, buf, length);
	    break;

	 case '\0': // 中文注释：意外的字符串结束
	    fmt --; // 中文注释：回退以便外层 ++ 对齐
	    break;

	 default:
	    OUTPUT(arg, fmt, 1); // 中文注释：未识别的格式字符，按原样输出
	}	// 中文注释：switch 结束
}
	fmt ++; // 中文注释：移动到下一个字符后继续循环
    }		// 中文注释：for(;;) 主循环结束

    OUTPUT(arg, "\0", 1); // 中文注释：发送终止标记给输出回调
}


/* --------------- local help functions --------------------- */
int
PrintChar(char * buf, char c, int length, int ladjust)
{
    int i; // 中文注释：循环变量
    
    if (length < 1) length = 1; // 中文注释：最小宽度为 1
    if (ladjust) { // 中文注释：左对齐
	*buf = c; // 中文注释：首位放字符
	for (i=1; i< length; i++) buf[i] = ' '; // 中文注释：其余填空格
    } else { // 中文注释：右对齐
	for (i=0; i< length-1; i++) buf[i] = ' '; // 中文注释：前置空格
	buf[length - 1] = c; // 中文注释：末位放字符
    }
    return length; // 中文注释：返回输出长度
}

int
PrintString(char * buf, char* s, int length, int ladjust)
{
    int i; // 中文注释：循环变量
    int len=0; // 中文注释：字符串长度
    char* s1 = s; // 中文注释：遍历指针
    while (*s1++) len++; // 中文注释：计算长度
    if (length < len) length = len; // 中文注释：保证输出宽度不小于字符串长度

    if (ladjust) { // 中文注释：左对齐：先内容后空格
	for (i=0; i< len; i++) buf[i] = s[i]; // 中文注释：拷贝内容
	for (i=len; i< length; i++) buf[i] = ' '; // 中文注释：补齐空格
    } else { // 中文注释：右对齐：先空格后内容
	for (i=0; i< length-len; i++) buf[i] = ' '; // 中文注释：填充空格
	for (i=length-len; i < length; i++) buf[i] = s[i-length+len]; // 中文注释：从末尾对齐拷贝
    }
    return length; // 中文注释：返回输出长度
}

int
PrintNum(char * buf, unsigned long u, int base, int negFlag, 
	 int length, int ladjust, char padc, int upcase)
{
    // 中文注释：反向生成数字串；根据对齐与填充修饰；必要时反转

    int actualLength =0; // 中文注释：实际长度
    char *p = buf; // 中文注释：写指针
    int i; // 中文注释：循环变量

    do { // 中文注释：逐位取模写入字符
	int tmp = u %base; // 中文注释：当前位
	if (tmp <= 9) {
	    *p++ = '0' + tmp; // 中文注释：数字 0-9
	} else if (upcase) {
	    *p++ = 'A' + tmp - 10; // 中文注释：大写 A-F
	} else {
	    *p++ = 'a' + tmp - 10; // 中文注释：小写 a-f
	}
	u /= base; // 中文注释：除以基数前进
    } while (u != 0); // 中文注释：直至全部位被处理

    if (negFlag) { // 中文注释：记录负号
	*p++ = '-';
    }

    actualLength = p - buf; // 中文注释：计算实际长度
    if (length < actualLength) length = actualLength; // 中文注释：宽度至少为实际长度

    if (ladjust) { // 中文注释：左对齐时填充统一为空格
	padc = ' ';
    }
    if (negFlag && !ladjust && (padc == '0')) { // 中文注释：右对齐且 0 填充，减号应放在最右侧
	for (i = actualLength-1; i< length-1; i++) buf[i] = padc; // 中文注释：从当前位置到倒数第二位填充
	buf[length -1] = '-'; // 中文注释：最后一位写减号
    } else {
	for (i = actualLength; i< length; i++) buf[i] = padc; // 中文注释：常规填充
    }
	    

    { // 中文注释：反转指定范围
	int begin = 0; // 中文注释：起始
	int end; // 中文注释：结束
	if (ladjust) {
	    end = actualLength - 1; // 中文注释：左对齐仅反转有效内容
	} else {
	    end = length -1; // 中文注释：右对齐包含填充一起反转
	}

	while (end > begin) { // 中文注释：首尾交换
	    char tmp = buf[begin];
	    buf[begin] = buf[end];
	    buf[end] = tmp;
	    begin ++;
	    end --;
	}
    }

    return length; // 中文注释：返回输出长度
}
