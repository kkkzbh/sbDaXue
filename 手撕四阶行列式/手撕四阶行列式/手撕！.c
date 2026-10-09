#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>


int main()
{
	int a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3, a4, b4, c4, d4;
	int chiken = 1,ji = 0;
	scanf("%d %d %d %d", a1, b1, c1, d1);
	scanf("%d %d %d %d", a2, b2, c2, d2);
	scanf("%d %d %d %d", a3, b3, c3, d3);
	scanf("%d %d %d %d", a4, b4, c4, d4);

	ji = a1 * b2 * c3 * d4 + b1 * c2 * d3 * a4 + c1 * d2 * a3 * b3 + d1 * a2 * b3 * c4;
	chiken = a1*d2*c3*b4+b1

	
	//int a[4][4] = { 0 };

	//for (int i = 0;i < 4;i++)
	//{
	//	for (int j = 0;j < 4;j++)
	//	{
	//		scanf("%d", &a[i][j]);
	//	}
	//}

	//for (int i = 0;i < 4;i++)
	//{
	//	for (int j = 0;j < 4;j++)
	//	{
	//		chiken *= a[i][j];
	//		i++;
	//		if (j = 3) j = 0;
	//		if (i = 3) i = 0;
	//	}
	//}



	return 0;
}