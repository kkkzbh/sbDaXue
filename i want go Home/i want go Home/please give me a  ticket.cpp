#define _CRT_SECURE_NO_WARNINGS
//
// #include<stdio.h>
//int main()
//{
//	printf("三阶行列式真几把难算\n");
//	printf("输入系数以及常数，给他手撕了\n");
//	double a, b, c, d, e, f, g, h, i, j, k, l, m, n, x, y, z;
//	double D;
//	double D1, D2, D3;
//	double x1, x2, x3;
//	printf("您想算根还是算解？\n");
//	printf("输入1算根 输入2只选系数D 输入3计算逆序>:");
//	int A = 0;
//	scanf(" %d", &A);
//	if (A == 1)
//	{
//		printf("请按行列式格式输入数据\n");
//		printf("如 1 2 3 4然后按下回车\n");
//		scanf(" %lf %lf %lf %lf", &a, &b, &c, &x);
//		scanf(" %lf %lf %lf %lf", &d, &e, &f, &y);
//		scanf(" %lf %lf %lf %lf", &g, &h, &i, &z);
//		D = a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
//		D1 = x * e * i + b * f * z + c * y * h - c * e * z - b * y * i - x * f * h;
//		D2 = a * y * i + x * f * g + c * d * z - c * y * g - x * d * i - a * f * z;
//		D3 = a * e * z + b * y * g + x * d * h - x * e * g - b * d * z - a * y * h;
//		x1 = D1 / D; x2 = D2 / D; x3 = D3 / D;
//		printf("x1=%lf x2=%lf x3=%lf", x1, x2, x3);
//		printf("\n可算踏马给他手撕了！\n");
//	}
//
//	if (A == 2)
//	{
//		scanf(" %lf %lf %lf", &a, &b, &c);
//		scanf(" %lf %lf %lf", &d, &e, &f);
//		scanf(" %lf %lf %lf", &g, &h, &i);
//		double X;
//		X = a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
//		printf("D=%lf", X);
//		printf("\n手撕了就是爽！\n");
//	}
//	if (A == 3)
//	{
//
//		;
//
//
//	}
//
//		return 0;
//}

////////////////////////////////////////////////////////////////////////////////
//
//
//#include<stdio.h>
//#include<math.h>
//
//
//
//int main()
//{


    //int a = 0;
    //int b = 0;
    //printf("input data is:");
    //scanf("%d", &a);
    //fabs(a);
    //int x, y, z;
    //x = a / 100; y = (a / 10) % 10; z = a % 10;
    //b = x + y + z;
    //printf("The sum of the total bit is %d\n", b);




    //int year = 0, month = 0, day = 0;

    //printf("Enter a date(year month day):\n");
    //scanf("%d%d%d", &year, &month, &day);
    //printf("You entered the date: %02d/%02d/%d", month, day, year);













    //int i;
    //char ch;
    //float f;
    //printf("Please input:\n");
    //scanf("%d %c%f", &i, ch, &f);
    //printf("The input integer is : %d \nThe input character is : %c\n", i, ch);
    //printf("The input float is : %f", f);


    //return 0;


















//
//
//
//
//
//
//	return 0;
//}
//
//












///////////////////////////////////////////////////////////////////////////




//
//#include<stdio.h>
//
//
//int Fib(int n)
//{
//    if (n <= 2)
//        return 1;
//    else
//        return Fib(n - 1) + Fib(n - 2);
//}
//
//int main()
//{
//    int n = 0;
//    printf(">:");
//    scanf("%d", &n);
//    int a =Fib(n);
//    printf("%d\n", a);
//
//    return 0;
//}
//









//
//
//#include<stdio.h>
//
//
//
//
//
//int main()
//{
//    double F = 0, t = 0;
//
//    while (F <= 300)
//    {
//        t = 5.0 / 9.0 * (F - 32);
//
//        printf("%4.0f%10.1f\n", F, t);
//        F += 20;
//
//    }
//    return 0;
//}

//
//
//#include<stdio.h>
//
//
//
//int main()
//{
//    char a, b;
//    scanf("%c", &a);
//    b = a - 32;
//    printf("%c,%d\n", b, b);
//
//    return 0;
//}



//
//
//#include<stdio.h>
//
//
//
//
//int main()
//{
//    double T, t;
//    printf("Please input fahr: ");
//    scanf("%lf", &t);
//
//    T = (t * 9.0 / 5.0) + 32.0;
//    printf("The cels is: %.2f", T);
//
//    return 0;
//}
//







//#include<stdio.h>
//
//
//
//
//int main()
//{
//    double a, b;
//    scanf("%lf,%lf", &a, &b);
//    double ave = (a + b / 2.0);
//
//    printf("The average is :%f", ave);
//
//    return 0;
//}
//
//

//
//#include<stdio.h>
//
//
//
//int main()
//{
//
//    char a = 0;
//    printf("Press a key and then press Enter:");
//    scanf("%c", &a);
//
//    if (a >= 'A' && a <= 'Z')
//    {
//        char b = a + 32;
//        printf("%c, %d\n", b, b);
//    }
//
//    else if (a >= 'a' && a <= 'Z')
//    {
//        char c = a - 32;
//        printf("%c, %d\n", c, c);
//    }
//
//    else
//    {
//        printf("%c,%d", a, a);
//    }
//
//    return 0;
//}
//
//


//
//
//#include<stdio.h>
//#include<math.h>
//#define N 10000000
//long long sum = 0;
//int a[N + 1] = { 0 };
//
//long long arr_p(int n)
//{
//    int i = 0;
// 
//    
//    int m = 0;
//    for (m = 2; m <= n;m++)
//    {
//        a[m] = m;
//    }
//
//    for (i = 2;i <= sqrt(n);i++)
//    {
//        int x = 0;
//        for (x = i + 1;x <= n;x++)
//        {
//            if (a[i] != 0 && a[x] != 0 && a[x] % a[i] == 0)
//            {
//                a[x] = 0;
//            }
//
//        }
//    }
//     m = 0;
//    for (m = 2;m <= n;m++)
//    {
//        if (a[m] != 0)
//        {
//            printf("%d\n", a[m]);
//            sum += a[m];
//        }
//    }
//    return sum;
//}
//
//
//
//int main()
//{
//
//    printf(":>");
//    int n = 0;
//    scanf("%d", &n);
//    int sum = arr_p(n);
//    printf("%lld\n", sum);
//
//
//    return 0;
//}



//#include<stdio.h>
//#include<stdlib.h>
//
//
//
//void priYH(int a[][20],int n)
//{
//    for (int i = 0;i <= n; i++)
//    {
//        for (int j = 0;j <= i;j++)
//        {
//            printf("%-4d", a[i][j]);
//        }
//        printf("\n");
//    }
//}
//
//void YHSJ(int n)
//{
//    int a[20][20] = { 0 };
//    int i = 0;
//    for (i = 0;i <= n;i++)
//    {
//        int j = 0;
//        for (j = 0;j <= i;j++)
//        {
//            if (j == 0 || j == i)
//                a[i][j] = 1;
//            else
//                a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
//            //printf("%-8d", a[i][j]);
//        }
//        //printf("\n");
//    }
//    priYH(a,n);
//
//}
//
//
//
//
//int main()
//{
//    int n = 0;
//    printf("显示几行？(n<=20) :>");
//    scanf("%d", &n);
//
//    system("cls");
//
//    YHSJ(n);
//    return 0;
//}



//#include<stdio.h>
//#include<math.h>
//
//
//
//
//int main()
//{
//
//    float x = 0;
//    printf("Please input x:\n");
//    scanf("%f", &x);
//
//    if (x < 0)
//    {
//        float y1 = 3 * x - 1;
//        printf("y = %.2f\n", y1);
//    }
//
//    else if (x >= 10)
//    {
//        printf("y = %.2f\n", x);
//    }
//    else
//    {
//        float y2 = exp(x);
//        printf("y = %.2f\n", y2);
//    }
//
//    return 0;
//}

////////////////////////////////////////////////////////////////////////////////////////////

//#include<stdio.h>


//int main()
//{
//
//    int a = 0;
//    printf("输入年份:");
//    scanf("%d", &a);
//    if ((a % 400 == 0) || (a % 4 == 0 && a % 100 != 0))
//    {
//        printf("%d是闰年!\n", a);
//    }
//    else
//    {
//        printf("%d不是闰年!\n", a);
//    }
//
//
//    return 0;
//}

///////////////////////////////////////////////////////////////////////////////////////


//#include<stdio.h>
//int main()
//{
//
//    int a = 0, b = 0;
//    printf("请输入两个整数：");
//    scanf("%d%d", &a, &b);
//
//
//    int c = a / b;
//    int d = a % b;
//    printf("%13d Remainder = %d\n", c, d);
//    printf("       ------\n");
//    printf("%5d ) %5d", b, a);
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
//    float x, y, z;
//
//    printf("请输入三个单精度数：");
//    scanf("%f%f%f", &x, &y, &z);
//    float sum = x + y + z; float ave = (sum / 3);
//
//    printf("三个数的和为%.3f，均值为%.3f", sum, ave);
//
//
//    return 0;
//}





//#include<stdio.h>
//
//
//int main()
//{
//    int number = 0;
//    float price = 0;
//    int year, month, date;
//    printf("Enter item number:\n");
//    scanf("%d", &number);
//    printf("Enter unit price:\n");
//    scanf("%f", &price);
//    printf("Enter purchase date (yy mm dd):\n");
//    scanf("%d%d%d", &year, &month, &date);
//    printf("Item      Unit     Purchase\n");
//
//
//    printf("%-9d$%-9.2f%02d/%02d/%02d\n", number, price, month, date, year);
//
//
//    return 0;
//}


//#include<stdio.h>
//
//
//
//
//int main()
//{
//    double T, t;
//    printf("Please input fahr: ");
//    scanf("%lf", &t);
//
//    //T = (t * 9.0 / 5.0) + 32.0;
//    T = 5 * (t - 32.0) / 9.0;
//    printf("The cels is: %.2f", T);
//
//    return 0;
//}



///////////////////////////////////////////////////////////////////////////////////////






//#include<stdio.h>
//
//
//
//
//
//int main()
//{
//    int s = 0;
//    printf("Please enter score:");
//
//    scanf("%d", &s);
//    int y = 0;
//
//    if (s <= 100 && s >= 90)
//        y = 1;
//    else if (s >= 80 && s < 90)
//        y = 2;
//    else if (s >= 70 && s < 80)
//        y = 3;
//    else if (s >= 60 && s < 70)
//        y = 4;
//    else if (s >= 0 && s < 60)
//        y = 5;
//    else
//        y = 6;
//
//
//
//    switch (y)
//    {
//
//
//
//
//
//    case 1:
//        printf("%d--A", s);
//    case 2:
//        printf("%d--B", s);
//    case 3:
//        printf("%d--C", s);
//    case 4:
//        printf("%d--D", s);
//    case 5:
//        printf("%d--E", s);
//    default:
//        printf("Input error!");
//
//
//    }
//        return 0;
//}



// 122→ 251.6



///////////////////////////////////////////////////////////////////


//#include <stdio.h>
//int MinCommonMultiple(int a, int b);
//
//int main()
//{
//    int a, b, x;
//    printf("Input a,b:");
//    scanf("%d,%d", &a, &b);
//    x = MinCommonMultiple(a, b);
//    printf("MinCommonMultiple = %d\n", x);
//
//    return 0;
//
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



//////////////////////////////////////////////////////////////////////////////////////////////





//#include<stdio.h>
//
//
//int main()
//{
//    
//    printf("Please enter h,w:\n");
//    float w = 0;
//    float h = 0;
//    float t = 0;
//
//
//    scanf("%f,%f", &h, &w);
//    
//
//    t = w / (h * h);
//
//    if (t < 18)
//        printf("Lower weight!\n");
//    else if (t >= 18 && t < 25)
//        printf("Standard weight!\n");
//    else if (t >= 25 && t < 27)
//        printf("Higher weight!\n");
//    else 
//        printf("Too fat!\n");
//
//
//    return 0;
//}



//////////////////////////////////////////////////////////////////////////////////////////





//#include<stdio.h>
//int main()
//{
//
//
//    for (int i = 0, y = sizeof(int);i > 10;i++)
//    {
//
//        ;
//
//    }
//
//
//}









































































































