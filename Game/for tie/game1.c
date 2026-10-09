#include"game.h"


void menu()
{
	char arr1[9] = { "         "};
	char arr2[9] = { "Welcome!" };
	
	for (int i = 0;i < 9;i++)
	{
		arr1[i] = arr2[i];
		Sleep(250);
		printf("%c", arr1[i]);
		printf("  ");
	}

	system("cls");
	char arr[] = { "**********************************" };
	char arr4[] = { "                                  " };

	for (int left = 0, right = sizeof(arr) / sizeof(arr[1]) - 2;left <= right;left++, right--)
	{
		arr4[left] = arr[left]; arr4[right] = arr[right];
		printf("%s", arr4);
		Sleep(100);
		
		system("cls");
		
	}
	printf("**********************************\n");


	char arr5[] = {"                                  "};
	for (int left = 0, right = sizeof(arr) / sizeof(arr[1]) - 2;left <= right;left++, right--)
	{
		arr5[left] = arr[left]; arr5[right] = arr[right];
		printf("%s", arr5);
		Sleep(100);
		
		system("cls");
		printf("**********************************\n");


	}
	printf("**********************************\n");

	char arr6[] = { "                                  " };
	for (int left = 0, right = sizeof(arr) / sizeof(arr[1]) - 2;left <= right;left++, right--)
	{
		arr6[left] = arr[left]; arr6[right] = arr[right];
		printf("%s", arr6);
		Sleep(100);
		
		system("cls");
		printf("**********************************\n");
		printf("**********************************\n");

		
	}
	printf("**********************************\n");
	printf("****                          ****\n");
	Sleep(100);
	printf("****                          ****\n");
	Sleep(200);
	printf("****                          ****\n");
	Sleep(200);
	printf("**********************************\n");
	Sleep(200);
	printf("**********************************\n");

	Sleep(300);
	system("cls");

}




void priQB(char arr[HA][LE],int x,int y)
{

	for (int i = 0;i < HA;i++)
	{
		for (int x = 0;x < LE;x++)
		{
			printf(" %c ",arr[i][x]);

			if(x<LE-1)
			printf("|");
		}
		printf("\n");
		for (int x = 0;x < LE;x++)
		{
			if(i<HA-1)
			printf("___ ");
		}
		printf("\n");
	}
}

void PlayerMove(char arr[HA][LE], int a, int b)
{
	printf("请选择您想放的位置:>");
	int x = 0, y = 0;
	char A = 0;
	while(1)
	{
		scanf("%d %d", &x, &y);

		if (x >= 1 && x <= 3 && y >= 1 && y <= 3 && arr[x-1][y-1] == ' ')
		{
			arr[x - 1][y - 1] = 'X';
			break;
		}
		else
		{
			printf("输的有问题，重输！\n");

			scanf("%c",&A);

			printf("请选择您想放的位置:>");

		}
	}
}



void ComputerMove(char arr[HA][LE],int m,int n)
{
	printf("电脑:该我了！！！\n");
	Sleep(1000);
	
	while (1)
	{
		int x = rand() % 3;
		int y = rand() % 3;
		if (arr[x][y] == ' ')
		{
			arr[x][y] = 'O';
			break;
		}
		else;
	}

}


int IsTie(char arr[HA][LE], int m, int n)
{
	for (int i = 0;i < HA;++i)
	{
		for (int j = 0;j < LE;++i)
		{
			if (arr[i][j] == ' ')
			return 1;
		}
	}
	return 2;
}

char IsWin(char arr[HA][LE], int n, int m)
{
	for (int i = 0;i < HA;i++)
	{
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][1] != ' ')
		{
			return arr[i][1];
		}
		else if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[1][i] != ' ')
		{
			return arr[1][i];
		}
	}
	if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[1][1] != ' ')
		{
			return arr[1][1];
		}
	else if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[1][1] != ' ')
		{
			return arr[1][1];
		}
	int ret = IsTie(arr, HA, LE);
	if (1 == ret)
	{
		return 'F';
	}
	else if (2 == ret)
	{
		return 'Y';
	}
}




void game1()
{
	char arr[HA][LE] = { 0 };
	for (int i = 0;i < HA;i++)
	{
		for (int j = 0;j < LE;j++)
		{
			arr[i][j] = ' ';
		}
	}
	priQB(arr,HA,LE);
	printf("Tips:输入格式为→行 列\n");

	char check = 0;

	while (1)
	{

		PlayerMove(arr, HA, LE);

		system("cls");

		priQB(arr, HA, LE);

		check = IsWin(arr, HA, LE);

		if (check == 'X')
		{
			Sleep(300);
			printf("恭喜获胜！\n");
			break;
		}
		else if (check == 'O')
		{
			Sleep(300);
			printf("牛！能让弱智赢了！\n");
			break;
		}
		else if (check == 'Y')
		{
			Sleep(300);
			printf("平局，强！！！！\n");
			break;
		}
		else;


		ComputerMove(arr, HA, LE);

		system("cls");

		check = IsWin(arr, HA, LE);

		if (check == 'X')
		{
			Sleep(300);
			printf("恭喜获胜！\n");
			printf("速速再来一把！！\n");
			break;
		}
		else if (check == 'O')
		{
			Sleep(300);
			printf("牛！能让弱智赢了！\n");
			printf("速速再来一把！！\n");

			break;
		}
		else if (check == 'Y')
		{
			Sleep(300);
			printf("平局，强！！！！\n");
			printf("速速再来一把！！\n");

			break;
		}
		else;

		priQB(arr, HA, LE);

	}

}



