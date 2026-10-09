#include"game.h"

int win = 1;


void AddBOOM(char b[HHS][LLS], int A, int B)
{

	for (int i = 0;i < BOM;++i)
	{
		int x = rand() % HH + 1;
		int y = rand() % LL + 1;
		b[x][y] = '1';
	}

}



void InitiaBOOM(char show[HHS][LLS], int A, int B,char set)
{
	for (int i = 0;i < A; ++i)
	{
		for (int j = 0; j < B; ++j)
		{
			 show[i][j] = set;
		}
	}



}

void printBOOM(char X[HHS][LLS],int x,int y)
{

	for (int i = 0;i <= x;++i)
	{
		printf("%d   ", i);
	}
	printf("\n---------------------------------------\n");
	for (int i = 1;i <= x;++i)
	{
		printf("%d | ", i);
		for (int j = 1;j <= y;++j)
		{
			printf("%c | ", X[i][j]);
		}
		printf("\n---------------------------------------\n");

	}
}


char FindBOOM(char show[HHS][LLS], char bm[HHS][LLS],int x,int y)
{
	int count = 0;
	for (int i = x - 1;i <= x + 1;++i)
	{
		for (int j = y - 1;j <= y + 1;++j)
		{
			if (bm[i][j] == '1')
			{
				++count;
			}
		}
	}
	return count + '0';
}



int PA = 0;



void Amazeing(char show[HHS][LLS], char bm[HHS][LLS], int x, int y)
{
	if (FindBOOM(show, bm, x, y) == '0')
	{
		show[x][y] = ' ';
		PA++;
		for (int i = x - 1;i <= x + 1;++i)
		{
			for (int j = y - 1;j <= y + 1;j++)
			{
				if (i >= 1 && i <= HH && j >= 1 && j <= LL && show[i][j] == '*')
				{
					Amazeing(show, bm, i, j);
				}
			}

		}

	}
	else
	{
		show[x][y] = FindBOOM(show, bm, x, y);
	}

}




void scanBOOM(char show[HHS][LLS],char bm[HHS][LLS], int A, int B)
{
	int x = 0; int y = 0;
	printf("可根据两侧快速确定坐标\n");
	printf("输入格式:行 列\n");
	char YYY = 0;

	while (PA < HH*LL-BOM)
	{
		printBOOM(show, A, B);
		printf("请输入:>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= 9 && y >= 1 && y <= 9)
		{
			if (bm[x][y] != '1')
			{
				show[x][y] = FindBOOM(show, bm, x, y);
				PA++;
				Amazeing(show, bm, x, y);
				system("cls");
				
			}
			else
			{
				printf("恭喜你，被炸死了！！！！\n");
				show[x][y] = '!';
				printBOOM(show, A, B);
				win = 0;
				break;
			}
		}
		else
		{
			scanf("%c", &YYY);
			system("cls");
			printf("输错了！重输！！\n");
		}
	}
}	

void game2()
{
	char show[HHS][LLS] = { 0 };
	char BM[HHS][LLS] = { 0 };

	InitiaBOOM(show,HHS,LLS,'*');

	InitiaBOOM(BM, HHS, LLS, '0');

	AddBOOM(BM, HHS, LLS);

	scanBOOM(show, BM, HH, LL);

	Sleep(300);
	if(win)
		printf("恭喜获胜！！\n");

}
