#include"hc.h"


void menu(char (*a)[MENUL])
{
	//char a[MENUR][MENUL] = { 0 };
	for (int i = 0; i < MENUR; i++)
	{
		int j = 0;
		for (j = 0; j < MENUL-1; j++)
		{
			a[i][j] = ' ';
		}
	}
	for (int i = 0;i < MENUL-1;i++)
	{
		for (int j = 0; j < MENUR;j++)
		{
			if((j <= BOARDUP || j >= BOARDDOWN) || (i<= BOARDLEFT || i >= BOARDRIGHT))
			a[j][i] = '*';

			printf("%s\n",&a[j][0]);
		}
		Sleep(1);
		system("cls");
	}
	strncpy(a[4] + 13, "1.print",7);
	strncpy(a[4] + 26, "2.search", 8);
	strncpy(a[5] + 13, "3.add", 5);
	strncpy(a[5] + 26, "4.delete", 8);
	strncpy(a[6] + 13, "5.sort", 6);
	strncpy(a[6] + 26, "6.modify", 8);
	strncpy(a[7] + 20, "0.exit", 6);
}

void pmenu(char(*a)[MENUL])
{
	for (int j = 0; j < MENUR;j++)
	{
		printf("%s\n", &a[j][0]);
	}
}


void Print(Contact* x)
{
	printf("%-12s\t%-8s\t%-4s\t%-10s\n", "id","name","sex","phone");
	for (int i = 0;i < (x->sz); i++)
	{
		printf("%-12lld\t%-8s\t%-4s\t%-10lld\n",
			x->a[i].id,
			x->a[i].name,
			x->a[i].sex,
			x->a[i].phone);
	}
}

static void ModifyContent(Contact* x)
{
	if (0 == (x->count) - (x->sz))
	{
		Person* ptr = realloc(x->a, (x->count += ADD_COUNT) * sizeof(Person));
		if (NULL != ptr)
		{
			x->a = ptr;
			ptr = NULL;
		}
	}
}

void Add(Contact* x)
{
	ModifyContent(x);

	printf("请输入id(学号):");
	scanf("%lld", &x->a[x->sz].id);
	printf("请输入姓名:>");
	scanf("%s", x->a[x->sz].name);
	printf("请输入性别:>");
	scanf("%s", x->a[x->sz].sex);
	printf("请输入电话号码:>");
	scanf("%lld", &x->a[x->sz].phone);
	(x->sz)++;
	printf("添加成功！\n");
	
}


void Search(Contact* x)
{
	long long id = 0;
	char name[NAME] = { 0 };
	printf("输入要查找的学号或姓名:>");
	//scanf("%d %s", name, &id);
	int find = 0;
	if (scanf("%lld",&id))
	{
		for (int i = 0; i < (x->sz); i++)
		{
			if (id == x->a[i].id)
			{
				find = 1;
				printf("查找人的信息如下\n");
				printf("%-12s\t%-8s\t%-4s\t%-10s\n", "id", "name", "sex", "phone");
				printf("%-12lld\t%-8s\t%-4s\t%-10lld\n",
					x->a[i].id,
					x->a[i].name,
					x->a[i].sex,
					x->a[i].phone);

			}
		}
	}
	else if (scanf("%s",name))
	{
		for (int i = 0; i < (x->sz);i++)
		{
			if (!(strcmp(name, x->a[i].name)))
			{
				find = 1;
				printf("查找人的信息如下\n");
				printf("%-12s\t%-8s\t%-4s\t%-10s\n", "id", "name", "sex", "phone");
				printf("%-12lld\t%-8s\t%-4s\t%-10lld\n",
					x->a[i].id,
					x->a[i].name,
					x->a[i].sex,
					x->a[i].phone);
			}
		}
	}
	if (!find)
	{
		printf("并未查询到指定人的信息\n");
	}
}

static void Move(Contact* x,int n)
{
	for (int i = n;i < (x->sz) - 1;i++)
	{
		x->a[i] = x->a[i + 1];
	}
	(x->sz)--;
}

void Delete(Contact* x)
{
	printf("请输入要删除人的姓名或学号>:");
	long long id = 0;
	char name[NAME] = { 0 };
	int find = 0;
	if (scanf("ll%d", &id))
	{
		for (int i = 0; i < (x->sz); i++)
		{
			if (id == x->a[i].id)
			{
				find = 1;
				printf("已成功删除\n");
				printf("%-12s\t%-8s\t%-4s\t%-10s\n", "id", "name", "sex", "phone");
				printf("%-12lld\t%-8s\t%-4s\t%-10lld\n",
					x->a[i].id,
					x->a[i].name,
					x->a[i].sex,
					x->a[i].phone);
				Move(x,i--);
			}
		}
	}
	else if (scanf("%s", name))
	{
		for (int i = 0; i < (x->sz);i++)
		{
			if (!(strcmp(name, x->a[i].name)))
			{
				find = 1;
				printf("已成功删除\n");
				printf("%-12s\t%-8s\t%-4s\t%-10s\n", "id", "name", "sex", "phone");
				printf("%-12lld\t%-8s\t%-4s\t%-10lld\n",
					x->a[i].id,
					x->a[i].name,
					x->a[i].sex,
					x->a[i].phone);
				Move(x, i--);
			}
		}
	}
	if (!find)
	{
		printf("并未能删除什么\n");
	}
}

static void Swap(char* e1, char* e2, int width)
{
	for (int i = 0;i < width;i++)
	{
		char tem = *e1;
		*e1 = *e2;
		*e2 = tem;
		e1++;
		e2++;
	}
}

static long long idsort(Person* e1, Person* e2)
{
	return (e1->id) - (e2->id);
}

static int namesort(Person* e1, Person* e2)
{
	char* x = e1->name;
	char* y = e2->name;
	while (!(*x-*y) && *x)
	{
		x++;
		y++;
	}
	return *x - *y;
}

static void bubble_sort(void* base, int sz, int width, int (*cmp)(void* e1, void* e2))
{
	for (int i = 0;i < sz ;i++)
	{
		for (int j = 0;j < sz - i;j++)
		{
			if ((*cmp)((char*)(base)+(j * width), (char*)(base)+((j + 1) * width)) > 0)
			{
				Swap((char*)(base)+(j * width), (char*)(base)+((j + 1) * width), width);
			}
		}
	}
}


void Sort(Contact* x)
{
	printf("您希望按照什么来排序？\n");
	printf("***1.id      2.name***\n");
	int n = 0;
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		bubble_sort(x->a, (x->sz) - 1,sizeof(Person), idsort);
		printf("排序成功！\n");
		break;
	case 2:
		bubble_sort(x->a, (x->sz) - 1,sizeof(Person), namesort);
		printf("排序成功！\n");
		break;
	}
}

void Modify(Contact* x)
{
	long long id = 0;
	char name[NAME] = { 0 };
	printf("输入要修改人的学号或姓名:>");
	//scanf("%d %s", name, &id);
	int find = 0;
	if (scanf("%lld", &id))
	{
		for (int i = 0; i < (x->sz); i++)
		{
			if (id == x->a[i].id)
			{
				find = 1;
				printf("查找人的信息如下\n");
				printf("%-12s\t%-8s\t%-4s\t%-10s\n", "id", "name", "sex", "phone");
				printf("%-12lld\t%-8s\t%-4s\t%-10lld\n",
					x->a[i].id,
					x->a[i].name,
					x->a[i].sex,
					x->a[i].phone);
				int Select = 0;
				printf("您是否想改的是这个人？\n1.是	0.不是	\n请输入:>");
				scanf("%d", &Select);
				if (Select)
				{
					printf("请输入id(学号):");
					scanf("%lld", &x->a[i].id);
					printf("请输入姓名:>");
					scanf("%s", x->a[i].name);
					printf("请输入性别:>");
					scanf("%s", x->a[i].sex);
					printf("请输入电话号码:>");
					scanf("%lld", &x->a[i].phone);
					printf("修改成功！\n");
				}
				else
				{
					find = 0;
				}
			}
		}


	}
	else if (scanf("%s", name))
	{
		for (int i = 0; i < (x->sz);i++)
		{
			if (!(strcmp(name, x->a[i].name)))
			{
				find = 1;
				printf("查找人的信息如下\n");
				printf("%-12s\t%-8s\t%-4s\t%-10s\n", "id", "name", "sex", "phone");
				printf("%-12lld\t%-8s\t%-4s\t%-10lld\n",
					x->a[i].id,
					x->a[i].name,
					x->a[i].sex,
					x->a[i].phone);

				int Select = 0;
				printf("您是否想改的是这个人？\n1.是	0.不是	\n请输入:>");
				scanf("%d", &Select);
				if (Select)
				{
					printf("请输入id(学号):");
					scanf("%lld", &x->a[i].id);
					printf("请输入姓名:>");
					scanf("%s", x->a[i].name);
					printf("请输入性别:>");
					scanf("%s", x->a[i].sex);
					printf("请输入电话号码:>");
					scanf("%lld", &x->a[i].phone);
					printf("修改成功！\n");
				}
				else
				{
					find = 0;
				}
			}
		}
	}
	if (!find)
	{
		printf("并未查询到指定人\n");
	}
}

void IniContact(Contact* x)
{
	x->a = malloc(DEFAULT_COUNT * sizeof(Person));
	if (NULL == x->a)
	{
		perror("Inimalloc");
		return;
	}
	x->sz = 0;
	x->count = DEFAULT_COUNT;
	FILE* ptr1 = fopen("pContact.dat","r");
	FILE* ptr2 = fopen("Person.dat", "r");
	if (NULL == ptr1 || NULL == ptr2)
	{
		perror("fopen");
		return;
	}
	fread(&(x->sz), sizeof(int), 1, ptr1);
	
	fread(&(x->count), sizeof(int), 1, ptr1);

	Person* ptr = realloc(x->a, (x->count) * sizeof(Person));
	if (NULL == ptr)
	{
		perror("Inread-realloc");
		return;
	}
	x->a = ptr;
	ptr = NULL;

	fread(x->a, sizeof(Person), x->sz, ptr2);
	

	fclose(ptr1);
	fclose(ptr2);
	ptr1 = ptr2 = NULL;
}

void Exit(Contact* x)
{

	FILE* ptr1 = fopen("pContact.dat", "w");
	FILE* ptr2 = fopen("Person.dat", "w");
	if (NULL == ptr1 || NULL == ptr2)
	{
		perror("fopen");
	}

	fwrite(&(x->sz), sizeof(int), 1, ptr1);
	fwrite(&(x->count), sizeof(int), 1, ptr1);
	fwrite(x->a, sizeof(Person), x->sz, ptr2);

	fclose(ptr1);
	fclose(ptr2);
	ptr1 = ptr2 = NULL;

	free(x->a);
	system("cls");
	printf("程序已正常退出！\n");
}