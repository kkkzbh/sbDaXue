#define _CRT_SECURE_NO_WARNINGS


//
//#include<stdio.h>
//
//#define ROW 4
//#define COW 3
//
//void LineMax(int(*x)[COW]);
//
//
//int main()
//{
//	printf("Input the 4*3 array:\n");
//	int a[ROW][COW];
//	for (int i = 0;i < ROW;i++)
//	{
//		for (int j = 0;j < COW;j++)
//		{
//			scanf("%d", &a[i][j]);
//		}
//	}
//	LineMax(a);
//}
//
//void LineMax(int(*x)[COW])
//{
//	for (int i = 0; i < ROW; i++)
//	{
//		int max = x[i][0];
//		for (int j = 1; j < COW; j++)
//		{
//			if (max < x[i][j])
//			{
//				max = x[i][j];
//			}
//		}
//		printf("The max value in line %d is %d\n", i,max);
//	}
//
//}

//
//#include<stdio.h>
//
//#define MAX 100
//
//int main()
//{
//	printf("Input n,m:");
//	int n, m;
//	scanf("%d %d", &n, &m);
//	int a[MAX] = { 0 };
//	for (int i = 0; i < n;i++)
//	{
//		scanf("%d", &a[i]);
//	}
//	int b[MAX] = { 0 };
//	for (int i = 0;i < n;i++)
//	{
//		b[(i+m)%n] = a[i];
//	}
//	printf("After moved:\n");
//	for (int i = 0; i < n;i++)
//	{
//		printf("%5d", b[i]);
//	}
//
//	return 0;
//}

//
#include<stdio.h>


#define MAX 100



void Separate(int a[], int n);

int Is(int x)
{
	if (x % 2 == 0)
		return 1;
	else
		return 2;
}


int main()
{
	printf("Input numbers:");
	int n = 0;
	scanf("%d",&n);
	int a[MAX] = { 0 };
	for (int i = 0;i < n;i++)
	{
		scanf("%d", &a[i]);
	}
	Separate(a, n);
	return 0;
}


void Separate(int a[], int n)
{
	for (int i = 0;i < n;i++)
	{
		if(Is(a[i]) == 2)
			printf("%d ",a[i]);
	}
	printf("\n");
	for (int j = 0;j < n;j++)
	{
		if (Is(a[j]) == 1)
			printf("%d ", a[j]);
	}
	printf("\n");
}


//
//#include<stdio.h>
//#include<string.h>
//#define MAX 100
//
//
//void  Squeeze(char s[], char c);
//
//int main()
//{
//	printf("Input a string:\n");
//	char str[MAX] =  "#############################################";
//	gets(str);
//
//    printf("Input a character:\n");
//	char x = getchar();
//	Squeeze(str, x);
//
//	printf("Results:%s\n", str);
//
//	return 0;
//}
//
//void  Squeeze(char s[], char c)
//{
//	char* tmp = s;
//	while (*s != '\0')
//	{
//		if (*s == c)
//		{
//			strcpy(s, s + 1);
//		}
//		s++;
//	}
//}


#include<stdio.h>

max(double x, double y)
{
	return x;
}

min(double x, double y)
{
	return x;
}

void change(double x)
{
	x += 1.0;
}

int main()
{
	double x = 5;
	double aaa = 3.3;
	double bbb = 2.2;
	x = max(aaa, bbb);

	printf("%f\n", x);

	x = min(aaa, bbb);
	printf("%lf\n", x);

	change(max(aaa,bbb));
	printf("%lf\n", x);

	return 0;
}