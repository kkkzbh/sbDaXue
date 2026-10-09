#include"game.h"

#include<stdlib.h>
int main()
{

	srand((unsigned int)time(NULL));

	
	int op = 999;char XXX = 0;
	menu();
	do
	{
		printf("**********************************\n");
		printf("**********************************\n");
		printf("**********************************\n");
		printf("*****    1.   三子棋          ****\n");
		printf("*****    2.   扫雷            ****\n");
		printf("*****    0.   exit  game      ****\n");
		printf("**********************************\n");
		printf("**********************************\n");
		printf("请输入:>");

		scanf("%d", &op);

		scanf("%c", &XXX);

		system("cls");



		if (op == 1)
		{
			game1();
			system("pause");
			system("cls");
		}
		else if (op == 2)
		{
			game2();
			system("pause");
			system("cls");
		}
		else if (op != 0)
		{
			printf("好好输行不行？\n");
		}
		else if (op == 0)
		{
			printf("游戏已退出\n");
		}


	} while (op);





	return 0;
}