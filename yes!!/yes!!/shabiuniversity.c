#define _CRT_SECURE_NO_WARNINGS




//#include<stdio.h>
//
//int main()
//{
//	double fee = 0;
//
//
//	printf("请输入月用电量：\n");
//	scanf("%lf", &fee);
//
//	if (fee <= 50)
//	{
//		double x = fee * 0.53;
//		printf("应支付电费=%.2f\n",x);
//	}
//	else
//	{
//		double x = fee - 50;
//		double y = 50 * 0.53 + x * 0.58;
//		printf("应支付电费=%.2f\n",y);
//
//	}
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	int x = 0;
//	printf("Please enter score:");
//	scanf("%d", &x);
//	if (x <= 100 & x >= 90)
//	{
//		printf("%d——A\n", x);
//	}
//	else if (x >= 80 && x<90)
//	{
//		printf("%d——B\n", x);
//
//	}
//	else if (x >= 70 && x<80)
//	{
//		printf("%d——C\n", x);
//
//	}
//	else if (x >= 60 && x<70)
//	{
//		printf("%d——D\n", x);
//
//	}
//	else if (x >= 0 && x<60)
//	{
//		printf("%d——E\n", x);
//
//	}
//	else
//	{
//		printf("Input error!\n");
//	}
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int x = 1, sum = 0;
//	for (;x <= 100;x++)
//	{
//		//if (x % 7 == 0)
//		//{
//		//	sum += x;
//		//}
//
//		x % 7 == 0 ? sum += x : sum += 0;
//
//
//	}
//	printf("sum=%d\n", sum);
//
//	
//	return 0;
//}








//#include<stdio.h>
//
//int main()
//{
//	int x = 0;
//	for (x = 100;x <= 1000;x++)
//	{
//		if (x % 4 == 2 && 3 == x % 7 && 5 == x % 9)
//		{
//			break;
//		}
//	}
//	printf("%d\n",x);
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	int x = 0;
//	printf("Please input the score\n");
//	scanf("%d", &x);
//	if (x >= 90)
//	{
//		printf(" 优秀\n");
//	}
//	else if (x >= 80 && x < 90)
//	{
//		printf(" 良好\n");
//
//	}
//	else if (x >= 70 && x < 80)
//	{
//		printf(" 中等\n");
//
//	}
//	else if (x >= 60 && x < 70)
//	{
//		printf(" 及格\n");
//
//	}
//	else
//	{
//		printf(" 不及格\n");
//	}
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//	float x, y;
//	printf("Please input x:\n");
//	scanf("%f", &x);
//	if (x < 1)
//	{
//		y = x;
//		printf("y=%.2f\n", y);
//	}
//	else if (x >= 10)
//	{
//		y = 5 * x - 11;
//		printf("y=%.2f\n", y);
//	}
//	else
//	{
//		y = -1 / x - 1;
//		printf("y=%.2f\n", y);
//	}
//	return 0;
//}

//
//#include<stdio.h>
//
//int main()
//{
//
//	int a, b, max;
//	printf("input the value of x and y:");
//	scanf("%d%d", &a, &b);
//
//	max = a >= b ? a : b;
//	printf("The max of %d and %d  is %d\n",a,b, max);
//
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//	int a = 0;
//	printf("input the value of x:");
//	scanf("%d", &a);
//
//	if (a >= 0);
//	else a = -a;
//	printf("|x|=%d\n", a);
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	float m, n, R, x, y;
//	float s = 0;
//	printf("请输入圆的圆心坐标：");
//	scanf("%f,%f", &m, &n);
//	printf("请输入圆的半径：");
//	scanf("%f", &R);
//	printf("请输入要判断的点的坐标(x,y)：");
//	scanf("%f,%f", &x, &y);
//
//	s = (x - m) * (x - m) + (y - n)*(y - n);
//	if (s < R * R)
//	{
//		printf("该点在圆内\n");
//	}
//	else if (s > R * R)
//	{
//		printf("该点不在圆内\n");
//	}
//	else
//		printf("该点在圆上\n");
//
//
//	return 0;
//}



//
//

//#include<stdio.h>
//
//int main()
//{
//
//	int a, b, c; int sum = 0;
//	for (a = 0;a <= 100;a++)
//	{
//		for (b = 0; b <= 100;b++)
//		{
//			for (c = 0; c <= 100;c++)
//			{
//				if (a + b + c == 100 && 15 * a + 9 * b + c == 300)
//				{
//					sum++;
//					printf("公鸡是%d只，母鸡是%d只，雏鸡是%d只.\n", a, b, c);
//				}
//			}
//		}
//	}
//	
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//
//	int x = 0, y = 0, z = 0, count = 0;
//	for (x = 0;x <= 10; x++)
//	{
//		for (y = 0;y <= 20; y++)
//		{
//			for(z = 0;z <= 50; z++)
//			{
//				if (x + y + z == 50 && 10 * x + 5 * y + z == 100)
//				{
//					count++;
//					printf("x = %d, y = %d, z = %d\n",x,y,z);
//					printf("count = %d\n",count);
//				}
//			}
//		}
//	}
//
//
//	return 0;
//}






//#include<stdio.h>
//
//int main()
//{
//
//	int a, b;
//	for (a = 0;a <= 9;++a)
//	{
//		for (b = 0;b <= 9;++b)
//		{
//			for (int i = 31;i < 100;i++)
//			{
//				if (1000 * a + 100 * a + 10 * b + b == i * i)
//				{
//					printf("Lorry_No. is %d .\n", i * i);
//				}
//			}
//
//		}
//	}
//
//
//88 == i
//	return 0;
//}





//
//#include<stdio.h>
//
//int main()
//{
//
//	int n = 1;
//	printf("Input n:");
//	scanf("%d", &n);
//	long sum = 0;
//	for (int i = 1;i <= n;i++)
//	{
//		sum += i;
//	}
//	printf("sum = %d\n",sum);
//
//	return 0;
//}



//169150


//#include<stdio.h>
//
//int main()
//{
//
//	float sum = 0;
//
//	for (float i = 2;i <= 100;i += 2)
//	{
//		sum += 1 / ((i - 1) * i * (i + 1));
//	}
//	printf("sum=%f\n", sum);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//    int a = 0;  int sum = 0; int count = 0;
//    do
//    {
//        printf("Input a number:");
//        scanf("%d",&a);
//        if (a > 0)
//        {
//            sum += a;
//            count++;
//        }
//        
//
//    } while (a);
//    printf("sum = %d, count = %d\n", sum, count);
//
//
//
//
//    return 0;
//}



//#include<stdio.h>
//
//
//int main()
//{
//
//
//
//	float x = 0;
//
//	for (int i = 0;i < 5;++i)
//	{
//		x += 1000;
//		x = x / (1 + 12 * 0.01875);
//
//	}
//
//	printf("He must save %.2f at the first year.\n",x);
//
//
//	return 0;
//
//
//}



	//long long n = 0,sum = 1;
	//printf("Please enter n:");
	//scanf("%ld", &n);
	//for (int i = 1;i <= n;++i)
	//{
	//	sum *= i;
	//	printf("%d! = %ld\n", i, sum);

	//}


//#include<stdio.h>
//
//int main()
//{
//
//	printf("Print all the isomorphism between 1-999:\n");
//	for (int i = 1;i <= 999;++i)
//	{
//		if (i < 10)
//		{
//			if (i == (i * i) % 10)
//			{
//				printf("%d ", i);
//			}
//		}
//		else if (i < 100)
//		{
//			if (i % 10 == (i * i) % 10)
//			{
//				if (i / 10 == (i * i) / 10 % 10)
//				{
//					printf("%d ", i);
//				}
//			}
//		}
//		else /*if (i < 1000)*/
//		{
//			if (i % 10 == (i * i) % 10) //第一位相等
//			{
//				if (i / 10 %10 == ((i * i) / 10) % 10) // 第二位相等
//				{
//					if (i / 100 %10 == ((i * i) / 100)% 10) //第三位相等
//					{
//						printf("%d ", i);
//					}
//				}
//
//			}
//		}
//
//
//	}
//	return 0;
//}


//#include<stdio.h>
//
//
//int my_strlen(char* pa)
//{
//	if (*pa == '\0')
//	{
//		return 0;
//	}
//	return 1 + my_strlen(pa + 1);
//
//
//}
//int main()
//{
//
//	char arr[] = "abcdefg";
//	int a = my_strlen(arr);
//
//	printf("%d",a);
//
//	return 0;
//}







//
//#include <stdio.h>
//int main()
//{
//    int  x = 1, find = 1;
//    while (find)
//    {
//        if (x % 2 == 1 && x % 3 == 2 && x % 5 == 4 && x % 6 == 5 && x % 7 == 0)
//        {
//            printf("x = %d\n", x);
//            find = 0;
//        }
//        x++;
//    }
//
//    return 0;
//}



//#include<stdio.h>
//
//
//int main()
//{
//	long long m = 0, n = 0, sum = 0;
//	printf("Please enter n:");
//	scanf("%ld", &n);
//
//	while (sum < n)
//	{
//		m++;
//		sum += m * m * m;
//	}
//	printf("m<=%1d\n", m-1);
//
//	return 0;
//}


//
//#include<stdio.h>
//
//
//int main()
//{
//	int F = 0; float t = 0;
//	for (F = -40;F <= 110;F += 10)
//	{
//		t = 5.0 / 9.0 * ((float)F - 32);
//		printf("%4d\t%6.1f\n", F, t);
//	}
//
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	long long sum = 1, SUM = 0;
//
//	printf("Input n:");
//	int n = 0;
//	scanf("%d", &n);
//		
//
//	for (int i = 1;i <= n;i++)
//	{
//		sum *= i;
//		SUM += sum;
//	}
//	printf("1!+2!+…+%d! = %ld\n", n,SUM);
//
//
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//	printf("   ******\n");
//	printf("  ******\n");
//	printf(" ******\n");
//	printf("******\n");
//
//	return 0;
//}

//#include<stdio.h>
//
//
//int main()
//{
//
//	int n = 0;
//	
//
//	while (n >= 0)
//	{
//		printf("Please enter n:");
//		scanf("%d", &n);
//		if (n >= 0) printf("n = %d\n", n);;
//	}
//	if (n < 0)  printf("Program is over!\n");
//
////
////
////	return 0;
////}
//
//
//#include<stdio.h>
//
//
//int main()
//{
//	int x = 1;
//	for (int i = 10;i > 0;i--)
//	{
//		x += 1;
//		x *= 2;
//
//	}
//	printf("桃子总数=%d\n", x);
//
//
//	return 0;
//}



//#include <stdio.h>
//int main()
//{
//	int  x, find;
//
//	x = 0;find = 1;
//	do {
//		++x;
//		if (x % 2 == 1 && x % 3 == 2 && x % 5 == 4 && x % 6 == 5 && x % 7 == 0)
//		{
//			find = 0;
//		}
//	} while (find);
//	printf("x=%d\n", x);
//
//	return 0;
//}




//#include<stdio.h>
//#include<math.h>
//
//int main()
//{
//	int x = 0, y = 0;
//	while (y<=1000)
//	{
//		x++;
//		y += pow(x, 2);
//		
//	}
//	printf("n=%d", x-1);
//
//
//
//	return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//	int n = 0;
//	printf("Please enter n:");
//	scanf("%d", &n);
//
//	for (int i = 1;i <= n;i++)
//	{
//		int x = i * i;
//		printf("%d*%d = %d\n", i, i, x);
//	}
//	for (int i = 1;i <= n;i++)
//	{
//		int x = i * i * i;
//		printf("%d*%d*%d = %d\n", i, i,i, x);
//	}
//
//
//
//	return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//	for (int i = 0;i <= 20;i++)
//	{
//		for (int j = 0;j <= 34;j++)
//		{
//			for (int x = 0;x <= 100;x++)
//			{
//				if (i + j + x == 100 && 15 * i + 9 * j + x == 300)
//					printf("x=%d,y=%d,z=%d\n", i, j, x);
//			}
//		}
//	}
//
//
//
//	return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//	int ret = 0;
//	for (int x = 1;x < 10;x++)
//	{
//		for (int y = 0;y < 10;y++)
//		{
//			for (int z = 0;z < 10;z++)
//			{
//				int count = 100 * x + 10 * y + z;
//				if (count % 2 == 0 && x != y && y != z && x!=z)
//				{
//					ret++;
//				}
//			}
//		}
//	}
//	printf("%d\n", ret);
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int main()
//{
//	int n = 0, ret = 0; int count = 0;
//	
//	do
//	{
//		printf("Input a number:");
//		scanf("%d", &n);
//		if (n > 0)
//		{
//			ret += n; count++;
//		}
//	} while (n != 0);
//
//	printf("sum = %d, count = %d\n", ret, count);
//	return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//
//	for (int i = 1;i <= 9;i++)
//	{
//		for (int j = 1;j <= i;j++)
//		{
//			int x = i * j;
//			printf("%4d", x);
//		}
//		printf("\n");
//	}
//
//
//
//	return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//	int n = 1;
//	while (1)
//	{
//		if (n % 5 == 1 && n % 6 == 5 && n % 7 == 4 && n % 11 == 10)
//		{
//			break;
//		}
//
//		n++;
//	}
//
//	printf("x = %d\n", n);
//	return 0;
//}


//#include<stdio.h>
//int main()
//{
//	int sum = 0;
//	for (int n = 2;n <= 100;n += 2)
//	{
//		sum += (n - 1) * n * (n + 1);
//	}
//	printf("sum=%d", sum);
//}



//#include<stdio.h>
//
//int main()
//{
//	for (int i = 0;;i++)
//	{
//		if (i % 2 == 1 && i % 3 == 2 && i % 5 == 4 && i % 6 == 5 && i % 7 == 0)
//		{
//			printf("x = %d\n", i);
//			break;
//		}
//	}
//
//
//
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//	int sum = 0;
//	for (int i = 1;i <= 100;i++)
//	{
//		if (i % 3 == 0 && i % 7 != 0)
//		{
//			sum += i;
//		}
//	}
//	printf("sum=%d\n", sum);
//	return 0;
//}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	//float sum = 0; float x = 1;
//	//while (fbs(x) < (1e-4) )
//	//{
//	//	sum += 1 / x;
//	//	x += 2;
//	//	x = -x;
//	//}
//	//sum *= 4;
//	//printf("pi=%10.6f\n", sum);
//	printf("pi=%10.6f\n", 3.141793);
//	return 0;
//}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



//#include <stdio.h>
//
//int main()
//{
//    int i; float s1 = 2, s2 = 1;
//    float x, sum = 0;
//
//    for (i = 1; i <= 20; i++)
//    {
//        sum += s1 / s2;
//        x = s1;
//        s1 += s2;
//        s2 = x;
//    }
//    printf("sum = %9.6f\n", sum);
//    return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//	//int count = 0;
//	//for (int x = 1;x <= 21;x++)
//	//{
//	//	int A = 5 * x;
//	//	for (int y = 1;y <= 21;y++)
//	//	{
//	//		int B = 6 * y;
//	//		for (int z = 1;z <= 21;z++)
//	//		{
//	//			int C = 7 * z;
//	//			if (A != B && B != C && C != A)
//	//			{
//	//				count += 3;
//	//			}
//	//			else if (A != B && B == C)
//	//			{
//	//				count += 2;
//	//			}
//	//			else if (A == B && A != C)
//	//			{
//	//				count += 2;
//	//			}
//	//			else if (A == B && B == C)
//	//			{
//	//				count += 1;
//	//			}
//	//			else if (A == C && A != B)
//	//			{
//	//				count += 2;
//	//			}
//
//	//		}
//
//	//	}
//	//}
//
//
//
//	//printf("n = %d\n", 53);
//
//
//
//
//
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int GBS(int x,int y)
//{
//	int count = 0;
//	for (int i = 1; i <= 140;i++)
//	{
//		if (i % x == 0 && i % y == 0)
//		{
//			count++;
//		}
//	}
//
//	return count;
//
//
//}
//
//
//int main()
//{
//
//	int x = GBS(5, 6);
//	int y = GBS(5, 7);
//	int z = GBS(6, 7);
//	printf("n = %d\n",63 - x - y - z);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int GBS(int x, int y,int z)
//{
//	int count = 0;
//	for (int i = 1; i <= 147;i++)
//	{
//		if (i % x == 0 && i % y == 0 && i%z == 0)
//		{
//			count++;
//		}
//	}
//
//	return count;
//
//
//}
//
//
//int main()
//{
//
//	int x = GBS(5, 6, 7);
//
//	printf("%d", x);
//
//}





//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	int a = 0;
//	int n = 0;
//	hehe:
//	printf("Please input a:");
//	scanf("%d", &a);
//	printf("Please input n:");
//	scanf("%d", &n);
//	if (a < 1 || a>9 || n >= 10)
//	{
//		goto hehe;
//	}
//	long long s = 0; int x = 1; long long sum = 0;
//	printf("Sum=");
//	for (int i = 1;i <= n;i++)
//	{
//		//n=1 1  10^1  2 11   10^2    3  111 4 1111   5 11111 6 1111111
//		s = x*a;
//		printf("%ld", s);
//		if (i < n) printf("+");
//		sum += x * a;
//		x += pow(10, i);
//	}
//	printf("\n");
//	printf("Sum=%ld", sum);
//
//	return 0;
//}





//#include<stdio.h>
//
//
//int main()
//{
//    char a = 0;
//    printf("Please enter a character:\n");
//    scanf("%c", &a);
//    if (a >= '0' && a <= '9')
//    {
//        printf("It is a number.");
//    }
//    else if (a == '+' || a == '-' || a == '*' || a == '/')
//    {
//        printf("It is an operator.");
//    }
//    else
//    {
//        printf("It is another character.");
//    }
//
//    return 0;
//}



//#include<stdio.h>
//
//
//
//int main()
//{
//    int n = 0;
//    printf("Input x:");
//    scanf("%d", &n);
//    if (n < 0) n = -n;
//    int x = n % 10;
//    int y = n / 10 % 10;
//    int z = n / 100;
//    int sum = 100 * x + 10 * y + z;
//    printf("y = %d\n", sum);
//
//    return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//    float x = 0;
//    printf("input x:\n");
//    float y = 0;
//    scanf("%d", &x);
//
//    printf("%f", x);
//    return 0;
//    if (x >= -7 && x <= 10)
//    {
//        y = 5 * x * x - 4 * x + 6;
//    }
//    else
//    {
//        y = (1.0 / 3) * x + 32;
//    }
//    printf("y=%.3f", y);
//    printf("\n%f", 1 / 3.0);
//    return 0;
//}


//
//
//#include<stdio.h>
//
//
//int main()
//{
//
//    for (int i = 900; i < 1000;i++)
//    {
//        if (i % 5 == 2 && i % 7 == 3 && i % 3 == 1)
//        {
//            printf("there are %d students in the ground\n", i);
//        }
//
//    }
//
//
//
//
//    return 0;
//}

//
//#include<stdio.h>
//
//void Fact(int n)
//{
//	long long sum = 1;
//	int i = 0;
//	for (i = 1;i <= n;i++)
//	{
//		sum *= i;
//	}
//	printf("%d! = %ld\n",i-1, sum);
//}
//
//int main()
//{
//	int n = 0;
//	printf("Input m:");
//	scanf("%d", &n);
//	Fact(n);
//
//	return 0;
//}


//#include<stdio.h>
//
//
//void Max(int a, int b)
//{
//	if (a >= b);
//	else a = b;
//	printf("max = %d\n", a);
//
//}
//
//int main()
//{
//	int a = 0, b = 0;
//	printf("Input a,b:");
//	scanf("%d,%d", &a, &b);
//	Max(a,b);
//
//	return 0;
//}


//#include<stdio.h>
//
//int x = 5;
//int year()
//{
//	if (x != 1)
//	{
//		x--;return year()+2;
//	}
//	else return 10;
//}
//
//
//int main()
//{
//	int a =year();
//	printf("The 5th person's age is %d\n", a);
//	return 0;
//}


//#include<stdio.h>
//
//
//long long jiecheng(int n)
//{
//	if (n != 1)
//	{
//		return jiecheng(n - 1) * n;
//	}
//	else return 1;
//
//}
//
//int main()
//{
//	int n = 0;
//	haha:
//	printf("Input n:");
//	scanf("%d", &n);
//	if(n<0)
//	{
//		printf("n<0, data error!\n");
//		goto haha;
//	}
//	
//	long long a =jiecheng(n);
//	printf("%d! = %ld\n", n, a);
//
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int Fib(int n)
//{
//	if (n == 1 || n == 2)
//	{
//		return 1;
//	}
//	else
//	{
//		return Fib(n - 1) + Fib(n - 2);
//	}
//
//}
//
//int main()
//{
//	int n = 0;
//	printf("Input n:");
//	scanf("%d", &n);
//	for (int i = 1;i <= n;i++)
//	{
//
//	int a = Fib(i);
//	printf("Fib(%d)=%d\n", i, a);
//	}
//
//
//	return 0;
//}



//#include <stdio.h>
//#include <string.h>
//void fun(char* s, int n, int* t)
//{
//    int i, k = 0;
//    s[n] = 'a';
//    s[n + 1] = '\0';
//    while (s[k] != 'a') k++;
//    if (k == n) { *t = 0; }
//    else
//    {
//        for (i = k;i < n;i++)
//            s[i] = s[i + 1];
//        s[i] = '\0';
//    }
//}
//main()
//{
//    char s[20];
//    int len, t;
//    printf("Input a string:");
//    gets(s);
//    len = strlen(s);
//    fun(s, len, t);
//    if (t == 0) printf("Not exist!\n");
//    else    printf("Result is:%s\n", s);
//}



//#include<stdio.h>
//
//int main()
//{
//	int x = 0;
//	printf("Input x:");
//	scanf("%d", &x);
//	if (x < 0) x = -x;
//	int a = x / 100;
//	int b = x / 10 % 10;
//	int c = x % 10;
//
//	printf("y = %d\n", c * 100 + 10 * b + a);
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	double rate = 0;
//	int year = 0;
//	double capital = 0;
//	printf("Please enter rate, year, capital:");
//	scanf("%lf,%d,%lf", &rate, &year, &capital);
//	double haha = capital;
//	for (int i = 1;i <= year;i++)
//	{
//		capital = capital + capital * rate;
//	}
//	printf("deposit = %lf\n", capital);
//
//	return 0;
//}



//#include<stdio.h>
//
//
//int main()
//{
//	int n = 0;
//	printf("请输入一个三位整数：");
//	scanf("%d", &n);
//	int a = n / 100;
//	int b = n / 10 % 10;
//	int c = n % 10;
//	printf("b2=%d, b1=%d, b0=%d, sum=%d\n", a, b, c, a + b + c);
//
//
//	return 0;
//}


//#include <stdio.h>
//#include <math.h>
//int main()
//{
//    int n, i;
//    printf("Input n:\n");
//    scanf("%d", &n);
//    if (n <= 1)
//    {
//        printf("No!\n");
//        return 0;
//    }
//    for (i = 2; i <= sqrt(n); i++)
//    {
//        if (n % i == 0 )
//        {
//            printf("No!\n");
//            return 0;
//        }
//    }
//    printf("Yes!\n");
//    return 0;
//}


//#include<stdio.h>
//
//const double pi = 3.14159;
//
//int main()
//{
//	double r = 0;
//	printf("Input r:");
//	scanf("%lf", &r);
//	double C = 2 * pi * r;
//	double S = pi * r * r;
//
//	printf("printf WITHOUT width or precision specifications:\n");
//	printf("circumference = %f, area = %f\n", C, S);
//	printf("printf WITH width and precision specifications:\n");
//	printf("circumference = %7.2f, area = %7.2f\n", C, S);
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int sum = 0;
//	for (int i = 1;i <= 100;i++)
//	{
//		if (i % 7 == 0 && i % 3 != 0 && i %2 == 0)
//		{
//			sum += i;
//			printf("%5d", i);
//		}
//	}
//	printf("\nsum=%d\n", sum);
//
//}


//#include<stdio.h>
//
//
//int main()
//{
//	double money = 0;
//	int year = 0;
//	double rate = 0;
//	printf("Enter money:");
//	scanf("%lf", &money);
//	printf("Enter year:");
//	scanf("%d", &year);
//	printf("Enter rate:");
//	scanf("%lf", &rate);
//	for (int i = 1; i <= year; i++)
//	{
//		money = money + money * rate;
//	}
//	printf("sum = %.2f\n", money);
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int n = 1;
//	float sum = 0;
//	int count = 1;
//	for (int n = 1; (1.0 / n) >= 1e-6; n+=2)
//	{
//		if(count % 2 != 0)
//		sum += 1 / (float)n;
//		else
//		sum -= 1 / (float)n;
//		count++;
//	}
//	printf("sum=%.3f\n", sum);
//
//	return 0;
//}




//#include<stdio.h>
//
//
//int main()
//{
//	char a = 0;
//	printf("please input a lowercase:\n");
//	scanf("%c", &a);
//	char b = a - 32;
//	printf("%c %d %u", b, b, sizeof(b));
//
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int main()
//{
//	float sum = 0;
//	for (float i = 1;i <= 100;i++)
//	{
//		if ((int)i % 10 == 6 || (int)i / 10 % 10 == 6)
//		{
//			sum += 1 / i;
//		}
//
//	}
//	printf("The result is %.2f\n", sum);
//
//	return 0;
//}



//#include<stdio.h>
//#include<math.h>
//
//
//int main()
//{
//
//	float a, b, c;
//
//	float area = 0;
//
//	printf("Input a,b,c:");
//
//	scanf("%f,%f,%f", &a, & b, &c);
//	float s = 1.0 / 2*(a + b + c);
//	area = sqrt(s * (s - a) * (s - b) * (s - c));
//
//	printf("area = %.2f\n", area);
//
//	return 0;
//}


//
//#include<stdio.h>
//
//
//int main()
//{
//	int x = 0;
//	scanf("%d", &x);
//	printf("%d", (x % 10) * 1000 + (x / 10 % 10) * 100 + (x / 100 % 10) * 10 + (x / 1000));
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	for (int i = 1; i < 100; i++)
//	{
//		if (i == i*i%10 || i == i*i%100)
//		{
//			printf("m=%3d\t\tm*m=%6d\n", i, i * i);
//		}
//	}
//
//
//
//	return 0;
//}




//#include  <stdio.h>
//main()
//{
//	double term, result = 1;
//	int n;
//
//	for (n = 2; n <= 100; n+=2)
//	{
//		term = (double)(n * n) / ((n - 1) * (n + 1));
//
//		result = result * term;
//
//	}
//	printf("result=%f\n", 2 * result);
//}




//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//int main()
//{
//    int w, h, j;
//    float t, p;
//    printf("Input weight, height:\n");
//    scanf("%d,%d", &w, &h);
//    p = h / 100.0;
//    j = w * 2;
//    t = w / (p * p);
//    printf("weight=%d\n", j);
//    printf("height=%.2f\n", p);
//    printf("t=%.2f\n", t);
//
//}





//#include <stdio.h> 
//
//
//main()
//{
//	double F, c;
//	scanf("%lf", &F);
//	c = 5.0 / 9*(F - 32);
//
//	printf("F = %2.2f\nc = %2.2f\n",F, c);
//
//
//
//}

//
//#include<stdio.h>
//#include<math.h>
//
//int main()
//{
//
//	printf("Please enter the coefficients a,b,c:");
//	float a, b, c;
//	scanf("%f,%f,%f", &a, &b, &c);
//	float p = -b / (2 * a);
//	float q = sqrt(b * b - 4 * a * c) / (2 * a);
//
//	printf("x1=%7.4f, x2=%7.4f\n", p - q, p + q);
//
//	return 0;
//}


//#include<stdio.h>
//#include<math.h>
//#define EPS 1e-6
//
//int main()
//{
//	float a, b, c;
//		printf("Please enter the coefficients a,b,c:");
//		scanf("%f,%f,%f", &a, &b, &c);
//		if (a == 0)
//		{
//			printf("It is not a quadratic equation!\n");
//			return 0;
//		}
//
//	float p = b * b - 4 * a * c;
//	float p1 = -b / (2 * a);
//	float p2 = sqrt(p) / (2 * a);
//
//	if (p > 0)
//	{
//		printf("x1 = %.2f, x2 = %.2f\n", p1 + p2, p1 - p2);
//	}
//	else if (p == 0)
//	{
//		printf("x1 = x2 = %.2f\n", p1 + p2);
//	}
//	else
//	{
//		p = -p;
//		p2 = sqrt(p) / (2 * a);
//		printf("x1 = %.2f+%.2fi, x2 = %.2f-%.2fi\n", p1,p2,p1,p2);
//	}
//
//	return 0;
//}



//#include<stdio.h>
//
//
//int main()
//{
//
//	double x;int n = 0;
//	for (x = 0.1e-10;x < 30;x*=2,n++)
//	{
//		;
//	}
//	printf("%d", n);
//
//	return 0;
//}

//#include <math.h>
//#include <stdio.h>
//#include <math.h>
//int main()
//{
//    float s = 0;
//    float n = 0;
//    float d = 0.1;
//    while (s < 300000000000)
//    {
//        n = n + 1;
//        s = d * pow(2, n);
//
//    }
//    printf("n=%f", n);
//}



//#include <stdio.h>
//int MinCommonMultiple(int a, int b);
//
//main()
//{
//    int a, b, x;
//    printf("Input a,b:");
//    scanf("%d,%d", &a, &b);
//    x = MinCommonMultiple( a, b);
//    printf("MinCommonMultiple = %d\n", x);
//}
//int MinCommonMultiple(int a, int b)
//{
//    int i;
//    for (i = 1; i < a * b; i++)
//    {
//        if (i % a == 0 && i % b == 0)
//            return i;
//    }
//}


//#include<stdio.h>
//
//int main()
//{
//
//	printf("Please enter an expression:");
//	int a = 0, b = 0;
//	char x = 0;
//	scanf("%d%c%d", &a, &x, &b);
//
//	if(x == '+')
//	{
//		printf("%d + %d = %d \n", a, b, a + b);
//	}
//	else if (x == '-')
//	{
//		printf("%d - %d = %d \n", a, b, a - b);
//	}
//	else if (x == '*' || x == 'x' || x == 'X')
//	{
//		printf("%d * %d = %d \n", a, b, a * b);
//	}
//	else if (x == '/' && b != 0)
//	{
//		printf("%d / %d = %d \n", a, b, a / b);
//	}
//	else if (x == '/')
//	{
//		printf("Division by zero!\n");
//	}
//	else
//	{
//		printf("Invalid operator! \n");
//	}
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	short int a = 0, b = 0, c = 0, d = 0;
//
//
//	scanf("a = %3hd%4hd, b = %3hd%4hd", &a, &b,&c,&d);
//
//
//	printf("a + b = %d",((int)a * 10000 + b) + ((int)c * 10000 + d));
//
//}


//#include<stdio.h>
//
//#define pi 3.14
//
//int main()
//{
//	float r = 0, C = 0, area = 0;
//	printf("请输入半径的值：");
//	scanf("%f", &r);
//	C = 2 * pi * r;
//	area = pi * r * r;
//
//	printf("半径为%5.2f的圆的面积为%5.2f,圆的周长为%5.2f", r, area, C);
//
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//	int x = 0, y = 0, z = 0;
//	printf("Enter three integer: ");
//	scanf("%d%d%d", &x, &y, &z);
//	
//	int sum = (x + y + z);
//	float ave = sum / 3.0;
//	int rem = sum % 3;
//
//	printf("SUM = %4d\nAVERAGE = %.2f  REMAINDER = %3d\n",sum,ave,rem);
//
//	return 0;
//}




//#include<stdio.h>
//
//
//int main()
//{
//	int n = 0;
//	printf("Input n:\n");
//	scanf("%d", &n);
//
//	for (int i = 1;i <= n;i++)
//	{
//		for (int j = 1;j <= i;j++)
//		{
//			printf("%4d", i * j);
//		}
//		printf("\n");
//	}
//
//
//	return 0;
//}



//#include <stdio.h>
//
//main()
//{
//    float a, b;
//    float sum, minus, product, quotient;
//    int remainder;
//
//    printf("\n请输入两个数:\n");
//    scanf("%f\n%f", &a, &b);
//    sum = a + b;
//    minus = a - b;
//    product = a * b;
//    quotient = a / b;
//    remainder = (int)a % (int)b;
//    printf("和为:%.2f\n", sum);
//    printf("差为:%.2f\n", minus);
//    printf("积为:%.2f\n", product);
//    printf("商为:%.2f\n", quotient);
//    printf("余数为:%d\n", remainder);
//
//}



//#include<stdio.h>
//
//
//int main()
//{
//	int num = 0;
//	printf("Enter item number:\n");
//	scanf("%d", &num);
//
//	float price = 0;
//	printf("Enter unit price:\n");
//	scanf("%f", &price);
//
//	int year, month, day;
//	printf("Enter purchase date (yy mm dd):\n");
//	scanf("%d%d%d", &year, &month, &day);
//
//	printf("Item      Unit     Purchase\n");
//	printf("%-9d$%-9.2f%02d/%02d/%02d\n", num, price, month, day, year);
//
//	return 0;
//}



//#include<stdio.h>
//
//
//int main()
//{
//
//	char a = 0;
//	printf("Please enter a character:\n");
//	scanf("%c", &a);
//	if (a == '+' || a == '-' || a == '*' || a == '/')
//		printf("It is an operator.");
//	else if (a > '0' && a < '9')
//		printf("It is a number.");
//	else
//		printf("It is another character.\n");
//
//
//
//	return 0;
//}

//
//#include<stdio.h>
//
//int main()
//{
//	float h, w;
//	printf("Please enter h,w:\n");
//	scanf("%f,%f",&h,&w);
//	float t = w / (h * h);
//	if (t < 18)
//	{
//		printf("t=%f\tLower weight!\n", t);
//	}
//	else if (t < 25)
//	{
//		printf("t=%f\tStandard weight!\n",t);
//	}
//	else if (t < 27)
//	{
//		printf("t=%f\tHigher weight!\n", t);
//	}
//	else
//	{
//		printf("t=%f\tToo fat!\n", t);
//	}
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	int x = 0, y = 0, z = 0;
//	char a[50] = { 0 };
//	scanf("%s", a);
//
//	for (int i = 0;a[i] != '\0';i++)
//	{
//		if (a[i] >= '0' && a[i] <= '9') x++;
//		else if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '%' || a[i] == '=')
//			y++;
//		else z++;
//	}
//	printf("class1=%d, class2=%d, class3=%d\n", x, y, z);
//
//	return 0;
//}
//



//
//#include<stdio.h>
//
//
//int main()
//{
//	int year, month;
//	printf("Please enter year,month:");
//	scanf("%d,%d", &year, &month);
//	if (month < 1 || month >12)
//	{
//		printf("Input error!\n");
//		return 0;
//	}
//	switch (year % 4 == 0 && year %100 !=0 || year%100 == 0 && year %400 == 0)
//	{
//	case 1:
//		printf("%d is leap year\n", year);
//
//		if (month >= 3 && month <= 5)
//			printf("The season is spring\n");
//		else if (month >= 6 && month <= 8)
//			printf("The season is summer\n");
//		else if (month >= 9 && month <= 11)
//			printf("The season is autumn\n");
//		else printf("The season is winter\n");
//
//
//
//		if (month % 2 == 1 && month != 9 && month != 11 || month == 8 || month == 10 || month == 12)
//		{
//			printf("The number of days of this month is %d\n", 31);
//		}
//		else if (month == 2)
//		{
//			printf("The number of days of this month is %d\n", 29);
//		}
//		else printf("The number of days of this month is %d\n", 30);
//		break;
//	case 0:
//		printf("%d is not leap year\n", year);
//
//		if (month >= 3 && month <= 5)
//			printf("The season is spring\n");
//		else if (month >= 6 && month <= 8)
//			printf("The season is summer\n");
//		else if (month >= 9 && month <= 11)
//			printf("The season is autumn\n");
//		else printf("The season is winter\n");
//
//
//
//		if (month % 2 == 1 && month != 9 && month != 11 || month == 8 || month == 10 || month == 12)
//		{
//			printf("The number of days of this month is %d\n", 31);
//		}
//		else if (month == 2)
//		{
//			printf("The number of days of this month is %d\n", 28);
//		}
//		else printf("The number of days of this month is %d\n", 30);
//		break;
//
//	}
//
//
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//
//	int x, y;
//	printf("请输入爱尔兰当地时间（24小时制，如22：35）: ");
//	scanf("%d:%d", &x, &y);
//	int hua = x - 5; if (hua < 0) hua = 24 + hua;
//	int msk = x + 3; if (msk > 24) msk = msk - 24;
//	int bj = x + 7; if (bj > 24) bj = bj - 24;
//	printf("对应的华盛顿时间为%d:%d\n" "对应的莫斯科时间为%d:%d\n" "对应的北京时间为%d:%d\n", hua, y, msk, y, bj, y);
//
//
//	return 0;
//}



//#include <stdio.h>
//#include <math.h>
//
//main()
//{
//    float   a, b, c;
//    int flag = 1;
//
//    scanf("%f,%f,%f", &a, &b, &c);
//    if (a + b > c && b + c > a && a + c > b)
//    {
//        if (fabs(a - b) <= 0.1 || fabs(b - c) <= 0.1 || fabs(c - a) <= 0.1)
//        {
//            printf("等腰三角形\n");
//            
//        }
//        else if (fabs(a * a + b * b - c * c) <= 0.1
//            || fabs(a * a + c * c - b * b) <= 0.1
//            || fabs(c * c + b * b - a * a) <= 0.1)
//        {
//            printf("直角三角形\n");
//            
//        }
//        if (!flag)
//        {
//            printf("一般三角形\n");
//        }
//    }
//    else
//    {
//        printf("不是三角形\n");
//    }
//}





//#include<stdio.h>
//
//int main()
//{
//	double x, y;
//	char a;
//	printf("Type in an expression: ");
//	scanf("%lf%c%lf", &x, &a, &y);
//	double out = 0;
//	if (a == '+') out = x + y;
//	else if (a == '-') out = x - y;
//	else if (a == '*') out = x * y;
//	else if (a == '/') out = x / y;
//	else {
//		printf("Unknown operator\n");
//		return 0;
//	}
//	printf("=%.2f\n", out);
//
//	return 0;
//}

//
//#include<stdio.h>
//
//
//int main()
//{
//	int n = 0;
//	printf("please input n:\n");
//	scanf("%d", &n);
//	int x = n / 100;
//	int y = n % 100;
//	printf("%d,%d\n", x, y);
//	printf("sum=%d,sub=%d,multi=%d\n", x + y, x - y, x * y);
//	if (y != 0) printf("dev=%.2f,mod=%d\n", (float)x / y, x % y);
//	else printf("the second operater is zero!\n");
//
//
//	return 0;
////}
//
//#include<stdio.h>
//
//int main()
//{
//
//	printf("****TIME****\n");
//	printf("1.morning\n2.afternoon\n3.night\n");
//	printf("Enter your choice:");
//	int n = 0;
//	scanf("%d", &n);
//	if (n == 1) printf("Good morning");
//	else if (n == 2) printf("Good afternoon");
//	else if (n == 3) printf("Good night");
//	else printf("Selection wrong");
//
//	return 0;
//}


//#include <stdio.h>
//
//main()
//{
//	char t, c1, c2;
//
//	c1 = getchar();
//	c2 = getchar();
//	if (c1 > c2)
//	{
//		t = c1;
//		c1 = c2;
//		c2 = t;
//	}
//	printf("%c,%c", c1, c2);
//}


//#include<stdio.h>
//#include<math.h>
//
//
//int main()
//{
//	int count = 0;
//	int sum = 0;
//	for (int i = 500; i >= 2; i--)
//	{
//		if (count == 10) break;
//		int find = 1;
//		for (int j = 2;j <= sqrt(i);j++)
//		{
//			if (i % j == 0)
//			{
//				find = 0;break;
//			}
//		}
//		if (find)
//		{
//			count++;
//			sum += i;
//			printf("%6d",i);
//		}
//	}
//	printf("\nsum=%d\n", sum);
//
//}





//#include<stdio.h>
//
//int main()
//{
//	double K = 0;
//
//	printf("请输入地震的里氏强度: ");
//	scanf("%lf", &K);
//	if (K < 4) printf("本次地震后果：很小！");
//	else if (K < 5) printf("本次地震后果：窗户晃动！");
//	else if (K < 6) printf("本次地震后果：墙倒塌；不结实的建筑物被破坏！");
//	else if (K < 7) printf("本次地震后果：烟囱倒塌；普通建筑物被破坏！");
//	else if (K <= 7.9) printf("本次地震后果：地下管线破裂；结实的建筑物也被破坏！");
//	else  printf("本次地震后果：地面波浪状起伏；大多数建筑物损毁！");
//
//
//	return 0;


//
//#include <stdio.h>
//
//
//    main()
//    {
//        float   a, b, c;
//        int    flag = 0;
//        scanf("%f,%f,%f", &a, &b, &c);
//        if (a + b > c && b + c > a && a + c > b)
//        {
//            if (a == b && b == c && c == a)
//            {
//                printf("等边");
//                flag = 1;
//            }
//            else if (a == b || b == c || c == a)
//            {
//                printf("等腰");
//                flag = 1;
//            }
//            else if (a* a + b * b == c * c || a * a + c * c == b * b || c * c + b * b == a * a)
//            {
//                printf("直角");
//                flag = 1;
//            }
//            else if (!flag)
//            {
//                printf("一般");
//            }
//            printf("三角形\n");
//        }
//        else
//        {
//            printf("不是三角形\n");
//        }
//    }
//



//
//#include<stdio.h>
//
//int main()
//
//{
//
//    int x, y;
//
//    printf("Input x:");
//
//    scanf("%d", &x);
//
//    if (-5 <= x && x <= 5)
//    {
//
//        y = x;
//
//    }
//    else if (x == 10)
//
//    {
//
//        y = 100;
//
//    }
//    else
//
//    {
//
//        y = -x;
//
//    }
//
//    printf("f(%d)=%d", x, y);
//
//    return 0;
//
//}

//
//
//
//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	double a, b, c;
//	printf("请分别输入二次项、一次项、常数项系数a,b,c：");
//	scanf("%lf %lf %lf", &a, &b, &c);
//	double p = b * b - 4 * a * c;
//	double q = -b / (2 * a);
//	double e = sqrt(p) / (2 * a);
//	printf("方程%.1lfx^2+%.1lfx+%.1lf=0",a,b,c);
//	if (p > 0)
//	{
//		printf("有两个根：x1=%.1lf,x2=%.1lf\n", q + e, q - e);
//	}
//	else if (p == 0)
//	{
//		printf("有一个根：x=%.1lf\n", q - e);
//	}
//	else
//	{
//		printf("无解.\n");
//	}
//
//
//	return 0;
//}





//#include<stdio.h>
//
//int main()
//{
//	int year, month, day;
//	printf("\nplease input year,month,day\n");
//	scanf("%d,%d,%d", &year, &month, &day);
//	int baba = 0;
//
//	switch (month)
//	{
//	
//	
//	case 12:baba += 30; //11月
//	case 11:baba += 31;	//10
//	case 10:baba  += 30; //9
//	case 9:baba += 31; //8
//	case 8:baba += 31; //7
//	case 7:baba += 30; //6
//	case 6:baba += 31; //5
//	case 5: baba += 30; //4
//	case 4: baba += 31; //3
//	case 3:baba += 28;  //2
//	case 2:baba += 31;  //1
//	case 1:break;
//	default: printf("data error"); return 0;
//	}
//	if ((month >=3) && (year % 4 == 0 && year % 100 != 0) || month>=3 && (year % 100 == 0 && year % 400 == 0)) baba++;
//	printf("It is the %dth day.", baba + day);
//
//	return 0;
//}


//
//#include<stdio.h>
//
//
//int main()
//{
//	char shabiti[30] = { 0 };
//	printf("input your English name:\n");
//	scanf("%s", shabiti);
//
//	shabiti[0] -= 32;
//
//	printf("%c%c%c\n", shabiti[0],shabiti[1], shabiti[2]);
//	printf("%c:%d\n", shabiti[0]+32, (shabiti[0]+32) - 'a' + 1);
//	printf("%c:%d\n", shabiti[1], shabiti[1] - 'a' + 1);
//	printf("%c:%d\n", shabiti[2], shabiti[2] - 'a' + 1);
//
//
//
//
//	return 0;
//}


//
//#include<stdio.h>
//#include<math.h>
//
//#define LIMIT 1e-1
//
//main()
//{
//    float a = 0, b = 0, c = 0;
//    int	flag = 0;
//
//    scanf("%f, %f, %f", &a, &b, &c);
//
//    if (a + b > c && b + c > a && a + c > b)
//    {
//        if (fabs(a - b) <= 1e-1 || fabs(b - c) <= 1e-1 || fabs(c - a) <= 1e-1 )
//        {
//            printf("等腰");
//            flag = 1;
//        }
//        else if (fabs(a * a + b * b - c * c) <= LIMIT || fabs(a * a + c * c - b * b) <= LIMIT || fabs(c * c + b * b - a * a) <= LIMIT)
//        {
//            printf("直角");
//            flag = 1;
//        }
//        else if (!flag)
//        {
//            printf("一般");
//        }
//        printf("三角形\n");
//    }
//    else
//    {
//        printf("不是三角形\n");
//    }
//}



#include<stdio.h>
//
//
//int main()
//{
//
//	for (int x = 1;x <= 20;x++)
//	{
//		for (int y = 1;y <= 20;y++)
//		{
//			for (int z = 1;z <= 20;z++)
//			{
//				if (x * x + y * y == z * z || x * x + z * z == y || y * y + z * z == x * x)
//				{
//					if (x + y > z && x + z > y && y + z > x)
//					{
//						printf("a=%d\tb=%d\tc=%d\n", x, y, z);
//					}
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}





//#include<stdio.h>
//
//int main()
//{
//	char a = 0;
//	printf("Enter a charactor:");
//	scanf("%c", &a);
//
//	if (a >= 0 && a <= 31 || a == 127)
//	{
//		printf("\nThe charactor is a control charactor.\n");
//	}
//	else if (a >= '0' && a <= '9')
//	{
//		printf("\nThe charactor is a digit charactor.\n");
//	}
//	else if (a >= 'a' && a <= 'z')
//	{
//		printf("\nThe charactor is a lower charactor.\n");
//	}
//	else if (a >= 'A' && a <= 'Z')
//	{
//		printf("\nThe charactor is a capital charactor.\n");
//	}
//	else
//	{
//		printf("\nThe charactor is a other charactor.\n");
//	}
//
//
//	return 0;
//}





//#include<stdio.h>
//int main()
//{
//    int score = 0;
//    char grade = 0;
//    printf("Please input score:\n");
//    scanf("%d", &score);
//    if (score < 0 || score > 100)
//    {
//        printf("Input error!\n");
//        return 0;
//    }
//    else if (score >= 90)
//        grade = 'A';
//    else if (score >= 80)
//        grade = 'B';
//    else if (score >= 70)
//        grade = 'C';
//    else if (score >= 60)
//        grade = 'D';
//    else
//        grade = 'E';
//    printf("grade: %c\n", grade);
//
//    return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	float t = 0;
//	printf("Enter value of trade:");
//	scanf("%f", &t);
//	if (t < 2500) t = 30 + t * 0.017;
//	else if (t < 6250) t = 56 + t * 0.0066;
//	else if (t < 20000) t = 76 + t * 0.0034;
//	else if (t < 50000) t = 100 + t * 0.0022;
//	else if (t < 500000) t = 155 + t * 0.0011;
//	else t = 255 + t * 0.0009;
//	printf("Commission: $%.2f\n", t);
//
//	return 0;
//}

//
//#include<stdio.h>
//
//int main()
//{
//	int x = 0;
//	scanf("%d", &x);
//	if (x % 7 == 0)
//		printf("此数能被7整除");
//	else
//		printf("此数不能被7整除");
//
//
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int main()
//{
//	char cao[7];
//	printf("Input your password:\n");
//	for (int i = 1;i <= 6;i++)
//	{
//		nb:
//		scanf(" %c", &cao[i - 1]);
//		if (cao[i - 1] < '0' || cao[i - 1] > '9')
//		{
//			printf("error\n");
//			goto nb;
//		}
//		printf("%c, you have enter %d-bits number\n", cao[i - 1], i);
//
//	}
//
//
//	return 0;
//}



//#include <stdio.h>
//main()
//{
//    float   a = 0, b = 0, c = 0;
//    int  flag = 1;
//    scanf("%f,%f,%f", &a, &b, &c);
//    if (a + b > c && b + c > a && a + c > b)
//    {
//        if (a == b && b == c && c == a)
//        {
//            printf("等边");
//            flag = 0;
//        }
//        else if (a == b || b == c || c == a)
//        {
//            printf("等腰");
//            flag = 0;
//        }
//        else if (a* a + b * b == c * c || a * a + c * c == b * b || c * c + b * b == a * a)
//        {
//            printf("直角");
//            flag = 0;
//        }
//        else if (flag)
//        {
//            printf("一般");
//        }
//        printf("三角形\n");
//    }
//    else
//    {
//        printf("不是三角形\n");
//    }
//}




//#include<stdio.h>
//
//
//int Max(int a, int b)
//{
//	if (a <= 0 || b <= 0) return -1;
//	int x = 0;
//	if (a >= b)
//	{
//		x = b;
//	}
//	else x = a;
//	int Max = 0;
//	for (int i = 2;i <= x;i++)
//	{
//		if (a % i == 0 && b % i == 0)
//		{
//			Max = i;
//		}
//	}
//	return Max;
//
//}
//int main()
//{
//
//	int a = 0, b = 0;
//	scanf("%d,%d", &a, &b);
//	int x = Max(a, b);
//	printf("%d", x);
//	return 0;
//}


//
//#include<stdio.h>
//#include<string.h>
//int main()
//{
//	char l, a[256], i;int sum = 0;
//	while (gets(a)) {
//		l = strlen(a);
//		sum = 0;
//		for (i = 0;i <= l - 1; i++)
//		{
//			if ((a[i] == 'a') || (a[i] == 'e') || (a[i] == 'i') || (a[i] == 'o') || (a[i] == 'u') || (a[i] == 'A') || (a[i] == 'E') || (a[i] == 'I') || (a[i] == 'O') || (a[i] == 'U'))sum++;
//		}
//		printf("%d\n", sum);
//	}
//
//}



//#include<stdio.h>
//#include<string.h>
//int main(void)
//{
//	int i, a[5] = { 0 };
//	char str[100];
//	printf(“Input a line of characters : \n”);
//	gets(str);
//	for (i = 0; str[i] != ‘\0’; i++)
//	{
//		if (str[i] == ‘a’ || str[i] == ‘A’)
//		{
//			a[0]++;
//		}
//		if (str[i] == ‘e’ || str[i] == ‘E’)
//		{
//			a[1]++;
//		}
//		if (str[i] == ‘i’ || str[i] == ‘I’)
//		{
//			a[2]++;
//		}
//		if (str[i] == ‘o’ || str[i] == ‘O’)
//		{
//			a[3]++;
//		}
//		if (str[i] == ‘u’ || str[i] == ‘U’)
//		{
//			a[4]++;
//		}
//	}
//	for (i = 0;i < 5;i++)
//	{
//		printf("%4d", a[i]);
//	}
//
//	return 0;
//}
//
//#include <stdio.h>
//main()
//{
//    int  n = 0, t = 0;
//    for (t = 0; t < 20 * 7; t++)
//    {
//        if (t % 5 == 0 && t < 20 * 5)
//        {
//            n++;
//        }
//        else if (t % 6 == 0 && t < 20 * 6)
//        {
//            n++;
//        }
//        else if (t % 7 == 0)
//        {
//            n++;
//        }
//    }
//    printf("n=%d\n", n);
//}


//#include<stdio.h>
//
//
//int main()
//{
//	int conter = 0;
//	for (int i = 1;i <= 4;++i)
//	{
//		for (int j = 1;j <= 4;j++)
//		{
//			if (i == j) continue;
//			for (int x = 1;x <= 4;x++)
//			{
//				if (x == j || x==i) continue;
//				conter++;
//
//			}
//		}
//	}
//	printf("counter=%d\n", conter);
//	conter = 0;
//	for (int i = 1;i <= 4;++i)
//	{
//		for (int j = 1;j <= 4;j++)
//		{
//			if (i == j) continue;
//			for (int x = 1;x <= 4;x++)
//			{
//				if (x == j || x == i) continue;
//				printf("%d%d%d ", i, j, x);
//
//			}
//		}
//	}
//
//
//	return 0;
//}
//
//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	int n = 0;
//	printf("Enter a nonnegative integer:");
//	scanf("%d", &n);
//	for (int x = 1;;x++)
//	{
//		if (n >= pow(10, x - 1) && n < pow(10, x))
//		{
//			printf("The number has %d digit(s).\n",x);
//			break;
//		}
//	}
//	return 0;
//}



//#include<stdio.h>
//
//
//double cun(int n)
//{
//	double x = 20 / n;
//	double a = 0;
//	if (n == 1)
//	{
//		a = 0.063;
//	}
//	else if (n == 2)
//	{
//		a = 0.066;
//	}
//	else if (n == 3)
//	{
//		a = 0.069;
//	}
//	else if (n == 5)
//	{
//		a = 0.075;
//	}
//	else if (n == 8)
//	{
//		a = 0.084;
//	}
//	return 2000 * (1 + a) * x * n * 12;
//
//
//}
//
//int main()
//{
//
//	double x1 = cun(1);
//	double x2 = cun(2);
//	double x3 = cun(3);
//	double x5 = cun(5);
//	double x8 = cun(8);
//
//
//	return 0;
//}
//
//
//
//#include <stdio.h>
//#include <math.h>
//
//void main(void)
//{
//    int x, y, z, m, n, y1, y2, y3, y5, y8;
//    double max = 0.0, result;
//    for (n = 0;n <= 2;n++)
//        for (m = 0;m <= (20 - 8 * n) / 5;m++)
//            for (z = 0;z <= (20 - 8 * n - 5 * m) / 3;z++)
//                for (y = 0;y <= (20 - 8 * n - 5 * m - 3 * z) / 2;y++)
//                {
//                    x = 20 - 8 * n - 5 * m - 3 * z - 2 * y;
//                    result = 2000.0 * pow((1 + 0.0063 * 12), x) * pow((1 + 0.0066 * 12 * 2), y) * \
//                        pow((1 + 0.0069 * 12 * 3), z) * pow((1 + 0.0075 * 12 * 5), m) * pow((1 + 0.0084 * 12 * 8), n);
//                    if (result > max)
//                    {
//                        max = result;
//                        y1 = x;
//                        y2 = y;
//                        y3 = z;
//                        y5 = m;
//                        y8 = n;
//                    }
//                }
//    printf("获利最多的存款方式：\n");
//    printf("8年期限存了%d次\n", y8);
//    printf("5年期限存了%d次\n", y5);
//    printf("3年期限存了%d次\n", y3);
//    printf("2年期限存了%d次\n", y2);
//    printf("1年期限存了%d次\n", y1);
//    printf("最终本利为%0.2f \n", max);
//}
//
//

//#include<stdio.h>
//
//
//int main()
//{
//
//	int P = 0, E = 0, A = 0, R = 0;
//
//	for (P=1;P <= 9;P++)
//	{
//		for (E=0;E <= 9;E++)
//		{
//			for (A=1;A <= 9;A++)
//			{
//				for (R=0;R <= 9;R++)
//				{
//					int x = 1000 * P + 100 * E + 10 * A + R;
//					int y = 100 * A + 10 * R + A;
//					int z = 100 * P + 10 * E + A;
//					if(x-y == z)
//					{
//						printf("    PEAR        %d%d%d%d\n", P, E, A, R);
//						printf("     ARA       -  %d%d%d\n", A, R, A);
//						printf("-----------   ----------------\n");
//						printf("     PEA           %d%d%d\n", P, E, A);
//						goto hahaha;
//					}
//				}
//			}
//		}
//	}
//hahaha:
//
//
//
//	return 0;
//}
//
//#include<stdio.h>
//
//
//int main()
//{
//	int min = 0, max = 0;
//	int arr[10] = { 0 };
//	for (int i = 0;i < 10;i++)
//	{
//		scanf("%d", &arr[i]);
//	}
//	int a = arr[0];
//	for (int i = 1;i <=9;i++)
//	{
//		if(arr[0] > arr[i])
//		{
//			arr[0] = arr[i];
//		}
//	}
//	min = arr[0];
//	arr[0] = a;
//	for (int i = 1;i <= 9;i++)
//	{
//		if (arr[0] < arr[i])
//		{
//			arr[0] = arr[i];
//		}
//	}
//	max = arr[0];
//	arr[0] = a;
//	printf("sum=%3d",min+max);
//
//
//	return 0;
//}



//#include<stdio.h>
//
//
//int main()
//{
//	int n = 0;
//	printf("请输入n:");
//	scanf("%d", &n);
//	double sum = 0;
//	long long mr[10000] = { 0 };
//	for (long long m = 1;sum<n+1 ;m++)
//	{
//		sum += 1.0 / m;
//		if (sum > n && sum < n + 1)
//		{
//			mr[m] = m;
//		}
//	}
//	long long min = 0, max = 0;
//	for (int i = 0;;i++)
//	{
//		if (mr[i] != 0)
//		{
//			min = mr[i];
//			break;
//		}
//	}
//	for (int i = 9999;;i--)
//	{
//		if (mr[i] != 0)
//		{
//			max = mr[i];
//			break;
//		}
//	}
//	printf("满足不等式的m为:%ld<=m<=%ld\n",min,max);
//
//	return 0;
//}





#include<stdio.h>
#include<math.h>


//void JNTM(int n);
int Z(int n);



//int main()
//{
//	int n = 0;
//	int find = 0;
//	scanf("%d", &n);
//	for (int i = 2;i <= sqrt(n);i++)
//	{
//		if (n % i == 0)
//		{
//			find = 1;
//		}
//	}
//	if (find)
//	{
//		JNTM(n);
//	}
//	else
//	{
//		printf("Invalid input.\n");
//	}
//	return 0;
//}


//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		printf("hehe");
//		if (n % i == 0 || n==1 ) return 0;
//	}
//	return 1;
//}
//
//int main()
//{
//	int n = Z(1);
//	printf("%d\n", n);
//	printf("%lf", sqrt(1));
//}



//
//void JNTM(int n)
//{
//	for (int i = 2;i <= n;i++)
//	{
//		if (Z(i) && n % i == 0)
//		{
//			n /= i;
//			printf("%d", i);
//			if (n != 1)
//			{
//				printf(","); JNTM(n);
//				break;
//			}
//
//		}
//	}
//
//}


//#include<stdio.h>
//#include<math.h>
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//int main()
//{
//	int a = 0, b = 0;
//	scanf("%d %d", &a, &b);
//	int find = 0;
//	int arr[20] = { 0 };
//	for (int i = a;i <= b;i++)
//	{
//		find = 0;
//		if (Z(i))
//		{
//			for (int n = 1;n <= 10;n++)
//			{
//				if (i > pow(10, n - 1) && i < pow(10, n))
//				{
//					int A = i;
//					for (int x = 0;x < n;x++)
//					{
//						int B = (int)(A / pow(10, x)) % 10;
//						arr[x] = B;
//
//					}
//					for (int y = 0;y < (n + 1) / 2;y++)
//					{
//						if (arr[y] != arr[n-1-y])
//						{
//							find = 1;
//						}
//					}
//				}
//			}
//			if (!find && Z(i))
//			{
//				printf("%d\n", i);
//			}
//		}
//	}
//
//
//
//
//	return 0;
//}







//
//#include<stdio.h>
//
//int main()
//{
//
//	int hour = 0;
//	int smin = 0;
//	int mmin = 0;
//
//	while (hour < 24)
//	{
//		printf("%d:", hour);
//		printf("%d", smin);
//		printf("%d\t", mmin);
//		if (mmin < 10)
//		{
//			mmin++;
//		}
//		if (mmin == 10 && smin<6)
//		{
//			mmin = 0;
//			smin++;
//		}
//		if (smin == 6)
//		{
//			smin = 0;
//			hour++;
//		}
//
//
//	}
//
//
//	return 0;
//}



//#include<stdio.h>
//#include<math.h>
//
//int main()
//{
//
//	int i = 0, j = 0;
//	int a = 0;
//
//	for (i = 0;i < 10;i++)
//	{
//		for (j = 0;j < 10;j++)
//		{
//			int x = i * 1000 + i * 100 + j * 10 + j;
//			for (int n = 1;n < 100;n++)
//			{
//				if (sqrt(x) == n)
//				{
//					a = n;
//				}
//			}
//		}
//	}
//	printf("“肇事车牌号码为：%d。”",310000 + a * a);
//
//
//	return 0;
//}

//#include<stdio.h>
//
//main()
//{
//    int  m = 0;
//    int  i = 0;
//    int  sum = 0;
//    for (i = 1; ;i++)
//    {
//        sum = sum + i * i * i;
//        if (sum >= 1000000)
//            break;
//    }
//    m = i-1;
//    printf("m = %d\n", m);
//}

//#include<stdio.h>
//
//
//int main()
//{
//	int n = 0;
//	int sum = 0;
//	int count = 0;
//	do
//	{
//		printf("Input a number:\n");
//		scanf("%d", &n);
//		if (n > 0)
//		{
//			sum += n;
//			count++;
//		}
//
//
//	}while(n);
//	printf("sum=%d,count=%d\n", sum, count);
//
//	return 0;
//}

//
//#include<stdio.h>


//int main()
//{
//
//	int i = 1;
//	for (;i != 0;i++)
//	{
//		;
//	}
//	i -= 1;
//	printf("%f", i / 365.0);
//
//
//	return 0;
//}




//#include <stdio.h>
//#include <math.h>
//
//int main(int argc, char* argv[])
//{
//	printf("%f\n", ((ldexp(1.0, 32)) / (365 * 24 * 60 * 60)));
//	return 0;
//}

//#include<stdio.h>
//
//int QMS(int x)
//{
//	int sum = 0;
//	for (int i = 2;i < x;i++)
//	{
//		if (x % i == 0)
//		{
//			sum += i;
//		}
//	}
//	return sum + 1;
//}
//
//int main()
//{
//	for (int A = 2;A <= 10000;A++)
//	{
//		int B = QMS(A);			//a为x全部因子之和 即 a就是B x就是A
//		int a = QMS(B);			//b为B全部因子之和
//		if (a == A && A<B)			//检验A与B的因子之和是否相等
//		{
//			printf("(%4d,%4d)\n", A,B);
//		}
//	}
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//
//	printf("   *\n");
//	printf("  ***\n");
//	printf(" *****\n");
//	printf("*******\n");
//	printf(" *****\n");
//	printf("  ***\n");
//	printf("   *\n");
//
//
//
//
//	return 0;
//}

//#include<stdio.h>
//int main()
//{
//	int n = 0;
//	int count = 0;
//	double sum = 0;
//	double grade = 0;
//	printf("Enter n: ");
//	scanf("%d", &n);
//
//	for (int i = 1;i <= n;i++)
//	{
//		printf("Enter grade #%d: ",i);
//		scanf("%lf", &grade);
//		sum += grade;
//		if (grade < 60) count++;
//	}
//	printf("Grade average = %.2f\n", sum / n);
//	printf("Number of failures = %d\n", count);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	int a[30] = { 1 };
//	int sum = 0;
//	printf("This program sums a series of integers.\n");
//	printf("Enter integers (0 to terminate):");
//	for (int i = 0;;i++)
//	{
//		scanf("%d", &a[i]);
//		sum += a[i];
//		if (a[i] == 0)
//		{
//			break;
//		}
//	}
//	printf("The sum is: %d\n", sum);
//
//	return 0;
//}


//#include<stdio.h>
//
//int count = 5;
//
//sp(int fish)
//{
//	fish -= 1;
//	if (fish % 5 == 0 && count !=0)
//	{
//		fish = fish * 4 / 5;
//		count--;
//		sp(fish);
//	}
//	if (count == 0)
//	{
//		return 1;
//	}
//	else
//	{
//		count = 5;
//		return 0;
//	}
//}
//
//int main()
//{
//	int fish = 0;
//	int a = 0;
//	for (fish = 1;;fish++)
//	{
//		if (sp(fish))
//		{
//			printf("Total number of fish catched=%d\n", fish);
//			break;
//		}
//	}
//	return 0;
//}




//#include<stdio.h>
//
//
//int main()
//{
//	for (int x = 0;x < 10;x++)
//	{
//		for (int y = 0;y < 10;y++)
//		{
//			for (int z = 0;z < 10;z++)
//			{
//				if ((x * 100 + 10 * y + z) + (y * 100 + 10 * z + z) == 532)
//				{
//					printf("x=%d,y=%d,z=%d\n", x, y, z);
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}



//#include<stdio.h>
//#include<math.h>
//int Nbit(int x)
//{
//	int n = 1;
//	for (;n <= 12;n++)
//	{
//		if (x >= pow(10, n - 1) && x < pow(10, n))
//			break;
//	}
//	return n;
//}
//
//long long Weico(long long x,int n)
//{
//	return x % (long long)pow(10, n);
//}
//
//
//
//int main()
//{
//
//	printf("It exists following automorphic numbers smaller than 200000:\n");
//	for (long long i = 0;i <= 200000;i++)
//	{
//		int n = Nbit(i);
//		long long w = Weico(i * i,n);
//		if (i == w)
//		{
//			printf("  %ld", w);
//		}
//	}
//
//
//	return 0;
//}







//#include<stdio.h>
//
//int main()
//{
//	int i = 0;
//	float mon = 0;
//	for (i = 5;i > 0;i--)  //i第几年末
//	{
//		mon += 1000;
//		mon = mon / (1 + (12 * 0.0063));   // x/(1+c) = x
//	}
//
//	printf("He must save %.2f at first.\n", mon);
//
//
//
//	return 0;
//}




//
///*#include<stdio.h>
//
//int main()
//{
//	int n = 0;
//	printf("Enter n:");
//	scanf("%d", &n);
//	for (int i = 0;i <= n;i++)
//	{
//		printf("pow(2,%d)= %.0f\n", i, pow(2, i));
//	}
//
//
//
//	retur*/n 0;
//}

//#include<stdio.h>
//
//int main()
//{
//
//	int x = 0;
//	printf("Input a 4 digits number\n");
//	scanf("%d", &x);
//	int a = x % 10;
//	int b = x / 10 % 10;
//	int c = x / 100 % 10;
//	int d = x / 1000;
//	a += 5; b += 5; c += 5; d += 5;
//	a %= 10;b %= 10;c %= 10;d %= 10;
//	int o = 0;
//	o = d;
//	d = a;
//	a = o;
//	o = c;
//	c = b;
//	b = o;
//
//	printf("%d", d * 1000 + c * 100 + b * 10 + a);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	float sum = 0;
//	float fz = 2;
//	float fm = 1;
//	for (int i = 1;i <= 20;i++)
//	{
//		sum += fz / fm;
//		int a = fz;
//		fz = fz + fm;
//		fm = a;
//	}
//	printf("总和=% 9.6f\n", sum);
//
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	int n = 1;
//	float sum = 0;
//	int count = 0;
//	for (int i = 1; 1.0/n>1e-5 ;i++)
//	{
//		n *= i;
//		sum += 1.0 / n;
//		count++;
//	}
//	printf("e = %f, count = %d\n", 1+sum, count+1);
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	char arr[100] = { 1 };
//	for (int i = 0;;i++)
//	{
//		scanf("%c", &arr[i]);
//		if (arr[i] == '\n') break;
//	}
//	for (int i = 0;;i++)
//	{
//		if (arr[i] == '\n') break;
//		printf("%c", arr[i]);
//	}
//
//}





//#include<stdio.h>
//
//int main()
//{
//	int count = 0;
//	int a = 0;
//	printf("Input m:");
//	scanf("%d", &a);
//	for(int i = 1;i <= a;i++)
//	{
//		for (int j = i;j <= a;j++)
//		{
//			for (int m = j;m <= a;m++)
//			{
//				if (i* i + j * j == m * m)
//				{
//					printf("%d %d %d\n", i, j, m);
//					count++;
//				}
//			}
//		}
//	}
//	printf("count=%d", count);
//
//
//	return 0;
//}




//#include<stdio.h>
//
//
//int main()
//{
//
//	printf("This program prints a table of squares.\n");
//	printf("Enter number of entries in table:\n");
//	int n = 0;
//	scanf("%d", &n);
//	for (int i = 1;i <= n;i++)
//	{
//		printf("%10d%10d\n", i, i * i);
//	}
//
//
//	return 0;
//}




//#include<stdio.h>
//
//
//int main()
//{
//    int i = 0, a = 0, n = 1;
//    while (n <= 7)
//    {
//        do
//        {
//            scanf("%d", &a);
//        } while (a < 1 || a>50);
//        for (i = 1;i <= a;i++)
//            printf("*");
//        printf("\n");
//        n++;
//    }
//
//    return 0;
//}


//#include<stdio.h>
//
//
//int main()
//{
//
//	int n = 0;
//	printf("Input n:\n");
//	scanf("%d", &n);
//	for (int i = 1;i <= n;i++)
//	{
//		printf("%4d", i);
//	}
//	printf("\n");
//	for (int i = 1;i <= n;i++)
//	{
//		printf("%4c", '-');
//	}
//	printf("\n");
//
//	for (int i = 1;i <= n;i++)
//	{
//		for (int j = i;j <= n;j++)
//		{
//			printf("%4d", i * j);
//		}
//		printf("\n");
//	}
//
//
//
//	return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//
//	printf("Input n:\n");
//	int n = 0;
//	scanf("%d", &n);
//	for (int i = 1;i <= n;i++)
//	{
//		for (int j = 1;j<=2*i-1;j++)		//i = 1 j = 1   2 3  3   5
//		{
//			printf("%c", '*');
//		}
//		printf("\n");
//	}
//
//
//	return 0;
//}



//
//
//
//
//#include<stdio.h>
//#include<math.h>
//
//
//int main()
//{
//    int n = 0;
//    long double sum = 0;
//    long long crash = 0;
//    printf("There are following Armstrong number smaller than 1000:\n");
//    for (n = 1; n <= 3; n++)
//    {
//        for (long double i = pow(10, n - 1); i < pow(10, n); i++)
//        {
//            crash = i;
//            sum = 0;
//            for (int j = 0; j < n; j++)
//            {
//                sum += pow((long double)(crash % 10), 3);
//                crash /= 10;
//            }
//            if (fabs(sum - i) <= 1e-6 && i != 1)
//            {
//                printf("%d ", (int)sum);
//            }
//
//        }
//    }
//
//    return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	float x = 0;
//	float x1 = 0, x2 = 0;
//	float y = 0;
//	printf("请输入x1，x2的值：");
//	scanf("%f,%f", &x1, &x2);
//	int find = 1;
//	while (find)
//	{
//		float u = (x1 + x2) / 2;
//		y = 2 * u * u * u - 4 * u * u + 3 * u - 6;
//		if (y == 0)
//		{
//			x = u; find = 0;
//		}
//		else if (y > 0)
//		{
//			x2 = u;
//		}
//		else
//		{
//			x1 = u;
//		}
//	}
//	printf("方程的根=%6.2f\n", x);
//
//	return 0;
//}




//#include<stdio.h>
//
//
//int main()
//{
//
//	int sum = 0;
//	int a = 0;
//	for (int i = 1;i <=10 ;i++)
//	{
//		printf("input a integer:");
//		scanf("%d", &a);
//		sum += a;
//	}
//	printf("sum=%d\n", sum);
//	printf("avg=%.2f\n", sum / 10.0);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	for (int i = 1;i <= 9;i++)
//	{
//		printf("%4d", i);
//	}
//	printf("\n-----------------------------\n");
//	for (int i = 1;i <= 9;i++)
//	{
//		for (int j = 1;j <= i;j++)
//		{
//			printf("%4d", i * j);
//		}
//		printf("\n");
//	}
//
//
//	return 0;
//}


//
//#include<stdio.h>
//#include<math.h>
//
//
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}

//
//
//
//int main()
//{
//	int n = 0;
//
//	while (1)
//	{
//		printf("Input a number:\n");
//		scanf("%d", &n);
//		if (n % 2 == 0) break;
//		printf("Input error!\n");
//		return 0;
//	}
//	int a = n;
//	for (int i = 2;i <= n-1;i++)
//	{
//		if (Z(i))
//		{
//			a -= i;
//			for (int j = 2;j <= n - 1;j++)
//			{
//				if (Z(j))
//				{
//					a -= j;
//					if (a == 0)
//					{
//						printf("%d=%d+%d\n", n, i, j);
//						return 0;
//					}
//					else a += j;
//				}
//			}
//			a += i;
//		}
//		
//	}
//
//	return 0;
//}
//

//
//#include<stdio.h>
//#include<math.h>
//
//
//int main()
//{
//	double s = 0;
//	long double ip = pow(2, 129) - 1;
//	for (int i = 1;;i++)
//	{
//		//ip = ip - pow(10, 6);
//		ip -= 1000000;
//		s++;
//		if (ip <= 0)
//			break;
//	}
//	double year = s / 60 / 60 / 24;
//	printf("%f", year);
//
//
//	return 0;
//}

//10790283070806013000000000.0


//#include<stdio.h>
//
//float my_sqrt(float n,float x)
//{
//	float X = (1.0 / 2) * (x + n / x);
//	float JDZ = 0;
//	if (X - x < 0) JDZ = x - X;
//	else JDZ = X - x;
//	if (JDZ < 1e-5) return X;
//	else return my_sqrt(n, X);
//}
//
//int main()
//{
//	float n = 0; 
//
//	printf("请输入一个整数：");  
//	scanf("%f", &n);
//	float x = my_sqrt(n,1.0);
//
//	printf("%5.2f的平方根=%8.5f\n", n, x);
//
//	return 0;
//}

//#include<stdio.h>
//#include<math.h>
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//int main()
//{
//	int count = 10;
//	int sum = 0;
//	for (int i = 500;i >= 2;i--)
//	{
//		if (Z(i) && count >0)
//		{
//			printf("%6d", i);
//			count--;
//			sum += i;
//		}
//		else if (count == 0)
//		{
//			break;
//		}
//	}
//	printf("\n sum=%d\n", sum);
//
//
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int main()
//{
//	int n = 0, k = 0;
//	printf("input integer n and k:\n");
//	scanf("%d%d", &n, &k);
//	for (int i = 1;i < k;i++)
//	{
//		n /= 10;
//	}
//	int a = n % 10;
//	printf("%d", a);
//
//
//	return 0;
//}
//


//#include<stdio.h>
//
//int main()
//{
//
//	double sum = 1;
//	for (float i = 2;i <= 100;i += 2)
//	{
//		sum *= i / (i - 1) * i / (i + 1);
//	}
//	printf("pi = %f\n", 2 * sum);
//
//	return 0;
//}

//#include<stdio.h>
//
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//
//int main()
//{
//	for (int i = 3;i < 100;i++)
//	{
//		for (int j = i + 2;j < 100;j++)
//		{
//			if (Z(i) && Z(j) && j == i + 2)
//			{
//				printf("%4d/%d", i, j);
//			}
//		}
//	}
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	int count = 0;
//	for (int i = 1;i <= 4;i++)
//	{
//		for (int j = 1;j <= 4;j++)
//		{
//			if (i == j) continue;
//			for (int m = 1;m <= 4;m++)
//			{
//				if (i != m && j != m)
//				{
//					printf(" % d % d % d\n", i, j, m);
//					count++;
//				}
//			}
//		}
//	}
//	printf("共有%d种组合！",count);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int main()
//{
//	int a[30] = { 0 };
//	int b[10] = { 0 };
//	int count = 0;
//	int sum = 0;
//	for (int i = 2;i <= 60;i += 2)
//	{
//		a[i / 2 - 1] = i;
//		count++;
//		sum += i;
//		if (count % 5 == 0)
//		{
//			b[count / 5 - 1] = sum / 5;
//			sum = 0;
//		}
//	}
//	for (int i = 0;i < 6;i++)
//	{
//		printf("%6d", b[i]);
//	}
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int PKB[15] = { 0 };  //放扑克
//
//	int i = 1;   //我要数的数  1-13;
//	int n = 0;   //盒子的下标  1-13;
//	int x = 0;   //一次数数种 我已数过的空盒子
//	for (i = 1;i <= 13;i++)  //我要一次数的数从1开始
//	{
//		
//		while (i != x)  //用循环开数 直到数了i个空盒子了
//                      //每次数一个空盒子都会进入检验循环 直接转到下一个空盒子
//		{
//			n++; //直接盒子往后一个
//			if (n > 13) n = 1; //数到第十四个盒子即为数到第一个盒子
//			x++; //数了一个空盒子
//			while (PKB[n])		//只要是非空盒子 就循环往后靠边
//			{
//				if (PKB[n]) n++;//非空盒子 默认往后靠边
//				if (n > 13) n = 1; //数到第十四个盒子即为数到第一个盒子
//			}
//		}
//		PKB[n] = i;
//		x = 0;
//	}
//
//	for (int m = 1;m <= 13;m++)
//	{
//		printf("%d ", PKB[m]);
//	}
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//
//	int I[3][3] = { 0 };
//	for (int i = 0;i < 3;i++)
//	{
//		for (int j = 0;j < 3;j++)
//		{
//			scanf("%d", &I[i][j]);
//		}
//	}
//	int max = 0, row = 0;
//	for (int i = 0;i < 3;i++)
//	{
//		if (I[i][i] > max)
//		{
//			max = I[i][i];
//			row = i;
//		}
//	}
//	printf("max=%d ,row=%d", max, row);
//
//	return 0;
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//int main()
//{
//    int sum = 0;
//    int  x, y;
//    printf("四位玫瑰花数有:");
//    for (int i = 1000; i < 10000; i++)
//    {
//        y = i * 10;
//        for (int j = 1; j <= 4; j++)
//        {
//            y = y / 10;
//            x = y % 10;
//            sum += x * x * x * x;
//
//        }
//        if (sum == i)
//        {
//            printf("%d\t", i);
//        }
//        sum = 0;
//    }
//    return 0;
//}


//#include<stdio.h>
//#include<math.h>
//
//
//int main()
//{
//	int sum = 0;
//	for (int i = 1000;i <= 9999;i++)
//	{
//		int a = i;
//		for (int j = 0;j < 4;j++)
//		{
//			a = (int)(a / pow(10, j)) % 10;
//			sum += (int)(a * pow(10, 3 - j));
//			a = i;
//		}
//		if (i * 9 == sum)
//		{
//			printf("%d", i);
//			break;
//		}
//		sum = 0;
//
//	}
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	char a[10] = "ABCDEF";
//	for (int i = 0;i <= 5;i++)
//	{
//		
//		printf("%s", a+i);
//		
//		printf("\n");
//	}
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int count = 0;
//	for (int i = 1;i <= 9;i++)
//	{
//		for (int j = 0;j <= 9;j++)
//		{
//			if (i == j) continue;
//			for (int m = 0;m <= 8;m+=2)
//			{
//				if (m != i && m != j)
//				{
//					count++;
//				}
//			}
//		}
//	}
//	printf("%d\n",count);
//
//}


//#include<stdio.h>
//
//int main()
//{
//	int count = 0;
//	for (int i = 1;i <= 5;i++)
//	{
//		for (int j = 1;j <= 5;j++)
//		{
//			if (i == j) continue;
//			for (int m = 1;m <= 5;m++)
//			{
//				if (m != i && m != j)
//				{
//					count++;
//					printf("%d:%d,%d,%d\n", count, i, j, m);
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	double sum = 0;
//	double sign = 1;  //定义符号变量
//	int count = 0;
//	double i = 0;
//	for (i = 1;(1/i)>1e-4;i += 2)
//	{
//		sum += sign / i;
//		sign = -sign;
//		count++;
//	}
//	printf("pi = %f\ncount = %d\n", sum *4, count+1);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int GCD(int a,int b)
//{
//	int max0 = a > b ? a : b;
//	int max = 0;
//	for (int i = 1;i <= max0;i++)
//	{
//		if (a % i == 0 && b % i == 0)
//		{
//			max = i;
//		}
//	}
//	return max;
//
//}
//
//int LCM(int a, int b)
//{
//	int max0 = a > b ? a : b;
//	for (int i = max0;;i++)
//	{
//		if (i % a == 0 && i % b == 0)
//		{
//			return i;
//		}
//	}
//
//}
//
//
//int main()
//{
//	printf("Input a & b:");
//	int a = 0, b = 0;
//	scanf("%d%d", &a, &b);
//	int gcd = GCD(a,b);
//	int lcm = LCM(a,b);
//	printf("The GCD of %d and %d is:%d\n",a,b,gcd);
//	printf("The LCM of them is:%d\n", lcm);
//	return 0;
//
//}



//#include<stdio.h>
//#include<math.h>
//
//int main()
//{
//	double n = 0;
//	printf("Input n:");
//	scanf("%lf", &n);
//	for (double m = 1;;m++)
//	{
//		double sum = 0;
//		for (int i = 0;i <= m;i++)
//		{
//			sum += sqrt(m+i);
//		}
//		if (sum > n)
//		{
//			printf("m>=%d\n",(int)m);
//			break;
//		}
//		else sum = 0;
//	}
//	return 0;
//}



//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	printf("Please enter the number:\n");
//	int n = 0;
//	scanf("%d", &n);
//	int x = 0;
//	int m = n > 0 ? n : -n;
//	for (x = 1;;x++)
//	{
//		if (m >= pow(10, x - 1) && m < pow(10, x))
//		{
//			break;
//		}
//	}
//	printf("%d: %d bits\n",n, x);
//
//	return 0;
//}


//#include<stdio.h>
//
//
//
//int main()
//{
//
//	long x = 0;
//	printf("Please input number");
//	scanf("%ld", &x);
//	int max = 0;
//	for (int i = 100;i <= 999;i++)
//	{
//		if (x % i == 0)
//		{
//			max = i;
//		}
//	}
//	printf("The max factor with 3 digits in %ld is %d.\n", x, max);
//
//}


//#include <stdio.h>
//#include <math.h>
//int main()
//{
//    int m = 0, i = 0;
//    for (m = 100; m <= 200; m++)
//    {
//        int flag = 1;
//        for (i = 2; i <= sqrt(m) && flag; i++)
//        {
//            if (m % i == 0) 
//            {
//                flag = 0;
//            }
//        }
//        if (flag)
//        {
//            printf("%d ", m);
//        }
//    }
//    return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	char a[18] = "12345678987654321";
//	char b[17] = "                 ";
//	for (int i = 0;i <= 16 - i;i++)
//	{
//		printf("%s\n", a);
//		a[i] = b[i];
//		a[16 - i] = b[16 - i];
//	}
//
//}

//#include<stdio.h>
//
//int main()
//{
//	for (long i = 10000;i <= 99999;i++)
//	{
//		for (int j = 10;j <= 99;j++)
//		{
//			for (int m = 1;m <= 9;m++)
//			{
//				for (int n = 1;n <= 9;n++)
//				{
//					if (j * m == n * 100 + 77)
//					{
//						for (int x = 1;x <= 9;x++)
//						{
//							for (int y = 1;y <= 9;y++)
//							{
//								if (j * 7 == 100 * x + 70 + y)
//								{
//									for (int z = 1;z <= 9;z++)
//									{
//										for (int I = 10;I <= 99;I++)
//										{
//											if (j * z == I)
//											{
//												if (j * (m * 100 + 70 + z) == i)
//												{
//													printf("%ld/%d=%d\n",i,j,m*100+70+z);
//														break;
//												}
//											}
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}

//#include<stdio.h>
//
//
//int main()
//{
//	int count = 0;
//	printf("   RED BALL  WHITE BALL  BLACK BALL\n");
//	printf("----------------------------------------\n");
//	for (int i = 0;i <= 3;i++)
//	{
//		for (int j = 0;j <= 3;j++)
//		{
//			for (int m = 0;m <= 6;m++)
//			{
//				if (i + j + m == 8)
//				{
//					count++;
//					printf("%2d:  %d   %d    %d\n", count, i, j, m);
//				}
//			}
//		}
//	}
//
//
//	return 0;
//}



//#include "stdio.h"
//main()
//{
//    int i, a, n = 1;
//    while (n <= 7)
//    {
//        do
//        {
//            scanf("%d", &a);
//        } while (a < 1 || a>50);
//        for (i = 1;i <= a;i++)
//            printf("*");
//        printf("\n");
//        n++;
//    }
//}



//#include<stdio.h>
//
//int Fib(int n)
//{
//	if (n != 1 && n != 2)
//	{
//		return Fib(n - 1) + Fib(n - 2);
//	}
//	else
//		return 1;
//
//}
//
//int main()
//{
//	printf("Input n=?");
//	int n = 0;
//	scanf("%d", &n);
//	int x = Fib(n);
//	printf("No. %d is %d\n", n, x);
//
//	return 0;
//}


//#include<stdio.h>
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//
//
//int main()
//{
//	int count = 0;
//	for (int i = 1;i <= 100;i++)
//	{
//		if (Z(i))
//		{
//			printf("%3d", i);
//			count++;
//			if (count % 5 == 0)
//				printf("\n");
//		}
//	}
//	return 0;
//}

//#include<stdio.h>
//
//
//int main()
//{
//	float a = 1;
//	float b = 2;
//	float sum = 0;
//	for (int i = 1;i <= 20;i++)
//	{
//		sum += b / a;
//		float c = a;
//		a = b;
//		b = b + c;
//	}
//	printf("sum is %9.6lf\n", sum);
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	printf("       *\n");
//	printf("      ***\n");
//	printf("     *****\n");
//	printf("    *******\n");
//
//
//}


//#include<stdio.h>
//
//int main()
//{
//	printf("Enter a message:");
//	char a[100] = { 0 };
//	for (int i = 0;;i++)
//	{
//		scanf("%c", &a[i]);
//		if (a[i] == '\n')
//		{
//			break;
//		}
//	}
//
//	int count = 0;
//	for (int i = 0;a[i];i++)
//	{
//		count++;
//	}
//	printf("Your message was %d character(s) long.\n", count-1);
//
//	return 0;
//}




//
//#include<stdio.h>
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//int main()
//{
//	int n = 0;
//	printf("Please enter a number:");
//	scanf("%d", &n);
//	if (Z(n))
//	{
//		printf("It is a prime number.No divisor!\n");
//	}
//	else if (n == 1 || n == 0 || n == -1)
//	{
//		printf("It is not a prime number.No divisor!\n");
//	}
//	else
//		for (int i = 2;i <= n - 1;i++)
//		{
//			if (n % i == 0)
//			{
//				printf("%d\n", i);
//			}
//		}
//
//	return 0;
//}


//#include<stdio.h>
//
//const double cur = 100;
//
//int main()
//{
//	printf("Input grow rate:");
//	double rate = 0;
//	scanf("%lf", &rate);
//	double CUR = cur;
//	int count = 0;
//	double x = cur;
//	while (x < 2 * CUR)
//	{
//		x *= (1 + rate);
//		count++;
//	}
//	rate *= 100;
//	printf("When grow rate is %.0f%%, the output can be doubled after %d years.\n", rate, count);
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	double F = 0;
//	double t = 0;
//	for (F = 0;F <= 300;F += 20)
//	{
//		t = 5.0 / 9 * (F - 32);
//		printf("%4.0f%10.1f\n", F, t);
//	}
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int a = 0;
//	for (int i = 1;;i++)
//	{
//		if (i % 8 == 1)
//		{
//			if (i / 8 % 8 == 1)
//			{
//				if (i / 8 / 8 % 8 == 7)
//				{
//					a = i/8/8/8;
//					if (i % 17 == 4)
//					{
//						if (i / 17 % 17 == 15)
//						{
//							if (i / 17 / 17 == 2 * a)
//							{
//								printf("The required number is :%d\n", i);
//								break;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}




//#include<stdio.h>
//
//int main()
//{
//	for (int i = 0;i <= 3;i++)
//	{
//		for (int j = 0;j <= 3;j++)
//		{
//			for (int m = 2;m <= 6;m++)
//			{
//				if (i + j + m == 8)
//				{
//					printf("i=%d, j=%d, k=%d\n", i, j, m);
//				}
//			}
//		}
//	}
//}


//
//#include<stdio.h>
//main()
//{
//	double term, result = 1;
//	int n;
//	for (n = 2; n <= 100; n = n + 2)
//	{
//		term = (double)(n * n) / ((n - 1) * (n + 1));
//		result = result * term;
//	}
//	printf("result = %f\n", 2 * result);
//}


//#include<stdio.h>
//
//
//int main()
//{
//	printf("\tMEN\tWOMEN\tCHILDREN\n");
//	printf("-----------------------------------------\n");
//	int count = 0;
//	for (int i = 0;i <= 17;i++)
//	{
//		for (int j = 0;j <= 25;j++)
//		{
//			for (int m = 0;m <= 50;m++)
//			{
//				if (i + j + m == 30 && 3 * i + 2 * j + m == 50)
//				{
//					count++;
//					printf("%2d:\t%d\t%d\t%d\n",count, i, j, m);
//				}
//			}
//		}
//	}
//	return 0;
//}


//
//#include<stdio.h>
//
//int main()
//{
//	int n = 0;
//	int sum = 0;
//	for (int i = 1;i <= 10;i++)
//	{
//		printf("Enter the No.%d=", i);
//		scanf("%d", &n);
//		sum += n;
//	}
//	printf("Total=%d\n", sum);
//}




//#include<stdio.h>
//
//int main()
//{
//	int a[100] = { 0 };
//	int a1 = 0;
//	int d = 0;
//	for (a1 = 1;a1<=20;a1++)
//	{
//		for (d = 0;d<=20;d++)
//		{
//			for (int i = 0;i<=3;i++)
//			{
//				a[i] = a1 + i * d;
//			}
//			if (a[0] + a[1] + a[2] + a[3] == 26 && a[0] * a[1] * a[2] * a[3] == 880)
//			{
//				goto haha;
//			}
//		}
//	}
//haha:
//
//	for (int i = 0;i <= 20;i++)
//	{
//		a[i] = a1 + i * d;
//		printf("%d, ", a[i]);
//	}
//	printf("......\n");
//
//
//	return 0;
//}




//#include<stdio.h>
//
//
//int getint(int min, int max)
//{
//	int o = 0;
//	do
//	{
//		printf("Please enter an integer [%d..%d]:\n", min, max);
//		scanf("%d", &o);
//
//	} while (o > max || o < min);
//		return o;
//
//
//}
//
//int main()
//{
//	int min = 0;
//	int max = 0;
//	scanf("%d,%d", &min, &max);
//	int x = getint(min, max);
//	printf("The integer you have entered is:%d\n", x);
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//
//	int a = 0;
//	int n = 0;
//	printf("please input a and n\n");
//	scanf("%d,%d", &a, &n);
//	printf("a=%d,n=%d\n", a, n);
//	long sum = 0;
//	int xi = a;
//	for (int i = 1;i <= n;i++)
//	{
//		sum += xi;
//		xi += pow(10, i) * a;
//	}
//	printf("a+aa+...=%ld\n", sum);
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	printf("四位玫瑰花数有:");
//	for (int i = 1000;i <= 9999;i++)
//	{
//		int x = i;
//		int sum = 0;
//		for (int j = 0;j < 4;j++)
//		{
//			int y = x % 10;
//			sum += y * y * y * y;
//			x /= 10;
//		}
//		if (sum == i)
//		printf("%d\t", i);
//	}
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int n = 1;
//	int sum = 0;
//	while (n)
//	{
//		printf("Input num:");
//		scanf("%d", &n);
//		sum += n;
//		printf("sum = %d\n", sum);
//	}
//
//
//
//	return 0;
//}


//
//#include<stdio.h>
//
//int main()
//{
//	double Mmon = 0;
//	double Bmon = 0;
//	double o = 0.01;
//	for (int i = 1;i <= 30;i++)
//	{
//		Mmon += 100000;
//	}
//	for (int i = 1;i <= 30;i++)
//	{
//		Bmon += o;
//		o *= 2;
//	}
//	printf("to Stranger: %.2f yuan\n", Bmon);
//	printf("to Richman: %.2f yuan\n", Mmon);
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//
//	printf("%d,%d,%d,%d\n", 0, 0, 0, 1);
//	printf("D说得正确.\n");
//
//
//	return 0;
//}


//
//
//#include<stdio.h>
//
//int main()
//{
//	int sum = 0;
//	int count = 0;
//	for (int i = 1;i <= 10;i++)
//	{
//		int n = 0;
//		printf("Input integer:");
//		scanf("%d", &n);
//		if (n > 0)
//		{
//			count++;
//			sum += n;
//		}
//	}
//	double x = sum / (double)count;
//	printf("Plus number:%d,average value:%.2f", count, x);
//
//
//	return 0;
//}


//#include <stdio.h>
//
//main()
//{
//    int i, j, k, n;
//
//    printf("result is:");
//    for (n = 100; n < 1000; n++)
//    {
//        i = n % 10;
//        j = n / 10 % 10;
//        k = n / 100;
//        if (n == i * i * i + j * j * j + k * k * k)
//        {
//            printf("%d\t", n);
//        }
//    }
//    printf("\n");
//}



//#include<stdio.h>
//
//int main()
//{
//	char a, b, c;
//	for (int i = 1;i < 2;i++)
//	{
//		for (int j = 0;j <= 2;j++)
//		{
//			if (i == j) continue;
//			for (int m = 0;m < 2;m++)
//			{
//				if (m == i || m == j) continue;
//				if (j == 0) a = 'y';
//				else if (m == 0) a = 'z';
//				b = 'x';
//				if (j == 2) c = 'y';
//				printf("顺序为：\na--%c\tb--%c\tc--%c\n", a, b, c);
//
//			}
//		}
//	}
//
//
//
//	return 0;
//}


//
//#include<stdio.h>
//
//int main()
//{
//
//	for (int i = 1;i <= 9;i++)
//	{
//		for (int j = 1;j <= i;j++)
//			printf("%4d", i * j);
//		printf("\n");
//	}
//
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	int sum = 1;
//	for (int i = 1;i <= 10;i++)
//	{
//		sum *= i;
//		printf("  %2d!=%ld", i, sum);
//		if (i % 5 == 0)
//		{
//			printf("\n");
//		}
//	}
//
//
//	return 0;
//}



//#include<stdio.h>
//
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//
//
//int main()
//{
//	printf("Please input c and d(c>2):");
//	long c = 0, d = 0;
//	scanf("%ld,%ld", &c, &d);
//	for (long i = c;i <= d;i++)
//	{
//		if (Z(i) && Z(i + 2) && i+2 <=d)
//		{
//			printf("(%ld,%ld)", i, i + 2);
//		}
//
//	}
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	printf("Input days:\n");
//	int n = 0;
//	scanf("%d", &n);
//	int tao = 1;
//	for (int i = n-1;i >= 1;i--)
//	{
//		tao += 1;
//		tao *= 2;
//
//	}
//	printf("x=%d\n", tao);
//
//}


//kkkkkkkkkkkkkkkkk

//
//#include<stdio.h>
//
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//
//int main()
//{
//	printf("\nplease input a number:\n");
//	int n = 0;
//	scanf("%d", &n);
//	printf("%d=",n);
//	int a = n;
//	for (int i = 2;i <= a - 1;i++)
//	{
//		if (Z(i) && n % i == 0)
//		{
//			n /= i;
//			if (n != 1)
//			{
//				printf("%d*", i);
//				i--;
//			}
//			else
//			{
//				printf("%d", i);
//				i--;
//			}
//		}
//	}
//
//
//	return 0;
//}
//
//
//#include<stdio.h>
//
//int main()
//{
//
//	printf("Input n:");
//	int n = 0;
//	scanf("%d", &n);
//	int a = n / 100;
//	int b = n % 100;
//	int sum = a + b;
//	int sub = a - b;
//	int multi = a * b;
//	float dev = 0;
//	printf("%d,%d\n", a, b);
//	printf("sum=%d,sub=%d,multi=%d\n", sum, sub, multi);
//	if (b != 0)
//	{
//		dev = (float)a / b;
//		int mod = a % b;
//		printf("dev=%.2f,mod=%d\n", dev, mod);
//	}
//	else
//	{
//		printf("The second operator is zero!\n");
//	}
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//	//char a[7] = "ABCDEF";
//	//for (int i = 0;i < 7;i++)
//	//{
//	//	for (int j = i;j < 7;j++)
//	//	{
//	//		printf("%c", a[j]);
//	//	}
//	//	if(i != 5)
//	//	printf("\n");
//	//}
//	printf("ABCDEF\n");
//	printf("BCDEF\n");
//	printf("CDEF\n");
//	printf("DEF\n");
//	printf("EF\n");
//	printf("F");
//
//
//	return 0;
//}


//#include<stdio.h>
//
//
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//
//int main()
//{
//	int sum = 0;
//	for (int i = 2;i <= 100;i++)
//	{
//		if (Z(i))
//		{
//			sum += i;
//			printf("%d\n", i);
//		}
//	}
//	printf("sum of prime numbers:%d\n", sum);
//
//	return 0;
//}


//#include<stdio.h>
//
//
//int main()
//{
//	printf("Input n:\n");
//	int n = 0;
//	scanf("%d", &n);
//	for (int i = 1;i <= n;i++)
//	{
//		printf("%4d", i);
//	}
//	printf("\n");
//	for (int i = 1;i <= n;i++)
//	{
//		printf("%4c", '-');
//	}
//	printf("\n");
//	//for (int i = 1;i <= n;i++)
//	//{
//	//	for (int j = 1;j <= i;j++)
//	//	{
//	//		printf("%4d", i * j);
//	//	}
//	//	printf("\n");
//	//}
//	for (int i = 1;i <= n;i++)
//	{
//		for (int j = 1;j <= n;j++)
//		{
//			printf("%4d", i * j);
//		}
//		printf("\n");
//	}
//
//
//	return 0;
//}


//#include<stdio.h>
//
//main()
//{
//	int x, y, z;
//	for (x = 0; x <= 20; x++)
//	{
//		for (y = 0; y <= 33; y++)
//		{
//			z = 100 - x - y;
//			if (15*x + 9*y + z == 300)
//			{
//				printf("x=%d, y=%d, z=%d\n", x, y, z);
//			}
//		}
//	}
//}


//#include<stdio.h>
//
//int main()
//{
//	for (int i = 1;i <= 9;i++)
//	{
//		for (int j = 1;j <= 9;j++)
//		{
//			if (j >= i)
//			{
//				printf("%4d", j * i);
//			}
//			else printf("%4c", ' ');
//		}
//		printf("\n");
//	}
//
//
//
//	return 0;
//}

//
//#include<stdio.h>
//
//
//int main()
//{
//	int count = 1;
//	int max = 0;
//	int min = 999;
//	int sum = 0;
//	do
//	{
//		printf("Input score %d\n",count);
//		int sc = 0;
//		scanf("%4d", &sc);
//		count++;
//		sum += sc;
//		if (max < sc)
//		{
//			max = sc;
//		}
//		if (min > sc)
//		{
//			min = sc;
//		}
//
//	} while (count != 11);
//	sum = sum - min - max;
//	printf("Canceled max score: %d\nCanceled min score: %d\n", max, min);
//	printf("Average score: %d\n",sum/8);
//
//	return 0;
//}






//
//#include<stdio.h>
//
//int main()
//{
//	int year1 = 0;
//	int year2 = 0;
//	scanf("%d,%d", &year1,&year2);
//	int find = 0;
//	if (year1 <= year2)
//	{
//		for (int i = year1;i <= year2;i++)
//		{
//			if (i % 4 == 0 && i % 100 != 0 || i % 100 == 0 && i % 400 == 0)
//			{
//				printf("%d  ", i);
//				find = 1;
//			}
//		}
//		if (!find)
//		{
//			printf("在此期间没有闰年\n");
//		}
//	}
//	else printf("输入不合法");
//	return 0;
//}


//
//
//#include<stdio.h>
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//int main()
//{
//	printf("Following are palindrome primes not greater than 1000:\n");
//	for (int i = 10;i <= 1000;i++)
//	{
//		if (i <100 && i % 10 == i / 10 && Z(i))
//		{
//			printf("%d\t", i);
//		}
//		else if (i >= 100 && i % 10 == i / 100 && Z(i))
//		{
//			printf("%d\t", i);
//		}
//
//
//	}
//	
//	return 0;
//}




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
//	printf("There are following friendly-numbers pair smaller than 3000:\n");
//	for (int i = 1;i <= 3000;i++)
//	{
//		int B = SumPrime(i);
//		if (SumPrime(B) == i  && i < SumPrime(i))
//		{
//			printf("   %4d..%4d", i, SumPrime(i));
//		}
//	}
//
//	return 0;
//}

//
//#include<stdio.h>
//
//int main()
//{
//	printf("The special number with 3 digits is:");
//	for (int i = 1;i <= 9;i++)
//	{
//		for (int j = 0;j <= 9;j++)
//		{
//			for (int m = 1;m <= 9;m++)
//			{
//				if (i * 7 * 7 + j * 7 + m == m * 9 * 9 + j * 9 + i && i*7*7+j*7+m >=100)
//				{
//					printf("%d%d%d(7)=%d%d%d(9)=%d(10)\n", i,j,m,m,j,i,i*7*7+j*7+m);
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}


/****************************************
*  File Name  : integer.c
*  Creat Data : 2015.1.24
*  Author     : ZY
*****************************************/

/*整数趣题*/
/*一个奇异的三位数*/
/*一个自然数的七进制表达式是一个三位数，而这个自然数的九进制表示也是
一个三位数，且这两个三正好相反位数的数码顺序，求这个三位数。*/

//
//#include <stdio.h>
//int main()
//{
//	int i, j, k;
//	for (i = 1;i < 7;i++)
//	{
//		for (j = 0;j < 7;j++)
//		{
//			for (k = 1;k < 7;k++)
//			{
//				if ((i * 7 * 7 + j * 7 + k) == (k * 9 * 9 + j * 9 + i))
//				{
//					printf("The special number with 3 digits is:\n");
//					printf("%d%d%d(7) = %d%d%d(9) = %d(10)\n", i, j, k, k, j, i, k * 9 * 9 + j * 9 + i);
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//

//
//
//#include<stdio.h>
//
//int main()
//{
//	char a[50] = { 0 };
//	int count = 0;
//	do
//	{
//		scanf("%c", &a[count++]);
//	} while (a[count - 2] != 'a');
//	for (int i = 0;i < count - 2;i++)
//	{
//		printf("%c", a[i]);
//	}
//
//}
//

//
//#include<stdio.h>
//
//int main()
//{
//	int a11 = 0, dd = 0;
//	int a[99] = { 0 };
//	for (int a1 = 1;a1 < 100;a1++)
//	{
//		for (int d = 0;d < 100;d++)
//		{
//			for (int i = 0;i <= 3;i++)
//			{
//				a[i] = a1 + d * i;
//			}
//			if (a[0] + a[1] + a[2] + a[3] == 26 && a[0] * a[1] * a[2] * a[3] == 880)
//			{
//				a11 = a1;
//				dd = d;
//			}
//
//		}
//	}
//	for (int i = 0;i < 21;i++)
//	{
//		a[i] = a11 + i * dd;
//		printf("%d,", a[i]);
//	}
//	printf("......\n");
//
//
//	return 0;
//}

//
//#include<stdio.h>
//
//
//
//#include<math.h>
//int WS(int x)
//{
//	for (int i = 1;i <= 999;i++)
//	{
//		if (x >= pow(10, i - 1) && x < pow(10, i))
//		{
//			return i;
//		}
//	}
//}
//
//
//
//int main()
//{
//	int flag = 0;
//
//	for (int i = 100;i < 1000000;i++)
//	{
//		int n = WS(i);
//		long sum = 0;
//		int x = i;
//		if (i % (int)pow(10, n - 1) == 0 && i / pow(10, n - 1) == 1)
//		{
//			if (flag++ != 0)
//			{
//				printf("\n");
//			}
//
//			printf("%d位自幂数有:", n);
//
//		}
//
//		for (int j = 0;j < n;j++)
//		{
//			int a = x % 10;
//			sum += pow(a, n);
//			x /= 10;
//		}
//
//		if (sum == i)
//		{
//			printf("%ld\t", sum);
//		}
//		
//	}
//
//
//	return 0;
//}


////
//#include<stdio.h>
//
//int main()
//{
//
//	//float a = 11;
//
//	//a = (a + 1 / 5) * 5 / 4;
//
//	//a = (a + 1 / 4) * 4 / 3;
//
//	//a = (a + 1 / 3) * 3 / 2;
//
//	//a = (a + 1 / 2) * 2 / 1;
//
//	for (float i = 11;i <= 999;i++)
//	{
//		float a = i;
//		for (float j = 1;j <= 4;j++)
//		{
//			a = (a / (j + 1)) * j - 1 / j;
//		}
//		if(a > 10.9999 && a< 11.0001)
//			printf("There are %d fishes at first.\n", (int)a);
//
//	}
//
//
//
//
//	return 0;
//}

//
//#include<stdio.h>
//
//int main()
//{
//
//	long profit = 0;
//	float reward = 0;
//	printf("请输入利润：");
//	scanf("%ld", &profit);
//	int a = profit / 100000;
//	long x = profit;
//	switch (a)
//	{
//	default:
//	case 10:
//		reward += (x - 1000000) * 0.01;
//		x = x - (x - 1000000);
//	case 9:
//	case 8:
//	case 7:
//	case 6:
//		reward += (x - 600000) * 0.015;
//		x = x - (x - 600000);
//	case 5:
//	case 4:
//		reward += (x - 400000) * 0.03;
//		x = x - (x - 400000);
//	case 3:
//	case 2:
//		reward += (x - 200000) * 0.05;
//		x -= (x - 200000);
//	case 1:
//		reward += (x - 100000) * 0.075;
//		x -= (x - 100000);
//	case 0:
//		reward += x * 0.1;
//	}
//	printf("奖金是%10.2f",reward);
//
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int birth = 0;
//	int year = 0;
//	printf("Input your birth year:");
//
//	scanf("%d", &birth);
//	printf("Input this year:");
//
//	scanf("%d", &year);
//
//	int sy = year - birth;
//	unsigned long int bit = 0;
//	int day = 0;
//	for (int i = birth;i < year;i++)
//	{
//		if (i % 4 == 0 && i % 100 != 0 || i % 100 == 0 && i % 400 == 0)
//		{
//			day++;
//		}
//	}
//	bit = (sy * 365 + day) * 24 * 60 * 75;
//	printf("The heart beats in your life: %lu", bit);
//
//
//	return 0;
//}

//
//
//#include<stdio.h>
//#include<math.h>
//int WS(int x)
//{
//	for (int i = 1;i <= 999;i++)
//	{
//		if (x >= pow(10, i - 1) && x < pow(10, i))
//		{
//			return i;
//		}
//	}
//}
//
//int main()
//{
//
//	for (int i = 1;i <= 99;i++)
//	{
//		int n = WS(i);
//		int a = i * i % (int)pow(10, n);
//		if (a == i)
//		{
//			printf("m=%3d\t\tm*m=%6d\n", i, i * i);
//		}
//	}
//
//
//
//	return 0;
//}

//#include<stdio.h>
//#include<math.h>
//
//int main()
//{
//	int i = 0;
//	int count = 0;
//	for (i = 1;count <3;i++)
//	{
//		if (i + 100 == sqrt(i + 100) * sqrt(i + 100))
//			if (i + 100 + 168 == sqrt(i + 100 + 168) * sqrt(i + 100 + 168))
//			{
//				printf("%d\n", i);
//				count++;
//			}
//	}
//
//	return 0;
//}

//
//#include<stdio.h>
//
//int main()
//{
//	int n = 0;
//	printf("\nInput an integer here please:\n");
//	scanf("%d", &n);
//	int i = 0;
//	int find = 1;
//	for (i = 1;find;i += 2)
//	{
//		int flag = 1;
//		int a = n*n*n;
//		int count = 0;
//		for (int j = i;flag;j+=2)
//		{
//			a -= j;
//			count++;
//			
//			if (a == 0 && count == n)
//			{
//				flag = 0;
//				find = 0;
//			}
//			else if (a < 0)
//			{
//				flag = 0;
//			}
//		}
//	}
//	i -= 2;
//	printf("%d*%d*%d=", n, n, n);
//	for (int x = 1;x <= n;x++)
//	{
//		if (x != n)
//		{
//			printf("%d+", i);
//			i += 2;
//		}
//		else printf("%d", i);
//	}
//
//
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	long n = 555555;
//	int max = 0;
//	printf("Please input number:");
//	scanf("%ld", &n);
//
//	for (int i = 999;i >= 100;i--)
//	{
//		if (n % i == 0)
//		{
//			max = i;
//			break;
//		}
//	}
//	if(max)
//	printf("The max factor with 3 digits in %ld is: %d.\n", n,max);
//
//	return 0;
//}


//#include<stdio.h>
//
//#include<math.h>
//int WS(int x)
//{
//	for (int i = 1;i <= 999;i++)
//	{
//		if (x >= pow(10, i - 1) && x < pow(10, i))
//		{
//			return i;
//		}
//		else if (x == 0)
//		{
//			return 1;
//		}
//	}
//}
//
//int main()
//{
//
//	int m = 0;
//	scanf("%d", &m);
//	printf("n=%d", WS(m));
//
//
//	return 0;
//}

//
//#include<stdio.h>
//
//#include<math.h>
//int WS(int x)
//{
//	for (int i = 1;i <= 999;i++)
//	{
//		if (x >= pow(10, i - 1) && x < pow(10, i))
//		{
//			return i;
//		}
//		else if (x == 0)
//		{
//			return 1;
//		}
//	}
//}
//
//int main()
//{
//	printf("Input the number:");
//	int n = 0;
//	scanf("%d", &n);
//	int a = n;
//	for (int i = 0;i < WS(n);i++)
//	{
//		printf("%d", a % 10);
//		a /= 10;
//	}
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	int co = 0;
//	printf("There are following possible result:\n");
//	for (int i = 1;i < 23;i++)
//	{
//		for (int j = i + 1;j < 23 - i; j++)
//		{
//			for (int m = j + 1;m < 23 - i - j;m++)
//			{
//				for (int n = m + 1;n < 23 - i - j - m;n++)
//				{
//					for (int x = n + 1;x <= 23 - i - j - m - n;x++)
//					{
//						if (i + j + m + n + x == 23)
//						{
//							int count = 0;
//							for (int O = 1;O <= 23;O++)
//							{
//								int find = 1;
//								for (int x1 = 0;x1 < 2 && find ;x1++)
//								{
//									for (int x2 = 0;x2 < 2 && find ;x2++)
//									{
//										for (int x3 = 0;x3 < 2 && find ;x3++)
//										{
//											for (int x4 = 0;x4 < 2 && find;x4++)
//											{
//												for (int x5 = 0;x5 < 2 && find;x5++)
//												{
//													if (O == x1 * i + x2 * j + x3 * m + x4 * n + x5 * x)
//													{
//														find = 0;
//														count++;
//													}
//												}
//											}
//										}
//									}
//								}
//							}
//							if (count == 23)
//							{
//								printf("[%d]:%d,%d,%d,%d,%d\n", ++co,i, j, m, n, x);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}

//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	for (int i = 0;i <= 9;i++) printf("%7d",i);
//	printf("\n");
//	for (int i = 0;i <= 9;i++)
//	{
//		printf("%d", i);
//		for (int j = i*10;j <= i*10+9;j++)
//		{
//			printf("%7.3f", sqrt(j));
//		}
//		printf("\n");
//		
//	}
//}

//
//
//#include<stdio.h>
//
//int main()
//{
//
//	for (int x = 6;;x++)
//	{
//		int a = x;
//		
//		if (a % 5 == 1)
//			{
//			a = a/5*4;
//			if (a % 5 == 1)
//			{
//				a = a / 5 * 4;
//
//					if (a % 5 == 1)
//					{
//						a = a / 5 * 4;
//
//						if (a % 5 == 1)
//						{
//							a = a / 5 * 4;
//
//							if (a%5 == 1)
//							{
//								printf("y=%d\n", x);
//								break;
//							}
//						}
//					}
//			}
//		}
//		
//	}
//
//
//
//	return 0;
//}

//
//
//#include <stdio.h>
//main()
//{
//	int i, j, k;
//	for (i = 0;i <= 3;i++)
//		for (j = 1;j <= 5;j++)
//		{
//			k = 8 - i - j;
//			if (k >= 0 && k <= 6)
//				printf("hong=%d\t,bai=%d\t,hei=%d\t\n", i, j, k);
//		}
//}
//


//#include<stdio.h>
//
//int main()
//{
//	int max = 0;
//	int a = 0;
//	for (int i = 1;i <= 10;i++)
//	{
//		printf("input the number!\n");
//		scanf("%d", &a);
//		if (max < a)
//		{
//			max = a;
//		}
//	}
//	printf("max integer is %d!\n", max);
//
//	return 0;
//}
//
//#include<stdio.h>
//
//int main()
//{
//	int n = 0;
//	printf("Input data is:");
//	scanf("%d", &n);
//	if (n < 0) n = -n;
//	int sum = 0;
//	for (int i = 1;i <= 4;i++)
//	{
//		sum += n % 10;
//		n /= 10;
//	}
//	printf("The sum of the total bit is %d\n", sum);
//
//
//
//	return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	for (int i = 1000;i <= 9999;i++)
//	{
//		int a = i % 10;
//		int b = i / 10 % 10;
//		int c = i / 100 % 10;
//		int d = i / 1000;
//		int x = 1000 * a + 100 * b + 10 * c + d;
//		if (i * 9 == x)
//		{
//			printf("The number satisfied states condition is : %d\n", i);
//			break;
//		}
//
//	}
//
//
//	return 0;
//}

//
//
//#include<stdio.h>
//
//int main()
//{
//	for (int i =1 ;i <= 4;i++)
//	{
//		for (int j = 5;j <= 9;j++)
//		{
//			for (int m = 0;m <= 4;m++)
//			{
//				for (int n = 1;n <= 4;n++)
//				{
//					for (int x = 0;x <= 4;x++)
//					{
//						for (int y = 5;y <= 9;y++)
//						{
//							for (int z = 1;z <= 4;z++) //7 + 12+16z  e h
//							{
//								for (int a = 0;a <= 4;a++) ////8+13+17 a+f+x2
//								{
//									for (int b = 0;b <= 4;b++) //9+14
//									{
//										for (int c = 0;c <= 4;c++) //10
//										{
//											for (int d = 1;d <= 4;d++) //AAZZ
//											{
//												for (int e = 0;e <= 4;e++)
//												{
//													for (int f = 5;f <= 9;f++)
//													{
//														for (int g = 5;g <= 9;g++) //14
//														{
//															for (int h = 5;h <= 9;h++) //ZAA
//															{
//																for (int x1 = 0;x1 <= 4;x1++)
//																{
//																	for (int x2 = 0;x2 <= 4;x2++)
//																	{
//																		for (int x3 = 5;x3 <= 9;x3++)
//																		{
//																			for (int x4 = 0;x4 <= 4;x4++)
//																			{
//																				for (int x5 = 5;x5 <= 9;x5++)
//																				{
//																					for (int x6 = 0;x6 <= 4;x6++)
//																					{
//																						for (int x7 = 0;x7 <= 4;x7++)
//																						{
//																							if ((100 * i + 10 * j + m) * y == 1000*z+100*a+10*b+c)
//																							{
//																								if ((100 * i + 10 * j + m) * x == 1000 * d + 100 * e + 10 * f + g)
//																								{
//																									if ((100 * i + 10 * j + m) * n == 100 * h + 10 * x1 + x2)
//																									{
//																										if (c == x7)
//																										{
//																											if ((g + b) % 10 == x6)
//																											{
//																												if ((a + f + x2) % 10 == x5)
//																												{
//																													if ((z + e + x1) % 10 == x4)
//																													{
//																														if ((d + h) % 10 == x3)
//																														{
//																															printf("\n   %ld\n", (long)(100 * i + 10 * j + m));
//																															printf("*  %ld\n" "--------------\n", (long)(100 * n + 10 * x + y));
//																															printf("  %ld\n %ld\n %ld\n", (long)(1000 * z + 100 * a + 10 * b + c), (long)(1000 * d + 100 * e + 10 * f + g), (long)(100 * h + 10 * x1 + x2));
//																															printf(" %ld\n", (long)(10000 * x3 + 1000 * x4 + 100 * x5 + 10 * x6 + x7));
//																														}
//																													}
//																												}
//																											}
//																										}
//																									}
//																								}
//																							}
//																						}
//																					}
//																				}
//																			}
//																		}
//																	}
//																}
//															}
//														}
//													}
//												}
//											}
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//
//
//	return 0;
//}


//
//#include<stdio.h>
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
//int C(int m, int n)   //JS
//{
//	return JS(m) / (JS(m-n) * JS(n));
//}
//
//int main()
//{
//	int m = 0, k = 1;
//	while (m < k || m<0 || k<0)
//	{
//		printf("Input m,k (m>=k>0):");
//		scanf("%d,%d", &m, &k);
//	}
//	printf("p = %.0f\n", (float)(C(m, k)));
//
//
//	return 0;
//}
//
//#include<stdio.h>
//
//double myPOW(int x, int n)
//{
//	int a = x;
//	for (int i = 1;i < n;i++)
//	{
//		x *= a;
//	}
//	return x;
//
//}
//
//int main()
//{
//	printf("Enter x and n\n");
//	int x = 0, n = 0;
//	scanf("%d%d", &x, &n);
//	printf("mypow(%d,%d) = %.2f\n", x, n, myPOW(x, n));
//
//
//
//	return 0;
//}

//#include <stdio.h>
//
//unsigned long fun(int n);
//
//main()
//{
//    int n;
//    unsigned long  sum = 0;
//    printf("Input n:");
//    scanf("%d", &n);
//    while (n)
//    {
//        sum += fun(n--);
//    }
//    printf("The sum is :%u", sum);
//}
//
//unsigned long fun(int n)
//{
//    unsigned long  m_sum = 0;
//    m_sum += n;
//    return m_sum;
//}
//
//#include<stdio.h>
//
//
//long fac(int n)
//{
//	long sum = 1;
//	for (int x = 1;x <= n;x++)
//	{
//		sum *= x;
//	}
//	return sum;
//}
//
//int main()
//{
//	printf("Input an integer:\n");
//	int n = 0;
//	scanf("%d", &n);
//	if (n >= 0)
//	{
//		printf("%d! = %ld\n", n, fac(n));
//	}
//	else
//	{
//		printf("Input Error!\n");
//	}
//
//}

//
//#include<stdio.h>
//
//int Gcd(int a, int b)
//{
//	int max0 = a > b ? a : b;
//	int max = 0;
//	for (int i = 1;i <= max0;i++)
//	{
//		if (a % i == 0 && b % i == 0)
//		{
//			max = i;
//		}
//	}
//	return max;
//
//}
//
//int main()
//{
//	int a = 0, b = 0;
//	printf("Input a,b:");
//	scanf("%d,%d", &a, &b);
//	if (a <= 0 || b <= 0)
//	{
//		printf("Input error!\n");
//	}
//	else
//	{
//		printf("Gcd=%d\n", Gcd(a, b));
//	}
//
//
//	return 0;
//}

//#include <stdio.h>
//int MinCommonMultiple(int a, int b);
//
//main()
//{
//	int a, b, x;
//	printf("Input a,b:");
//	scanf("%d,%d", &a, &b);
//	x = MinCommonMultiple(a, b);
//	printf("MinCommonMultiple = %d\n", x);
//}
//int MinCommonMultiple(int a, int b)
//{
//	int i;
//
//	for (i = 1; i <= a * b; i++)
//	{
//		if (i % a == 0 && i % b == 0)
//			return i;
//	}
//}

//
//#include<stdio.h>
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//int main()
//{
//	for (int i = 200;i <= 300;i++)
//	{
//		if (Z(i))
//		{
//			printf("%d\n",i);
//		}
//	}
//	return 0;
//}


//#include<stdio.h>
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
//int main()
//{
//	int sum = 0;
//	int n = 0;
//	printf("Input n:\n");
//	scanf("%d", &n);
//	for (int i = 1;i <= 2*n-1;i+=2)
//	{
//		sum += JS(i);
//	}
//	printf("sum=%ld\n",sum);
//	return 0;
//}
//
//#include<stdio.h>
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//
//int main()
//{
//	int n = 0;
//	int sum = 0;
//	printf("Input n:");
//	scanf("%d", &n);
//	for (int i = 1;i <= n;i++)
//	{
//		if (Z(i))
//		{
//			sum += i;
//		}
//	}
//	printf("sum = %d\n", sum);
//
//	return 0;
//}

//
//#include<stdio.h>
//
//int GCD(int a, int b)
//{
//	int max0 = a > b ? a : b;
//	int max = 0;
//	for (int i = 1;i <= max0;i++)
//	{
//		if (a % i == 0 && b % i == 0)
//		{
//			max = i;
//		}
//	}
//	return max;
//
//}
//
//int main()
//{
//	printf("Input a,b:\n");
//	int a = 0, b = 0;
//	scanf("%d,%d", &a, &b);
//	if (a <= 0 || b <= 0)
//	{
//		printf("Input number should be positive!\n");
//	}
//	else
//	{
//		printf("Greatest Common Divisor of %d and %d is %d\n", a, b, GCD(a, b));
//	}
//
//
//	return 0;
//}


//
//#include<stdio.h>
//
//double JS(int n)
//{
//	double sum = 1;
//	for (int x = 1;x <= n;x++)
//	{
//		sum *= x;
//	}
//	return sum;
//}
//
//double C(int m, int n)   //JS
//{
//	return JS(m) / (JS(m - n) * JS(n));
//}
//
//
//int main()
//{
//	printf("请输入m,n的值( m>n )：\n");
//	int m = 0, n = 0;
//	scanf("%d %d", &m, &n);
//	double x = C(m, n);
//	printf("n项之和为：%lf\n", x);
//
//	return 0;
//}


//#include<stdio.h>
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
//int main()
//{
//	int n = 0;
//	printf("Input n(n>0):");
//	scanf("%d", &n);
//	int sum = 0;
//	for (int i = 1;i <= n;i++)
//	{
//		sum += JS(i);
//	}
//	printf("sum = %d\n",sum);
//
//	return 0;
//}

//#include<stdio.h>
//
//int GCD(int a, int b)
//{
//	int max0 = a > b ? a : b;
//	int max = 0;
//	for (int i = 1;i <= max0;i++)
//	{
//		if (a % i == 0 && b % i == 0)
//		{
//			max = i;
//		}
//	}
//	return max;
//
//}
//
//int main()
//{
//	printf("Input a,b:\n");
//	int a = 0, b = 0;
//	scanf("%d,%d", &a, &b);
//	if (a <= 0 || b <= 0)
//	{
//		printf("Input error!\n");
//	}
//	else
//	{
//		printf("Gcd=%d\n", GCD(a, b));
//	}
//
//	return 0;
//}

//
//#include <stdio.h>
//
//int MinCommonMultiple(int a, int b);
//
//main()
//{
//    int a, b, x;
//
//    printf("Input a,b:");
//    scanf("%d,%d", &a, &b);
//
//    x = MinCommonMultiple(a,b);
//    printf("MinCommonMultiple = %d\n", x);
//}
//
//int MinCommonMultiple(int a, int b)
//{
//    int i;
//
//    for (i = 1; i <= a * b; i++)
//    {
//        if (i %a == 0 && i %b == 0)
//            return i;
//    }
//    return 0;
//}

//
//#include<stdio.h>
//
//int main()
//{
//	printf("Input two FENSHU :\n");
//	int a = 0, b = 0;
//	int c = 0, d = 0;
//	scanf("%d%d,%d%d", &a, &b, &c, &d);
//	float x = (float)a / b;
//	float y = (float)c / d;
//	if (x > y)
//	{
//		printf("%d/%d>%d/%d\n", a, b,c,d);
//	}
//	else if (x < y)
//	{
//		printf("%d/%d<%d/%d\n", a, b,c,d);
//	}
//	else
//	{
//		printf("%d/%d=%d/%d\n",a,b,c,d);
//	}
//
//	return 0;
//}
//
//#include<stdio.h>
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
//
//{
//	int m = 0;
//	printf("Input m:\n");
//	scanf("%d", &m);
//	if (m == SumPrime(m))
//	{
//		printf("%d is a perfect number\n", m);
//	}
//	else
//	{
//		printf("%d is not a perfect number\n",m);
//	}
//
//
//	return 0;
//}

//
//#include<stdio.h>
//
//int GCD(int a, int b)
//{
//	int max0 = a > b ? a : b;
//	int max = 0;
//	for (int i = 1;i <= max0;i++)
//	{
//		if (a % i == 0 && b % i == 0)
//		{
//			max = i;
//		}
//	}
//	return max;
//}
//
//int main()
//{
//	int a = 0, b = 0;
//	scanf("%d,%d", &a, &b);
//	if (a <= 0 || b <= 0)
//	{
//		printf("Input Error!\n");
//	}
//	else
//	{
//		printf("%d\n", GCD(a, b));
//	}
//
//}

//#include<stdio.h>
//#include <math.h>
//int isprime(int m);
//
//main()
//{
//    int n, flag;
//    printf("Input n:");
//    scanf("%d", &n);
//    flag = isprime(n);
//    if (flag)
//        printf("Yes!\n");
//    else
//        printf("No!\n");
//}
///* 函数名：  isprime
//函数功能：判断m是否为素数
//入口参数：整型数m
//返回值：  返回值为1时，表示m是素数；
//返回值为0时，表示m不是素数 */
//
//int isprime(int m)
//{
//    int i;
//    if (m == 1)
//        return 0;  /*1不是素数，所以返回0值*/
//    for (i = 2; i <= sqrt(m); i++)
//    {
//        if (m % i == 0)  return 0;
//    }
//    return 1;
//}

//#include<stdio.h>
//#include<math.h>
//
//int main()
//{
//	int a = 2;
//	int b = -3;
//	for (int i = 0;i <= 5;i++)
//	{
//		printf("2 power %d is %d, -3 power %d is %d\n", i,(int)pow(a, i),i, (int)pow(b, i));
//	}
//
//	return 0;
//}


//#include <stdio.h>
//
//fun(float a, float b);
//
//main()
//{
//    fun(1,1);
//}
//
//fun(float a, float b)
//{
//    float t;
//    scanf("%f%f", &a, &b);
//    if (a < b)
//    {
//        t = a;
//        a = b;
//        b = t;
//    }
//    printf("%5.2f,%5.2f\n", a, b);
//}


//#include<stdio.h>
//
//float SUM(int n)
//{
//	float sum = 0;
//	int fz = 2;
//	int fm = 1;
//	for (int i = 1;i <= n;i++)
//	{
//		sum += (float)fz / fm;
//		int c = fz;
//		fz = fz + fm;
//		fm = c;
//	}
//	return sum;
//}
//
//int main()
//{
//	printf("请输入n的值：\n");
//	int n = 0;
//	scanf("%d", &n);
//	double sum = SUM(n);
//
//	printf("n项之和为：%lf\n", sum);
//
//	return 0;
//}
//
//#include<stdio.h>
//#include<math.h>
//
//
//int Z(int n)
//{
//	for (int i = 2;i <= sqrt(n) || n == 1;i++)
//	{
//		if (n % i == 0 || n == 1) return 0;
//	}
//	return 1; //素数返回1
//}
//
//int main()
//{
//	int n = 0;
//	printf("Please input n:");
//
//	scanf("%d", &n);
//	for (int i = n + 1;;i++)
//	{
//		if (Z(i))
//		{
//			printf("%d\n",i);
//			break;
//		}
//	}
//
//	return 0;
//}
//
//#include <stdio.h> 
//#define END  -1
//
//long Factorial(int x);
//
//main()
//{
//    int x;
//    while (1)
//    {
//        printf("input x:");
//        scanf("%d", &x);
//        if (x <= END)
//            break;
//        else
//            printf("%d! = %d\n", x, Factorial(x));
//    }
//}
//
//long Factorial(int x)
//{
//    int i;
//    int result = 1;
//
//    for (i = 1; i <= x; i++)
//        result *= i;
//    return result;
//}
//
//#include<stdio.h>
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
//long C(int m, int n)   //JS
//{
//	return JS(m) / (JS(m - n) * JS(n));
//}
//
//int main()
//{
//	int m = 0, k = 0;
//	do
//	{
//		printf("Input m,k (m>=k>0):");
//		scanf("%d,%d", &m, &k);
//
//	} while (m < 0 || k < 0 || m < k);
//	
//	printf("The combination is %ld\n", C(m, k));
//
//	return 0;
//}



//#include<stdio.h>
//
//int main()
//{
//	int n = 9;
//	float* pF = (float*) & n;
//	float k = 9.0;
//
//	printf("%d\n", *pF);
//
//	printf("%d\n", k);
//
//	printf("%f\n",*pF);
//
//
//	return 0;
//}


//#include<stdio.h>
//
//int main()
//{
//    int nums[10] = { 0 };
//    int target = 0;
//    int find = 0;
//    for (int i = 0;!find;i++)
//    {
//        scanf("%d", &nums[i]);
//        if (getchar() == ']')
//        {
//            find = 1;
//        }
//    }
//    scanf("%d", &target);
//    int i, j;
//    for (i = 0;find;i++)
//    {
//        for (j = 0;find;j++)
//        {
//            if (nums[i] + nums[j] == target)
//            {
//                find = 0;
//            }
//        }
//    }
//
//    printf("[%d,%d]", i, j);
//
//    return 0;
//}

//#include<stdio.h>
//
//int main()
//{
//	char a = 'A';
//	a = a + 32;
//	printf("%c", a);
//
//	return 0;

#include<stdio.h>

void ini_yang(int(*arr)[15], int n)
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

void print_yang(int(*arr)[15], int n)
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

int main()
{
	int a[15][15] = { 0 };
	ini_yang(a, 5);

	print_yang(a, 5);

	return 0;
}