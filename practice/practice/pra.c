#define _CRT_SECURE_NO_WARNINGS


//习题七-196-1. 产值翻番 /////////////////////////////////////////////////////////////////

//#include<stdio.h>
//
//#define CURRENT 100
//
//int NyearDob(float m,float a)
//{
//	int year = 0;
//	while (m < 200)
//	{
//		m = m + m * (a / 100);
//		year++;
//	}
//	return year;
//
//}
//
//
//int main()
//{
//	float money = CURRENT;
//	int GrowRate[] = { 6,8,10,12 };
//	//int x1 = NyearDob(money,6);
//	//int x2 = NyearDob(money,8);
//	//int x3 = NyearDob(money,10);
//	//int x4 = NyearDob(money,12);
//	/*printf("6c=%d\n8c=%d\n10c=%d\n12c=%d\n", x1, x2, x3, x4);*/
//	for (int i = 0;i < sizeof(GrowRate) / sizeof(GrowRate[0]);++i)
//	{
//		int x = NyearDob(money, GrowRate[i]);
//		printf("增长率为%d%%,增番所需%d年\n", GrowRate[i], x);
//	}
//
//	return 0;
//}
//关键！=使用宏常量#define 近似使用变长数组或使用可能会随情况改变而改变的常量


//习题七-196-2. 递归调用次数////////////////////////////////////////////////////

//#include<stdio.h>
//int count = 0;
//CauFib(int x)
//{
//	count++;
//	//if (x == 1 || 2 == x)
//	//{
//	//	/*++count;*/
//	//	return 1;
//	//}
//
//	if (x == 1) return 1;
//	else if (x == 0) return 0;
//	else
//	{
//		/*++count;*/
//		return CauFib(x - 1) + CauFib(x - 2);
//	}
//}
//
//
//int main()
//{
//	int n = 0;
//	printf("请输入:>");
//	scanf("%d", &n);
//	int x = CauFib(n);
//	printf("Fib(%d)=%d,递归了%d次\n",n,x, count);
//
//	return 0;
//}

//***************************************习题七-196-3. 三位数构成******************************************

////思路 要仔细思考题目 而不是简单看一眼题目，由题目的信息可以直接确定
//		 确定第一个数 然后直接得到对应的第二三数 判定九位是否存同
// 坑：想同时利用九位不同+循环创造三个数，然后再利用 大小关系判定是否成立
// 可以得到：我们要思考 怎样的算法更加容易写 即制造一个条件+判定这个条件 的配置 
// 
// 
//// 第一个三位数 小于 第二个三位数 小于 第三个三位数
////得到此条件可以使后续编程简化
//
//
////1.使用传统方法 利用数组存储1-9
//#include<stdio.h>
//int PD(int x);
//
//int main()
//{
//	//由题 三个三位数每位数字皆不同 估每个三位数的取值范围为123-987
//	//又 第三个三位数为第一个三位数的三倍 即第一个三位数的取值范围为123-329
//	for (int i = 123;i < 330;i++)		//先确定第一个三位数 便可用数乘得到三个三位数
//	{
//
//		if (PD(i))		//函数：用于判断三个三位数共九项 是否存在重复的数 若存 返回0 不存 返回1
//		{
//			printf("%d %d %d\n", i, i * 2, i * 3); //打印最终结果
//		}
//
//	}
//	return 0;
//}
//
//int PD(int x)
//{
//	int a[9] = { 0 };   //创建一个数组用于存储九项
//	a[0] = x / 100;
//	a[1] = x / 10 % 10;
//	a[2] = x % 10;
//	a[3] = (x * 2) / 100;
//	a[4] = (x * 2) / 10 % 10;
//	a[5] = (x * 2) % 10;
//	a[6] = (x * 3) / 100;
//	a[7] = (x * 3) / 10 % 10;
//	a[8] = (x * 3) % 10;
//	for (int i = 0;i < 9;i++)
//	{
//		for (int j = i + 1;j < 9;j++)
//		{
//			if (a[i] == a[j] || a[i] == 0 || a[j] == 0)   //利用循环判定不符要求的数据
//				return 0;
//		}
//	}
//	return 1;     //若不能判定不符要求 就是符合要求 返回1
//}



////2.使用<string.h>下的sprintf()完成
//// int sprintf(char* str,const char* format)
////char* str 接收字符数组的一个地址  const char* format 要写入字符数组的字符串
//// 成功返回写入的字符长度值 失败返回一个负数
////		如写入的字符串""中包含%d等 则 sprintf(str,"%d",a)类似printf
//
//#include<stdio.h>
//#include<string.h>
//int PD2(int x);
//
//int main()
//{
//
//	for (int i = 123;i < 330;i++)
//	{
//		if (PD2(i))			//依旧一个判定是否符合题意的函数 逻辑依旧符合返回1不符合返回0
//		{
//			printf("%d %d %d\n",i, i * 2, i * 3);
//		}
//	}
//	return 0;
//}
//
//int PD2(int x)
//{
//	char a[10] = { '0' };	//字符数组未初始化的空间皆为'\0'  系统会自动在结尾增加'\0'
//							//也就是说写入字符数组时 也要考虑'\0'的长度 因此定义a[10]
//	sprintf(a, "%d", x);
//	sprintf(a+3, "%d", x*2);
//	sprintf(a+6, "%d", x*3);
//	for (int i = 0;i < 9;i++)
//	{
//		for (int j = i + 1;j < 9;j++)
//		{
//			if (a[i] == a[j] || a[i] == '0' || a[j] == '0')   //利用循环判定不符要求的数据
//				return 0;
//		}
//	}
//	return 1;
//}







//3.传统方法二解 采用另类的方法 利用数组存储 此法可简化 最终的判定程序

//#include<stdio.h>
//int PD(int x);
//void P(int x, int a[10]);
//
//
//int main()
//{
//
//	for (int i = 123; i < 330; i++)
//	{
//		if (PD(i))
//		{
//			printf("%d %d %d\n", i, 2 * i, 3 * i);
//		}
//	}
//
//
//	return 0;
//}
//
//int PD(int x)
//{
//	int b[10] = { 0 };
//	P(x,b);
//	P(x*2, b);
//	P(x*3, b);
//	for (int i = 1;i < 10;i++)
//	{
//		if (b[i] == 0) return 0;	//如果存在x位为0 说明没有数写入这里（0写入0位）即存在重复数
//	}
//	return 1;
//}
//
//void P(int x, int a[10])
//{
//	for (int i = 0;i < 3;i++)
//	{
//		a[x % 10] = x % 10;				//将九位数 每位数x输到数组的第x位
//		x /= 10;
//	}
//}














//***************************************************习题七-196-4. 阿姆斯特朗数////////////////

//思路：如何创建一个n位数？ 利用pow(a,x)指数函数 10^n-1 与10^n-1 两数 来创建n位数

//
//#include<stdio.h>
//#include<math.h>
//
//
//int main()
//{
//	int n = 0; long double sum = 0; long long crash = 0;
//	do
//	{
//		printf("输入n (n<=8) :>");
//		scanf("%d", &n);
//
//	} while (!(n > 0 && n <= 8));
//
//	for (long double i = pow(10, n - 1);i < pow(10, n);i++)
//	{
//		crash = i;
//		sum = 0;
//		for (int j = 0;j < n;j++)
//		{
//			sum += pow((long double)(crash % 10), n);
//			crash /= 10;
//		}
//		if (fabs(sum - i) <= 1e-6)
//		{
//			printf("一个阿姆斯特朗数=%ld\n", (long long)sum);
//		}
//		
//	}
//
//	return 0;
//}

/////仍存问题！！！↑




//习题七-196-5. 亲密数/////////////////////////////////////////////////////////////////

//
//#include<stdio.h>
//
//
//int SumPrime(int x)
//{
//	int sum = 0;
//	for (int i = 1;i <= x - 1;++i)
//	{
//		if (x % i == 0)
//		{
//			sum += i;
//		}
//	}
//	return sum;
//}
//
//int main()
//{
//
//	int m = 0, n = 0;
//	printf("Input:>");
//	scanf("%d %d", &m, &n);
//
//	if (SumPrime(SumPrime(n) == n))  printf("是亲密数");
//	else printf("不是亲密数");
//
//	return 0;
//}




//习题七-196-6. 主对角线元素之和///////////////////////////////////////////////


//#include<stdio.h>
//
//
//int main()
//{
//	int sum1 = 0, sum2 = 0;
//	int n = 0; printf("n:>");scanf("%d", &n);
//	int a[400] = { 0 };
//	printf("输入n x n 的矩阵\n");
//	for (int i = 0;i <= n*n-1;++i)
//	{
//		scanf("%d", &a[i]);
//	}
//
//	for (int i = 0;i < n;++i)
//	{
//		sum1 += *(a + (i * n) + i);
//	}
//	for (int i = 0;i < n;++i)
//	{
//		sum2 += *(a + (i * n) + n-1-i);
//	}
//	int sum3 = sum1 + sum2;
//	printf("%d", sum3);
//	return 0;
//}

//习题七-196-7. 矩阵乘法//////////////////////////////////////////////////////////

//
//#include<stdio.h>
//
//int main()
//{
//	int m = 0, n = 0;
//	printf("输入m n\n");
//	scanf("%d %d", &m, &n);
//	printf("输入m x n 列的矩阵\n");
//	int a[100] = { 0 };
//	int b[100] = { 0 };
//	for (int i = 0;i < m * n;++i)
//	{
//		scanf("%d", &a[i]);
//	}
//	printf("输入n x m 列的矩阵\n");
//	for (int i = 0;i < m * n ;++i)
//	{
//		scanf("%d", &b[i]);
//	}
//
//	int x[100] = { 0 };
//
//	int sum = 0;
//	for (int q = 0 ;q<m;++q)
//		{
//		for (int i = 0;i < m;++i)
//			{
//			sum = 0;
//			for (int j = 0; j < n;++j)
//				{
//				sum += a[q*n+j] * b[j * m + i];
//				}
//			x[q*m+i] = sum;
//			}
//		}
//	printf("\n");
//	for (int i = 0;i < m * m;++i)
//	{
//		printf("%-3d", x[i]);
//		if((i+1)%m == 0) printf("\n");
//	}
//	return 0;
//}


//
//#include<stdio.h>
//
//
//void Swap(char* e1, char* e2, int width)
//{
//	for (int i = 0;i < width;i++)
//	{
//		char tem = *e1;
//		*e1 = *e2;
//		*e2 = tem;
//		e1++;
//		e2++;
//	}
//}
//
////冒泡排序Plus	(需要交换函数以及附属功能函数）
////除了对整形排序以外，还可以其他如结构体，字符串等类型排序
////base为待排序数首地址 sz为排序元素 width为一个元素的大小 后者为判定两元素大小的函数
//													//前者大于后者 则返回值>0 其他情况同理
//
//void bubble_sort(void* base, int sz, int width, int (*cmp)(const void* e1,const void* e2))
//{
//	for (int i = 0;i < sz - 1;i++)
//	{
//		for (int j = 0;j < sz - 1 - i;j++)
//		{
//			if ((*cmp)((char*)(base)+(j * width), (char*)(base)+((j + 1) * width)) > 0)
//			{
//				Swap((char*)(base)+(j * width), (char*)(base)+((j + 1) * width), width);
//			}
//		}
//	}
//}
//
////冒泡plus附属函数 作为第四个参数使用
//
////关于int型数据的交换
//int Int(int* e1, int* e2)
//{
//	return *e1 - *e2;
//}
//
//int main()
//{
//	int a[10] = { 1,2,8,6,9,5,4,3,7,0 };
//	bubble_sort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), Int);
//	for (int i = 0;i < sizeof(a) / sizeof(a[0]);i++)
//	{
//		printf("%d ", a[i]);
//	}
//
//	return 0;
//}



//#include<stdio.h>
//
//
//int JS(int n)
//{
//	int sum = 1;
//	for (int x = 1;x <= n;x++)
//	{
//		sum *= x;
//	}
//	return sum;
//}
//
//
//int C(int m, int n)   //JS
//{
//	return JS(m) / (JS(m - n) * JS(n));
//}
//
//
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	int i = 0;
//	int j = 0;
//	for (i = 0;i < n;i++)
//	{
//		for (int x = n - i;x > 0;x--)
//		{
//			printf("  ");
//		}
//		for (j = 0;j <= i;j++)
//		{
//			printf("%-4d", C(i, j));
//		}
//		printf("\n");
//	}
//	return 0;
//}

//
//#include<stdio.h>
//
//int isReqal(int (*arr)[15], int n)
//{
//	int sum = 0;
//	int find = 1;
//	for (int j = 0;j < n;j++)
//	{
//		sum += arr[0][j];
//	}
//	for (int i = 1;i < n && find ;i++)
//	{
//		int sum2 = 0;
//		for (int j = 0;j < n && find ;j++)
//		{
//			sum2 += arr[i][j];
//		}
//		if (sum2 != sum)
//		{
//			find = 0;
//		}
//	}
//	return find;
//}
//
//int isCeqal(int(*arr)[15], int n)
//{
//	int sum = 0;
//	int find = 1;
//	for (int i = 0;i < n;i++)
//	{
//		sum += arr[i][0];
//	}
//	for (int j = 1;j < n && find;j++)
//	{
//		int sum2 = 0;
//		for (int i = 0;i < n && find;i++)
//		{
//			sum2 += arr[i][j];
//		}
//		if (sum2 != sum)
//		{
//			find = 0;
//		}
//	}
//	return find;
//}
//
//int isDeqal(int(*arr)[15], int n)
//{
//	int sum = 0;
//	int sum2 = 0;
//	int find = 1;
//	for (int i = 0;i < n;i++)
//	{
//		sum += arr[i][i];
//	}
//	for (int i = 0;i < n;i++)
//	{
//		sum2 += arr[i][n - i - 1];
//	}
//	if (sum != sum2)
//	{
//		find = 0;
//	}
//	return find;
//}
//
//int main()
//{
//	int n = 0;
//	int arr[15][15] = { 0 };
//	scanf("%d", &n);
//
//	for (int i = 0;i < n;i++)
//	{
//		for (int j = 0;j < n;j++)
//		{
//			scanf("%d", &arr[i][j]);
//		}
//	}
//
//	if (isReqal(arr, n) && isCeqal(arr, n) && isDeqal(arr, n))
//		printf("是\n");
//	else
//		printf("不是\n");
//
//
//	return 0;
//}
//
//
//





