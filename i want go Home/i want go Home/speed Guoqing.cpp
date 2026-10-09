#define _CRT_SECURE_NO_WARNINGS


//#include <conio.h>
//#include<stdio.h>
//#include<string.h>
//#include<windows.h>
//#include <stdio.h>
//
//int main()
//{
//	int a = 0;
//
//	int b = 1;
//
//
//		while (b > 0)
//		{
//			a++;
//
//			if (a % 2 == 1 && a<=100)
//				printf("%d\n", a);
//
//
//	int i = 0;
//
//		while (i <= 100 )
//		{
//			if (i % 2 == 1)
//			{
//				printf("%d\n", i);
//			}
//			i++;
//		}
//
//	int ch = 0;
//	while ((ch = getchar()) != EOF)
//	{
//		putchar(ch);
//	}
//
//	int	a = 5;
//	putint(a);
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//sizeof怎么用的

//int main()
//{


	//printf("%d\n", sizeof(char));
	//printf("%d\n", sizeof(int));
	//printf("%d\n", sizeof(short));


///////////////////////////////////////////////////////////////////////////////////////////



//输入一个小写转大写的程序


	//char c = 'a';
	//printf("请输入一个小写字母\n");
	//scanf("%c", &c)
	//	c= 'c'-32;
	//printf("%c", c);

	//char c ;
	//	printf("请输入一个小写字母\n");
	//	printf("我来输出它的大写字母\n");
	//	scanf("%c ", &c);

		//while (c < 97 || c >122)
		//{
		//	printf("不是说让你输小写字母？？？？\n");
		//

		//	scanf("%c", &c);
		//}
		//c = c - 32;

		//scanf("%c", &c);

		//printf("%c\n", c);






///////////////////////////////////////////////////////////////////////////////////////////////////

















//////////////////////////////////////////////////////////////////////////////////////////////////


	//char ch = getchar();

	//ch = ch + 32;

	//putchar(ch);

	//putchar('\n');

	//putchar('a');




	//char ch = getchar();

	//putchar(ch);



	//char ch = '-1';
	//putchar(ch);




	//int a = 0;
	////scanf(" %d", &a);

	//a = getchar();

	//putchar(a);


	//int a =  3;
	//

	//float c = (float) a / 2;


	//printf(" %f\n", c);


	//int b = 5 / 2;
	//printf(" %d\n", b);


	//int a = 0, b = 0;
	//scanf("%d %d", &a, &b);

	//printf("%d\n%d\n", a, b);
	//char a = 2;
	//char b = 1;
	//char c;
	//scanf("%c %c", &a,&b);
	//scanf("%c", &a);


	//scanf(" %c %c", &b,&c);


	//printf("%c", a);
	//printf("%c", b);
	//printf("%c", c);
//
// 
// /////////////////////////////////////////////////////////////////////////////////////////////////////
//
// #include<stdio.h>
// 
// 手撕行列式
//#include<stdio.h>
//
//
//int main()
//{
//
//	printf("三阶行列式真几把难算\n");
//	printf("输入系数以及常数，给他手撕了\n");
//	double a, b, c, d, e, f, g, h, i, j, k, l, m, n, x, y, z;
//	double D;
//	double D1, D2, D3;
//
//	double x1, x2, x3;
//
//	printf("您想算根还是算解？\n");
//	printf("输入1算根 输入2只选系数D>:");
//	int A = 0;
//	scanf(" %d", &A);
//
//	if (A == 1)
//	{
//		printf("请按行列式格式输入数据\n");
//		printf("如 1 2 3 4然后按下回车\n");
//		scanf(" %lf %lf %lf %lf", &a, &b, &c, &x);
//		scanf(" %lf %lf %lf %lf", &d, &e, &f, &y);
//		scanf(" %lf %lf %lf %lf", &g, &h, &i, &z);
//
//		D = a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
//		D1 = x * e * i + b * f * z + c * y * h - c * e * z - b * y * i - x * f * h;
//		D2 = a * y * i + x * f * g + c * d * z - c * y * g - x * d * i - a * f * z;
//		D3 = a * e * z + b * y * g + x * d * h - x * e * g - b * d * z - a * y * h;
//
//
//		x1 = D1 / D; x2 = D2 / D; x3 = D3 / D;
//
//		printf("x1=%lf x2=%lf x3=%lf", x1, x2, x3);
//
//		printf("\n可算踏马给他手撕了！\n");
//	}
//
//	if (A == 2)
//	{
//		scanf(" %lf %lf %lf", &a, &b, &c);
//		scanf(" %lf %lf %lf", &d, &e, &f);
//		scanf(" %lf %lf %lf", &g, &h, &i);
//
//		double X;
//
//		X = a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
//
//		printf("D=%lf", X);
//
//		printf("\n手撕了就是爽！\n");
//
//
//
//
//	}
//	return 0;
//}
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////



//计算阶乘
//int main()
//{
//	int a = 0;
//	int b = 0;
//	int c = 0;
//
//	printf("输入一个数以计算它的阶乘\n");
//
//	scanf(" %d", &a);
//	b = a;
//	do
//	{
//		b--;
//		a =a * b;
//
//	} while(b>1);
//		
//
//	printf("%d", a);
//
//
//	return 0;
//}

//#include<math.h>
//int main() 
//{
//	int a = 1;
//	int b = 1;
//
//	a = 1!+ 2!+ 3!+ 4!+ 5!+ 6!+ 7!+ 8!+ 9!+ 10!;
//	printf(" %d", a);
//
//
//
//	return 0;
//}



/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

//左值为表达式会报错

//int main()
//{
//	int a = 0;
//	int b = 0;
//
//	a = a + b = 2;
//
//
//
//	
//
//	return 0;
//}



///////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//二分算法
//int main()
//{
//	int a[20] = { 1,2,3,4,5,6,7,8,9,11,12,13,14 };
//	int k = 10;
//	int left = 0, right = sizeof(a)/sizeof(a[1]);
//	int mid = 0;
//
//	while (left <= right)
//	{
//		mid = (left + right) / 2;
//
//		if (a[mid] < k)
//		{
//			left = mid + 1;
//		}
//		else	if (a[mid] > k)
//		{
//			right = mid - 1;
//		}
//		else
//		{
//			printf("该数据位于>:%d", mid);
//			break;
//		}
//	}
//
//	if (left > right)
//	{
//		printf("并未从数组中找到指定数据");
//	}
//	return 0;
//	}


//////////////////////////////////////////////////////////////////////////////////////////////////
//#include<stdio.h>
//#include<string.h>
//#include<windows.h>
//#include<stdlib.h>
//
//int main()
//{
//	char arr1[] = "I want go Home!!!";     //创建一个想打印的数组
//	char arr2[] = "                 ";     //创建一个空数组，以上面的数组一个个往下放
//										   //从而实现动态效果
//	int left = 0;
//	int right = strlen(arr2)-1;
//		//(sizeof(arr1) / sizeof(arr1[1]))-2  ;   //strlen(arr2)-1;
//	while (left <= right)
//	{
//		arr2[left] = arr1[left];
//		arr2[right] = arr1[right];
//
//		left += 1; right -= 1;
//
//		printf("%s\n", arr2);
//		Sleep(300);
//
//		system("cls");
//
//
//	}
//
//	printf("!!!!!\n\n\n%s\n\n\n!!!!!", arr2);
//
//	return 0;
//}

///////////////////////////////////////////////////////////////////////////////////


//
//int main()
//{
//	char password[30] = { 0 };
//
//	int i = 0;
//
//	printf("请输入密码:>");
//	scanf(" %s", password);
//
//	if (strcmp(password, "20060211") == 0)
//	{
//		printf("密码已输入，请等待系统加载\n");
//		Sleep(2000);
//		system("cls");
//		printf("系统加载中.......10%%\n");
//		Sleep(2000);
//		system("cls");
//		printf("系统加载中.......27%%\n");
//		Sleep(3000);
//		system("cls");
//		printf("系统加载中.......39%%\n");
//		Sleep(5000);
//		system("cls");
//		printf("系统加载中.......71%%\n");
//		Sleep(1000);
//		system("cls");
//		printf("系统加载中.......99%%\n");
//		Sleep(10000);
//		system("cls");
//		printf("系统加载中.......100%%\n");
//		Sleep(300);
//		system("cls");
//		printf("系统加载中.......101%%\n");
//		printf("加载完成\n登录成功！！！！！！");
//	}
//	else
//	{
//		printf("密码输入错误！！\n");
//		Sleep(300);
//		system("cls");
//		for (i = 0; i < 5; i++)
//		{
//			printf("请重新输入密码:>");
//			scanf("%s", password);
//			if (strcmp(password, "20060211") == 0)
//			{
//				printf("密码已输入，请等待系统加载\n");
//				Sleep(2000);
//				system("cls");
//				printf("系统加载中.......10%%\n");
//				Sleep(2000);
//				system("cls");
//				printf("系统加载中.......27%%\n");
//				Sleep(3000);
//				system("cls");
//				printf("系统加载中.......39%%\n");
//				Sleep(5000);
//				system("cls");
//				printf("系统加载中.......71%%\n");
//				Sleep(1000);
//				system("cls");
//				printf("系统加载中.......99%%\n");
//				Sleep(10000);
//				system("cls");
//				printf("系统加载中.......100%%\n");
//				Sleep(300);
//				system("cls");
//				printf("系统加载中.......101%%\n");
//				system("cls");
//				printf("加载完成\n登录成功！！！！！！");
//				break;
//			}
//
//			else
//			{
//				printf("怎么密码都输不对？重输！\n");
//				Sleep(1000);
//				system("cls");
//			}
//		}
//
//		
//	}
//	if (i == 5)
//	{
//		printf("已连续输入错误5次密码\n程序停止");
//	}
//
//
//	return 0;
//}
//


/////////////////////////////////////////////////////////////////////////////////////////


//#include<stdio.h>
//#include<time.h>
//#include<stdlib.h>
//#include<string.h>
//#include<windows.h>
//
//void menu()
//{
//			char arr1[] = "Wlcome to guess number!";     
//			char arr2[] = "                       ";   
//												   
//			int left = 0;
//			int right = strlen(arr2)-1;
//			while (left <= right)
//			{
//				arr2[left] = arr1[left];
//				arr2[right] = arr1[right];
//		
//				left += 1; right -= 1;
//		
//				printf("%s\n", arr2);
//				Sleep(300);
//		
//				system("cls");
//			}
//			printf("请等待游戏加载.....");
//			Sleep(1000);
//			system("cls");
//			printf("%s\n", arr2);
//	printf("*******************************************\n");
//	printf("*******************************************\n");
//	printf("***********     1.play          ***********\n");
//	printf("***********     2.exit          ***********\n");
//	printf("*******************************************\n");
//	printf("*******************************************\n");
//}
//
//void game()
//{
//	system("cls");
//	Sleep(1000);
//	printf("欢迎进入游戏！\n");
//	int guess = 0;
//	srand((unsigned int)time(NULL));//!!!!!!!!!!!!!!!!!!!
//	int X = rand() % 100 + 1;
//	Sleep(200);
//	printf("我想了一个数字你可以猜猜是几吗？\n");
//	printf("提示:>范围在1-100\n");
//	printf("\ntips:不想玩了可以输入666回到主界面！\n");
//
//		while (guess != 666)
//		{
//
//			printf("猜猜看:>");
//			scanf(" %d", &guess);
//
//
//
//			if (guess < X && guess>=0)
//			{
//				system("cls");
//				printf("猜的数猜小了一点哦\n");
//				printf("再猜猜看吧\n");
//				Sleep(100);
//			}
//			else if (guess > X && guess<=100)
//			{
//				system("cls");
//				printf("猜的数猜大了一点哦\n");
//				printf("再猜猜看吧\n");
//				Sleep(100);
//			}
//			else if(guess == X)
//			{
//				system("cls");
//				Sleep(1000);
//				printf("恭喜猜对了！！！\n");
//				Sleep(1000);
//				system("cls");
//				Sleep(200);
//				printf("您还要再玩一次吗？>输入666可以回到主界面！0.o\n");
//				printf("否则继续游戏\n");
//				printf(">");
//				scanf(" %d", &guess);
//				
//			}
//			else
//			{
//				system("cls");
//				printf("\n欢迎下次来玩0.o !\n");
//			}
//
//
//		}
//}
//
//
//
//
//
//int main()
//{
//	
//	char ret = 0;
//	menu();
//	system("cls");
//	
//	do
//	{
//		printf("*******************************************\n");
//		printf("*******************************************\n");
//		printf("***********     1.play          ***********\n");
//		printf("***********     2.exit          ***********\n");
//		printf("*******************************************\n");
//		printf("*******************************************\n");
//		printf("输1以进行游戏，输2结束游戏！\n");
//		printf("请选择您的选项:>");
//
//		scanf(" %c", &ret);
//
//		switch (ret)
//		{
//		case 50:
//			printf("\n正在退出游戏....\n");
//			Sleep(500);
//			system("cls");
//			printf("游戏退出！");
//			return 0;
//			break;
//
//		case 49:
//			printf("\n进入游戏中........\n");
//			Sleep(500);
//			system("cls");
//			game();
//			break;
//
//		default:
//			system("cls");
//			printf("你找茬吗？？？重输！\n\n\n");
//			break;
//		}
//
//	} while (1);
//
//	return 0;
//}


///////////////////////////////////////////////////////////////////////


//？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
//int main()
//{
//	menu();
//	printf("\n");
//	int ret = 0;
//
//	do
//	{
//	
//	printf("请选择您的选项:>");
//
//	scanf(" %d", &ret);
//
//	switch (ret)
//	{
//	case 2:
//		printf("\n正在退出游戏....\n");
//		Sleep(500);
//		system("cls");
//		printf("游戏退出！");
//		return 0;
//		break;
//
//	case 1:
//		printf("\n进入游戏中........\n");
//		Sleep(500);
//		system("cls");
//		game();
//		break;
//	default:
//		printf("你找茬吗？重输！\n");
//		break;
//	}
//
//	} while (1);
//
//	return 0;
//}
//////////////////////////////////////////////////////////////////////////////////////////////

//
//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	float h = 100;
//	int x = 0;
//	float reh = 100;
//	int i = 0;
//	printf("input:\n");
//	scanf("%d", &x);
//	if (x >= 0 && x <= 15)
//	{
//		printf("%d times:\n", x);
//		for (i = 1; i < x; i++)
//		{
//			h /= 2;
//			reh += h;
//			reh += h;
//		}
//		h /= 2;
//		printf("%.3f\n", reh);
//		printf("%.3f\n", h);
//	}
//	return 0;
//}
//
////////////////////////////////////////////////////////////////////////////

//
//#include<stdio.h>
//#include<math.h>
//#include<stdlib.h>
//int main()
//{
//	int a = 0;
//	printf("Input x:\n");
//	scanf("%d", &a);
//	a = abs(a);
//	int k = 0, b = 0, s = 0, g = 0;
//	k = a / 1000, b = (a / 100) % 10, s = ((a / 10) % 100) % 10, g = (((a % 1000) % 100) % 10);
//
//
//
//	int z = g * 1000 + s * 100 + b * 10 + k;
//	printf("y=%d\n", z);
//	int A = g * 10 + s, B = b * 10 + k;
//	printf("a=%d,b=%d\n", A, B);
//	int X = A * A + B * B;
//	printf("result=%d\n", X);
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////////////////


//#include<stdio.h>
//
//
//int main()
//{
//	printf("Input 10 numbers:\n");
//	int arr[10] = { 0 };
//	int a = 0;
//	scanf(" %d", &arr[0]);
//	scanf(" %d", &arr[1]);
//	scanf(" %d", &arr[2]);
//	scanf(" %d", &arr[3]);
//	scanf(" %d", &arr[4]);
//	scanf(" %d", &arr[5]);
//	scanf(" %d", &arr[6]);
//	scanf(" %d", &arr[7]);
//	scanf(" %d", &arr[8]);
//	scanf(" %d", &arr[9]);
//
//
//
//
//
//	int b = 0;
//	int i = 0;
//	a = arr[0];
//	while (i < 9)
//	{
//		b = arr[i + 1];
//		if (a <= b)
//		{
//			a = b;
//			i++;
//		}
//		else
//		{
//			i++;
//		}
//	}
//	int maxNum = a;
//
//	a = arr[0];
//	i = 0;
//	while (i < 9)
//	{
//		b = arr[i + 1];
//		if (a >= b)
//		{
//			a = b;
//			i++;
//		}
//		else
//		{
//			i++;
//		}
//
//	}
//	int minNum = a;
//	printf("maxNum=%d\n", maxNum);
//	printf("minNum=%d\n", minNum);
//	
//	int X = 0;
//	int C = 0;
//	int D = 0;
	////求最大公约数的算法逻辑///////////////////////////////////////////

//	for (X = 1;minNum>=X;X++)
//	{
//		if (maxNum % X == 0 && minNum % X ==0)
//		{
//			C = X;
//		}
//		else
//		{
//			;
//		}
//	}
//	printf("%d", C);
//
//
//		return 0;
//}


///////////////////////////////////////////////////////////////////////////



//
//#include<stdio.h>
//
//
//int main()
//{
//	int a = 1;
//	int b = 0;
//	while(a<=20)
//	{
//		b = a * a;
//		printf("%d*%d=%d\n", a, a, b);
//		a=a+1;
//		if (b >= 100)
//		{
//			return 0;
//		}
//
//
//	}
//	return 0;
//}
//
///////////////////////////////////////////////////////////////////////////////////////////


//
//#include<stdio.h>
//int main()
//{
//	float a = 11.5, b = 2.5, c = 10, V = 0, S = 0;
//	V = a * b * c; S = 2 * (a * b + b * c + a * c);
//	printf("area=%.2f,volume=%.2f", S, V);
//	return 0;
//}

//int main()
//{
//	int a = 0, b = 0;
//	printf("Input a,b:");
//	scanf("%d,%d",&a,&b);
//	int max = 0;
//	if (a <= b)
//	{
//		max = b;
//		printf("max = %d\n",max);
//	}
//	if (a > b)
//	{
//		max = a;
//		printf("max = %d\n",max);
//	}
//


//#include <stdio.h>
//
//int main()
//{
//	int a, b, c;
//
//	printf("Input two integers:");
//	scanf("%d %d", &a, &b);
//	c = a/b;
//	printf("The quotient of a and b is :%d", c);
//
//
//
//
//
//
//	return 0;
//}



//
//#include <stdio.h>
//
//int main()
//{
//	int a, b, c;
//
//	scanf("%d,%d,%d", &a, &b, &c);
//	if (a == b  && b== c)
//		printf("The three number is equal!!!");
//	else
//		printf("The three number isn't equal!!!");
//	return 0;
//}
//


//#include<stdio.h>



//
//int main()
//{
//	int a = 0;
//
//	printf("Input an integer number:\n");
//	scanf("%d", &a);
//
//	if (a % 2 == 0)
//	{
//		printf"%d is an even number\n", a);
//	}
//	else
//	{
//		printf("%d is an odd number\n", a);
//	}
//
//
//
//
//
//
//
//	return 0;
//}





//////////////////////////////////////////////////////////////////////////////////////




//#include<stdio.h>
//int f(int x)
//{
//	int right = x - 1;
//	int left = 2;
//	int i = 0;
//	if (x == 1)
//	{
//		printf("不是素数\n");
//		return 0;
//	}
//	for (left;left <= right;left++)
//	{
//		i = x % left;
//		if (i == 0)
//		{
//			printf("不是素数\n");
//			return 0;
//		}
//	}
//	printf("素数\n");
//
//}
//int main()
//{
//	int a = 0;
//	scanf(" %d",&a);
//	f(a);
//	return 0;
//}


///////////////////////////////////////////////////////////////////////////////////////////////

//#include<stdio.h>
//
//int g(int x)
//{
//	if (x % 4 == 0 && x % 100 != 0)
//	{
//		printf("普通闰年\n");
//		return 0;
//	}
//	else if (x % 400 == 0)
//	{
//		printf("世纪闰年\n");
//		return 0;
//	}
//	else
//	{
//		printf("不是闰年\n");
//		return 0;
//	}
//}
//int main()
//{
//	int a = 0;
//	scanf(" %d", &a);
//	g(a);
//	return 0;
//}

//////////////////////////////////////////////////////////////////////////////////////


//
//
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
//#include<stdio.h>
//
//
//
//void find(int x,int y,int z, int* p )
//{
//	int xrr[] = *p;
//	int mid = x + y / 2;
//	if(*p[mid])
//		
//
//}
//
//
//
//int main()
//{
//	int arr[17] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
//	int* pa = arr;
//	int k = 0;
//	scanf(" %d", &k);
//	int le = 0;
//	int ri = sizeof(arr) / sizeof(arr[0]);
//	find(le, ri,k,pa);
//	return 0;
//}
//

///////////////////////////////////////////////////////////////////////////////////////////////



//
//#include<stdio.h>
//
//void add(int* x)
//{
//	*x += 1;
//}
//
//
//int main()
//{
//	int num = 0;
//	int* pnum = &num;
//	while (num < 100)
//	{
//		add(pnum);
//		printf(" %d\n", num);
//	}
//	return 0;
//}


///////////////////////////////////////////////////////////////////////////////////////////

//
//
//#include<stdio.h>
//
//
//
//
//int main()
//{
//
//
//
//
//
//	return 0;
//}
//

/////////////////////////////////////////////////////////////////////////////////////////















