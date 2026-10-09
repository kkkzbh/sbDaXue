#include"hc.h"


int main()
{
	char a[MENUR][MENUL] = { 0 };
	menu(a);
	Contact Con;
	Contact* con = &Con;
	IniContact(con);
	int n = 0;
	pmenu(a);
	do
	{
		printf("\n\n请选择(数字):>");
		scanf("%d", &n);
		switch (n)
		{
		case print:
			system("cls");
			Print(con);
			printf("\n");
			system("pause");
			system("cls");
			pmenu(a);
			break;
		case search:
			Search(con);
			system("pause");
			system("cls");
			pmenu(a);
			break;
		case add:
			Add(con);
			Sleep(800);
			system("cls");
			pmenu(a);
			break;
		case del:
			Delete(con);
			system("pause");
			system("cls");
			pmenu(a);
			break;
		case sort:
			Sort(con);
			Sleep(800);
			system("cls");
			pmenu(a);
			break;
		case modify:
			Modify(con);
			Sleep(800);
			system("cls");
			pmenu(a);
			break;
		case EXIT:
			Exit(con);
			break;
		default:
			printf("输入的信息不正确 请重新输入\n");
			break;
		}
	} while(n);

	return 0;
}

