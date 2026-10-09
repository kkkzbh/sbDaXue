

#include"f_dec.h"


const char key[KEY] = "woful";		//判定是否是管理员的一串key
int Administrator = -1;
int Admlocation = -1;
extern TIME* TIM;

//建立一个账号数据库
acc_data* CreateAccData()
{
	acc_data* data = (acc_data*)malloc(sizeof(acc_data));	//重复工作 不再注释
	if (NULL == data)
	{
		perror("CreateAccData ");
		exit(-10086);
	}
	data->sz = -1;
	data->account = (account*)calloc(MINIMUM, sizeof(account));
	data->maxsz = MINIMUM;
	return data;
}

//调整内存
int DataAlloc(acc_data* data)
{
	account* tmp = (account*)realloc((void*)data->account, (data->maxsz += ADDCOUNT) * sizeof(account));
	if (NULL == tmp)
	{
		perror("DataAlloc ");
		return -1;
	}
	data->account = tmp;
	return 0;
}

//查找账号数据库 检验是否可登录账号
int FindAcc(acc_data* data,const char* acc_num,const char* password,int* sz)
{
	int find = 1;
	for (int i = 0;i <= data->sz && find ; i++)
	{
		if (   (!strcmp(acc_num, data->account[i].account_num)) && (!strcmp(password, data->account[i].password)))	//检验账号密码的合理性
		{
			find = 0;
			printf(GREEN_TEXT"              >>>>>>>>>登录成功！！！<<<<<<<<<\n");
			printf(WHITE_TEXT "                       欢迎 %s\n",data->account[i].user.name);
			Administrator = data->account[i].adm;
			Admlocation = i;
		}
	}
	if (find)
	printf(RED_TEXT"输入的信息有误 请重新输入\n");
	return find;
}

//实际上 输入密码是一个非常困难的事情
//所以我要额外用一个函数去实现输入密码
void enter_password(char* password)
{
	char ch = 0;
	int sz = -1;
	while (TRUE)
	{
		ch = _getch();
		if (ch == '\r')
		{
			printf("\n");
			break;
		}
		else if (ch == 0x08 && sz >= 0 )
		{
			printf("\b \b");
			sz--;
		}
		else if(ch != 0x08)
		{
			password[++sz] = ch;
			printf("*");
		}

	}
	password[++sz] = '\0';
}



void login(user_manage* usm,acc_data* data)		//登录账号
{
	char acc_num[ACCOUNT_NUM] = { 0 };
	char password[PASSWORD] = { 0 };
	int sz = 0;
	do
	{
		//printf(WHITE_TEXT " -------------------\n");
		//printf( "|  输入~返回上一级  |\n");
		//printf(" -------------------\n");
		//printf("\n");
		
		printf(WHITE_TEXT "               *************************************************\n");
		printf(           "               **             欢迎来到客房管理系统            **\n");
		printf(           "               **          --------------------------         **\n");
		printf(           "               **          >>>>>>>>>登录账号<<<<<<<<<         **\n");
		printf(           "               **                                             **\n");
		printf(           "               **           //若需注册新账号请按~//           **\n");
		printf(           "               *************************************************\n");
		printf(">>>>>账号 :");
		scanf("%s", acc_num);
		if (acc_num[0] == '~')
		{
			system("cls");
			register_account(data, usm);
			system("cls");
			return;
		}
		printf(">>>>>密码 :");
		enter_password(password);
		if (password[0] == '~')
		{
			system("cls");
			register_account(data, usm);
			system("cls");
			return;
		}
	}while(FindAcc(data, (const char*)acc_num, (const char*)password,&sz));




	system("pause");
	system("cls");
}


//检查是否注册了同样的账号 重了返回 1 ！
int check(const char* acc_num,acc_data* data)
{
	int flag = 0;
	for (int i = 0;i <= data->sz && !flag;i++)
	{
		if (strcmp(acc_num, data->account[i].account_num) == 0)
		{
			flag = 1;
		}
	}
	return flag; 
}


void register_account(acc_data* data,user_manage* usm)		//注册账号
{
	//printf(WHITE_TEXT " -------------------\n");
	//printf("|  输入~返回上一级  |\n");
	//printf(" -------------------\n");
	//printf("\n");
	if (data->sz + 1 == data->maxsz)
	{
		int find = DataAlloc(data);
		if (-1 == find)
			return;
	}
	char acc_num[ACCOUNT_NUM] = { 0 };
	char password[PASSWORD] = { 0 };
	char confirm_password[PASSWORD] = { 0 };
	char key_[KEY] = { 0 };
	int flag = 0;
	int tmp = data->sz + 1;

	do
	{
		printf(WHITE_TEXT "               *************************************************\n");
		printf("               **             欢迎来到客房管理系统            **\n");
		printf("               **          --------------------------         **\n");
		printf("               **          >>>>>>>>>注册账号<<<<<<<<<         **\n");
		printf("               **                                             **\n");
		printf("               **           //若需登录原有账号请按~//         **\n");
		printf("               *************************************************\n");
		printf("\n");
		printf("                        >>>>>>>>>>>>>请设置:<<<<<<<<<<<<\n");
		printf("\n");

		acc_num:

		printf(WHITE_TEXT ">>>>>账号 :");
		scanf("%s", acc_num);
		if (acc_num[0] == '~')
		{
			system("cls");
			return;
		}
		if (check((const char*)acc_num, data))
		{
			printf(RED_TEXT"账号已存在 请重新输入！\n");
			goto acc_num;
		}


		printf(WHITE_TEXT ">>>>>密码 :");
		enter_password(password);
		if (password[0] == '~')
		{
			system("cls");
			return;
		}
		printf(">>>>>确认密码 :");
		enter_password(confirm_password);
		if (confirm_password[0] == '~')
			return;
		if (flag = strcmp( (const char*)password, (const char*)confirm_password) )
		{
			printf(RED_TEXT"两次密码输入不一致,请重新输入\n");
		}
	} while (flag);
	printf(WHITE_TEXT ">>>>>请输入管理员身份认证码 :\n");
	char ch = 0;
	getchar();

	if ((ch = getchar()) == '\n')
	{
		;
	}
	else
	{
		key_[0] = ch;
		scanf("%s", key_+1);
	}


	if (!strcmp((const char*)key_, key))
	{
		data->account[tmp].adm = 1;
	}
	strcpy(data->account[tmp].account_num, (const char*)acc_num);
	strcpy(data->account[tmp].password, (const char*)password);


	register_person(usm);
	data->sz++;
	memcpy((void*)&data->account[data->sz].user, (const void*)&usm->user[usm->sz], sizeof(Person));
	strcpy(data->account[data->sz].ymd, TIM->ymd);
	printf(GREEN_TEXT"              >>>>>>>>>>>>注册成功！<<<<<<<<<<\n");

	system("pause");
}



void menu_login()
{
	printf(WHITE_TEXT "               *************************************************\n");
	printf("               **             欢迎来到客房管理系统            **\n");
	printf("               **          --------------------------         **\n");
	printf("               **          >>>>>>>>>账户菜单<<<<<<<<<         **\n");
	printf("               **                 1.登录账号                  **\n");
	printf("               **                 2.注册账号                  **\n");
	printf("               *************************************************\n");
}                          

void m_log(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{
	char select = -1;


	while (Administrator == -1 && select != 0)
	{
		//menu_login();
		//printf(WHITE_TEXT ">>>>>请选择 :");
		select = _getch();
		start(usm, rom, data, Res);

		switch (select)
		{
		case '1':
			system("cls");
			login(usm, data);
			system("cls");
			break;
		case '2':
			system("cls");
			register_account(data, usm);
			Exit(usm, rom, data, Res);
			system("cls");
			break;
		case '0':
			select = 0;
			break;
		default:
			printf(RED_TEXT">>>>>输入错误！重新输入 :");
			system("cls");
		}

	}

}




void logout()
{
	Administrator = -1;
	Admlocation = -1;
}














