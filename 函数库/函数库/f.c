

#include "f.h"

//素数函数

#include<math.h>
int Z(int n)
{
	for (int i = 2;i <= sqrt(n) || n == 1;i++)
	{
		if (n % i == 0 || n == 1) return 0;
	}
	return 1; //素数返回1
}

//GCD最大公约数函数

int GCD(int a, int b)
{
	int max0 = a > b ? a : b;
	int max = 0;
	for (int i = 1;i <= max0;i++)
	{
		if (a % i == 0 && b % i == 0)
		{
			max = i;
		}
	}
	return max;
}

//LCM最小公倍数函数

int LCM(int a, int b)
{
	int max0 = a > b ? a : b;
	for (int i = max0;;i++)
	{
		if (i % a == 0 && i % b == 0)
		{
			return i;
		}
	}

}


//阶乘函数 返回阶乘值

int JS(int n)
{
	int sum = 1;
	for (int x = 1;x <= n;x++)
	{
		sum *= x;
	}
	return sum;
}


// 包括1的因子之和

int SumPrime(int x)
{
	int sum = 0;
	for (int i = 1;i <= x - 1;++i)
	{
		if (x % i == 0)
		{
			sum += i;
		}
	}
	return sum;
}

//返回位数函数

#include<math.h>
int WS(int x)
{
	x = x > 0 ? x : -x;
	for (int i = 1;i <= 999;i++)
	{
		if (x >= pow(10, i - 1) && x < pow(10, i))
		{
			return i;
		}
		else if (x == 0)
		{
			return 1;
		}
	}
}

//组合数函数 配合JS阶乘函数使用
int C(int m, int n)   //JS
{
	return JS(m) / (JS(m - n) * JS(n));
}

//指数函数 返回double的值
double myPOW(int x, int n)
{
	int a = x;
	for (int i = 1;i < n;i++)
	{
		x *= a;
	}
	return x;

}

//冒泡排序算法
//每一次的冒泡 会将最大值泡到最右边
void BubbleSort(int* arr,int sz)  //接收数组arr与数组长度sz
{
	for (int i = 0;i < sz-1;i++)
	{
		for (int j = 0;j < sz - 1 - i;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				arr[j] = arr[j] ^ arr[j + 1];
				arr[j + 1] = arr[j] ^ arr[j + 1];
				arr[j] = arr[j] ^ arr[j + 1];
			}
		}
	}
}


//欧几里得-辗转相除法-求最大公约数

int GCD2(int x, int y)
{
	int max = x > y ? x : y;
	int min = x > y ? y : x;
	int r = 0;
	do
	{
		r = max % min;
		max = min;
		min = r;

	} while (r);
	return max;
}


//交换函数 交换两个值
//逐字节的交换 这里采用char 作为中间变量类型 去实现逐字节交换两值	char本质上也是一字节的二进制数

void Swap(char* e1, char* e2,int width)
{
	for (int i = 0;i < width;i++)
	{
		char tem = *e1;
		*e1 = *e2;
		*e2 = tem;
		e1++;
		e2++;
	}
}

//冒泡排序Plus	(需要交换函数以及附属功能函数）
//除了对整形排序以外，还可以其他如结构体，字符串等类型排序
//base为待排序数首地址 sz为排序元素 width为一个元素的大小 后者为判定两元素大小的函数
													//前者大于后者 则返回值>0 其他情况同理
//此函数调用情况与qsort()函数类似 该函数包含于头文件<stdlib.h>

void bubble_sort(void* base, int sz, int width, int (*cmp)(void* e1, void* e2))
{
	for (int i = 0;i < sz - 1;i++)  //共排序次数
	{
		for (int j = 0;j < sz - 1 - i;j++)  //一次排序的循环
		{
			if ((*cmp)((char*)(base)+(j * width), (char*)(base)+((j + 1) * width)) < 0)
			{
				Swap((char*)(base)+(j * width), (char*)(base)+((j + 1) * width),width);
			}
		}
	}
}

//冒泡plus附属函数 作为第四个参数使用 这里由使用者编写 这里写出两个

//关于int型数据的交换

int Int(int* e1, int* e2)
{
	return *e1 - *e2;
}

//关于字符串数据的交换(需用到附属函数Strcmp 用于比较字符串大小)

int Str(char* e1, char* e2)
{
	while (!(*e1 - *e2) && *e1)
	{
		e1++;
		e2++;
	}
	return *e1 - *e2;
}


//生成一个n x n 阶 奇数幻方矩阵

void GenerateMagicSquare(int(*arr)[NN], int n)
{
	int row = 0;
	int cow = (n - 1) / 2;
	arr[row][cow] = 1;

	for (int i = 2;i <= n * n;i++)
	{
		int r = row;
		int c = cow;
		row = (row + n-1) % n;
		cow = (cow + 1) % n;
		
		if (arr[row][cow] == 0)
		{
			arr[row][cow] = i;
		}
		else
		{
			row = (r + 1) % n;
			cow = c;
			arr[row][cow] = i;
		}
	}

}

//生成杨辉三角

//函数→赋值杨辉三角

void ini_yang(int (*arr)[NN], int n)
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j <= i;j++)
		{
			if (j == 0 || j == i)
			{
				arr[i][j] = 1;
			}
			else
			{
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
			}
		}
	}
}

//函数→以金字塔打印杨辉三角
#include<stdio.h>
void print_yang(int (*arr)[NN], int n)
{
	for (int i = 0;i < n;i++)
	{
		for (int j = n - 1 - i;j > 0;j--)
		{
			printf("  ");
		}
		for (int j = 0;j <= i;j++)
		{
			printf("%-4d", arr[i][j]);
		}
		printf("\n");
	}
}

//以半三角形式打印杨辉三角
void print_yang_b(int(*arr)[NN], int n)
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j <= i;j++)
		{
			printf("%-4d", arr[i][j]);
		}
		printf("\n");
	}
}

//以杨辉三角得出FIB
void yang_fib(int(*arr)[NN], int *Fib ,int n)
{
	for (int i = 0;i < n;i++)
	{
		Fib[i] = 0;
		for (int j = i , row = 0;j >= 0; row++,j--)
		{
			Fib[i] += arr[row][j];
		}
	}
}

//以一行形 打印FIB
void printYfib(int* Fib, int n)
{
	printf("Fibonacci:  ");
	for (int i = 0;i < n;i++)
	{
		printf("%-4d", Fib[i]);
	}
}

//提取自然数n以内含n的素数,并整齐放在数组中 (从0开始)
//但 不使用 素数函数的算法

#include<math.h>
void getZ(int *arr, int n)
{
	int a[NN] = { 0 };
	for (int i = 2;i <= n;i++)
	{
		a[i] = i;
	}
	for (int i = 2;i <= sqrt(n);i++)
	{
		for (int j = i + 1;j <= n;j++)
		{
			if (a[i] && a[j] && a[j] % a[i] == 0)
			{
				a[j] = 0;
			}
		}
	}
	int count = 0;
	for (int i = 2;i <= n;i++)
	{
		if (a[i])
		{
			arr[count++] = a[i];
		}
	}
}


//生成 n x n 蛇形矩阵

void IniSnakeSquare(int(*arr)[NN], int n)
{
	int count = 0;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j <= i;j++)
		{
			if (i % 2)  //左下  注意数组里是第0根开始 平时我们可能看第一根 可以计数从0记起
			{
				arr[j][i - j] = ++count;
			}
			else  //从绝对第一根开始！
			{
				arr[i - j][j] = ++count;
			}
		}
	}
	for (int i = n; i < 2 * n - 1;i++)
	{
		for (int j = 0; j < 2 * n - i - 1; j++)
		{
			if (i % 2)  //左下
			{
				arr[i - n + 1+j][n - 1-j] = ++count;
			}
			else
			{
				arr[n - 1-j][i - n + 1+j] = ++count;
			}
		}
	}
}

 
// 打印 n x n 矩阵

void printNxN(int(*arr)[NN], int n)
{
	for (int i = 0; i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			printf("%-4d", arr[i][j]);
		}
		printf("\n");
	}
}


//秦九韶算法 - 计算一元n次多项式 - 递推12 递归3

//递推 第一次所写  利用 x^n+1 = x^n * x 使每一次的幂x 用一次乘法得出

double Qinxn1(int n, double *arr, double x)
{
	double sum = 0;
	double y = 1;
	for (int i = n;i>=0 ;i--)
	{
		sum += arr[i] * y;
		y *= x;
	}
	return sum;
}

//递推 改良  // (a0x+a1)x+a2)x+a3)x+a4).......)x+an   化简形式

double Qinxn2(int n, double* arr, double x)
{
	double sum = arr[0];
	for (int i = 1;i <= n;i++)
	{
		sum = sum * x + arr[i];
	}
	return sum;
}

//递归 - 函数 //注意每次递归所传的参数 到底是改变了什么 以及函数所作的形式

double Qinxn3(int n, double* arr, double x)
{
	if (n == 0) return arr[n];
	return Qinxn3(n-1, arr, x) * x + arr[n];
}

//汉诺塔 - 移动n 要几步 返回几步 (n<=64 否则数值溢出)

unsigned long long Hanoi(int n)
{
	if (n == 1)
		return 1;
	else
		return 2 * Hanoi(n - 1) + 1;
}

//输入n个一维数组

void IniArr1(int *arr, int n)
{
	printf("Input Array :\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
}

//输出n个一维数组

void PriArr1(int* arr, int n)
{
	for (int i = 0;i < n;i++)
	{
		printf("%-4d", arr[i]);
	}
}

//交换排序

void ExchangeSort(int* arr, int n)
{
	for (int i = 0; i < n-1;i++)
	{
		for (int j = i + 1; j < n;j++)
		{
			if (arr[i] > arr[j])
			{
				arr[i] = arr[i] ^ arr[j];
				arr[j] = arr[i] ^ arr[j];
				arr[i] = arr[i] ^ arr[j];
			}
		}
	}
}

//选择排序

void SelectionSort(int* arr, int n)
{
	for (int i = 0; i < n - 1;i++)
	{
		int temp = i;
		for (int j = i + 1; j < n;j++)
		{
			if (arr[temp] > arr[j])
			{
				temp = j;
			}
		}
		if (temp != i)
		{
			arr[i] = arr[i] ^ arr[temp];
			arr[temp] = arr[i] ^ arr[temp];
			arr[i] = arr[i] ^ arr[temp];
		}
	}
}


//产生一个标记数组
//通过标记数组 可以迅速判断一个数组内是否含有指定的数

void RemarkArr(const int* arr, const int n, int* brr)
{
	for (int i = 0; i < n;i++)
	{
		brr[arr[i]]++;
	}
}

//线性查找
//查找一个数组中是否含有一个数 并返回它的下标值 如果没有 返回-1

int LineFind(int* arr, int n, int Find)
{
	for (int i = 0;i < n;i++)
	{
		if (arr[i] == Find)
		{
			return i;
		}
	}
	return -1;
}


//找0排序
//将数组中0 提到前方 其余顺序不变

void Zerofront(int* arr, int n)
{
	for (int i = 0,x = 0; x<n ;i++ )
	{
		for (x = i + 1;arr[x] && x<n ;x++);
		if (x < n)
		{
			for (int j = x;j > i;j--)
			{
				arr[j] = arr[j] ^ arr[j - 1];
				arr[j - 1] = arr[j] ^ arr[j - 1];
				arr[j] = arr[j] ^ arr[j - 1];
			}
		}
	}
}


//找出数组的最大值 返回其下标

int MaxFind(int* arr, int n)
{
	int max = 0;
	for (int i = 1; i < n;i++)
	{
		if (arr[i] > arr[max])
		{
			max = i;
		}
	}
	return max;
}


//找出数组的最小值 返回其下标

int MinFind(int* arr, int n)
{
	int max = 0;
	for (int i = 1; i < n;i++)
	{
		if (arr[i] < arr[max])
		{
			max = i;
		}
	}
	return max;
}

//找出数组的众数
//返回众数值

int ModeFind(int* arr, int n, int max)
{
	int b[NNN] = { 0 };
	for (int i = 0; i < n;i++)
	{
		b[arr[i]]++;
	}
	return MaxFind(b, n);
}

//找出数组的中位数
//返回中位数(计算中位数前需要对数值排序！)

int MedianFind(const int* arr, int n)
{
	int b[NN] = { 0 };
	for (int i = 0;i < n;i++)
		b[i] = arr[i];
	SelectionSort(b, n);
	return n % 2 ? b[n / 2] : (b[n / 2] + b[n / 2 - 1]) / 2;
}


// 计算 M x N 矩阵种元素的最大值及其下标
// 返回一个ret数组 ret[max , 行 , 列 ]

void FindMNmax(int m, int n, int(*arr)[NN], int ret[3])
{
	int max = arr[0][0];
	int x = 0, y = 0;
	for (int i = 0; i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (arr[i][j] > max)
			{
				max = arr[i][j];
				x = i;
				y = j;
			}
		}
	}
	ret[0] = max;
	ret[1] = x;
	ret[2] = y;
}

//输入一个 M x N 的矩阵

void IniMN(int m, int n, int (*arr)[NN])
{
	printf("请输入 M x N 矩阵 >:\n");
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}
}


//寻找矩阵鞍点(所在行的最大值 也是 所在列的最小值)
//返回鞍点个数 鞍点值保存在 ret 中


int FindSaPoint(int m, int n, int(*arr)[NN], int* ret)
{
	int count = 0;
	int cow = 0;
	for (int i = 0;i < m;i++)
	{
		cow = MaxFind(arr[i], n);
		int find = 0;
		for (int j = 0;j < n && !find ;j++)
		{
			if (arr[j][cow] < arr[i][cow])
			{
				find = 1;
			}
		}
		if (!find)
		{
			ret[count++] = arr[i][cow];
		}
	}
	return count;
}


//卡布列克运算
//一个四位数 如果各位不相等 按从大到小(Max) 和从小到大(Min) 重排两个数 做差（有0置顶就是三位数）
//不断重复 最后得到 6174
// 展示过程



void Cablake(int n)
{
	int a[4] = { 0 };
	int x = 0;
	int max = 0, min = 0;
	int count = 0;
	while (n != 6174)
	{
		x = n;
		max = min = 0;
		for (int i = 0;i < 4;i++)
		{
			a[i] = x % 10;
			x /= 10;
		}
		SelectionSort(a, 4);
		for (int i = 0;i < 4;i++)
		{
			max += a[3-i] * pow(10, 3 - i);
			min += a[i] * pow(10, 3-i);
		}
		n = max - min;
		count++;
		printf("[%d] : %d - %d = %d\n", count, max, min, n);
	}
}


//合并两个升序数列（按序)

void CombineArr(int* a, int* b, int m, int n, int* c)
{
	int x = 0;
	int y = 0;
	int count = -1;
	int find = 0;
	while (x < m && y < n)
	{
		find = a[x] / b[y];  // 等价 a[x] < a[y]

		if (!find) 
		{
			c[++count] = a[x];
			x++;
		}
		else
		{
			c[++count] = b[y];
			y++;
		}
	}

	find = a[m-1] >= b[n-1] ? 1 : 0; // x = m ? y = n ?
	//因为上面跳出循环条件为 x<m && y<n 所以检验下x与y的值即可判断

	if(find)
		for (;x < m;x++)
		{
			c[++count] = a[x];
		}
	else
		for (;y < n;y++)
		{
			c[++count] = b[y];
		}
}



//将数组中0后置
//返回非0的最大下标

int ZeroBack(int* arr, int n)
{
	int count = 0;
	for (int i = 0, x = 0; x >= 0;i++)
	{
		for (x = n-1-i ;arr[x] && x >= 0;x--);
		if (x >= 0)
		{
			count++;
			for (int j = x;j < n-1-i;j++)
			{
				arr[j] = arr[j] ^ arr[j + 1];
				arr[j + 1] = arr[j] ^ arr[j + 1];
				arr[j] = arr[j] ^ arr[j + 1];
			}
		}
	}
	return n - 1 - count;
}

//将数组中重复的数置0(置前面的数为0)

void EqalZero(int* arr, int n)
{
	for (int i = 0;i < n-1;i++)
	{
		if (arr[i] == arr[i+1])
		{
			arr[i] = 0;
		}
	}
}


//在原数排列上 排列成 一个在所有可能排列情况上 仅比原排列大的排列
//排则返回1 没排返回0


int BigPointSort(int* arr, int n)
{
	int find = 0;
	for (int i = n - 2;i >= 0 && !find ;)
	{
		int mid = i+1;
		for (int j = i +1;j < n;j++)
		{
			if (arr[j] > arr[i] && arr[j] <= arr[mid])
			{
				mid = j;
			}
		}
		if (arr[i] < arr[mid])
		{
			arr[i] = arr[i] ^ arr[mid];
			arr[mid] = arr[i] ^ arr[mid];
			arr[i] = arr[i] ^ arr[mid];
			find = 1;
		}
		else
			i--;
	}
	return find;
}


//--展示上面函数排列过程--

void ShowBpS(int* arr, int n)
{
	int count = 0;
	for (printf("\n--------\n"); BigPointSort(arr, n) ;printf("\n"))
	{
		printf("[%d] :", ++count);
		PriArr1(arr, n);
	}
}


//Strcmp 比较两个字符串大小
//返回值
//			dst < src 返回 <0
//			dst = src 返回 0
//			dst > src 返回 >0

int Strcmp(const char* dst, const char* src)
{
	while (!(*dst - *src) && *dst)
	{
		dst++;
		src++;
	}
	return *dst - *src;
}

//Strncmp 比较两个字符串前n个的大小

int Strncmp(const char* dst, const char* src, size_t n)
{
	while (n && !(*dst - *src) && *dst)
	{
		dst++;
		src++;
		n--;
	}
	return *dst - *src;
}


//Strcpy 拷贝src字符串到dst
//返回dst


char* Strcpy(char* dst, const char* src)
{
	char* str = dst;
	while (*dst++ = *src++);
	return str;
}


//Strncpy 拷贝src中n个字符到dst
//返回dst


char* Strncpy(char* dst, const char* src, size_t n)
{
	char* str = dst;
	while (n-- && (*dst++ = *src++));
	while (n--)
	{
		*dst++ = '\0';
	}
	return str;
}


//Strcat 追加拷贝字符串 延长原字符串
//返回dst

char* Strcat(char* dst, const char* src)
{
	char* str = dst;
	while (*dst)
		dst++;
	while (*dst++ = *src++);
	return str;
}

//Strncat 追加拷贝字符串n个字符

char* Strncat(char* dst, const char* src , size_t n)
{
	char* str = dst;
	while (*dst)
		dst++;
	while (n-- && (*dst++ = *src++));
	if (++n)
		*dst = '\0';
	return str;
}


//Strlen 求字符串长度大小

size_t Strlen(char* str)
{
	char* start = str;
	while (*str)
		str++;
	return str - start;
}

//Strstr 在字符串中寻找字符串

char* Strstr(const char* dst, const char* src)
{
	if (!(*src))
		return (char*)dst;
	while (*dst)
	{
		const char* start = dst;
		const char* source = src;
		while (*src && (*dst++ == *src++))
		if (!(*src))
			return (char*)start;
		dst = ++start;
		src = source;
	}
	return (NULL);
}


//Strtok 按某字符 分割字符串（将某字符替换成\0）
//分割成功 保存分割点 返回

char* Strtok(char* str, const char* sep)
{
	static char* sep_point = (NULL);
	if (str)
	{
		char* s1 = str;
		while (*s1)
		{
			const char* s2 = sep;
			while (*s2)
			{
				if (!(*s2 - *s1))
				{
					*s1 = '\0';
					sep_point = s1+1;
					return str;
				}
				s2++;
			}
			s1++;
		}
		sep_point = s1;
		return str;
	}
	else
	{
		if (sep_point && !*sep_point)
			return (NULL);
		char* s1 = str = sep_point;
		while (*s1)
		{
			const char* s2 = sep;
			while (*s2)
			{
				if (!(*s2 - *s1))
				{
					*s1 = '\0';
					sep_point = s1+1;
					return str;
				}
				s2++;
			}
			s1++;
		}
		sep_point = s1;
		return str;
	}
}


//Memcpy拷贝src内存的n字节空间到dst所指处

void* Memcpy(void* dst, const void* src, size_t n)
{
	char* s1 = (char*)dst;
	const char* s2 = (const char*)src;
	while (n--)
		*s1++ = *s2++;
	return dst;
}


//Memmove 移动src指向的内存的n字节空间 到 dst指向的内存处

void* Memmove(void* dst,const void* src, size_t n)
{
	char* s1 = (char*)dst;
	const char* s2 = (const char*)src;
	if (s1 > s2 ? 1 : 0)
		while (n--)
			*(s1 + n) = *(s2 + n);
	else
		while (n--)
			*s1++ = *s2++;
	return dst;
}


//Memcmp 比较两块内存指定字节数量的大小 逐个字节比较
// 大于返回1 小于返回-1 相等返回0 

void* Memcmp(const void* s1, const void* s2, size_t num)
{
	int ret = 0;
	while (num-- && !(ret = (*((const char*)s1)++) - *((const char*)s2)++));
	return (ret > 0) - (ret < 0);
}

int Gcd(int a, int b)
{
	if (a <= 0 || b <= 0)
		return -1;
	if (a == b)
		return a;
	else
	{
		int c = a > b ? a : b;
		int d = a > b ? b : a;
		return GCD(c - d, d);
	}
}

//输入一个整数 打印其二进制形式

void bbb(int n)
{
	std::print("{:b}",n);
}


