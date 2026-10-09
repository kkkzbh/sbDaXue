

#include"f_dec.h"

extern int Administrator;
extern int Admlocation;

//作为主要操作区的函数
void action()
{
	user_manage* usm = CreateUserManage();	//这里就是初始创建对象了
	room_manage* rom = CreateRoomManage();
	acc_data* data = CreateAccData();
	Reserve_manage* Res = CreateReserve();

	start(usm, rom, data, Res);

	m_log(usm, rom, data, Res);

	while (Administrator != -1)
	{
		if (Administrator == 1)
			op(usm, rom, data, Res);
		else
		{
			op_unadm(usm, rom, data, Res);
		}
	}

}


void op(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	char select = -1;


	while (select)
	{


		menu_main(usm);
		printf("\n");
		printf("请选择:>");
		select = _getch();
		start(usm, rom, data, Res);
		switch (select)			//这里用switch 会比if效率高
		{
		case '1':
			system("cls");
			oper_person_Adm(usm, rom, data, Res);
			break;
		case '2':
			system("cls");
			opra_room_Adm(usm, rom, data, Res);
			break;
		case '3':
			system("cls");
			opra_Reserve_Adm(usm, rom, data, Res);
			break;
		case '0':
			select = 0;
			Administrator = -1;
			break;
		case '5':
			system("cls");
			logout();
			m_log(usm, rom, data, Res);
			select = 0;
			break;
		default:
			system("cls");
		}

	}



}


void op_unadm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{
	printf(divider);
	printf("欢迎-- %s\t\t\t当前时间%s\n", usm->user[Admlocation].name, __TIME__);

	char select = -1;


	while (select)
	{
		menu_main_unadm(usm,rom,data,Res);
		printf("\n");
		printf("请选择:>");
		select = _getch();
		start(usm, rom, data, Res);
		switch (select)			//这里用switch 会比if效率高
		{
		case '1':
			system("cls");
			register_res(usm, rom, Res);
			Exit(usm, rom, data, Res);
			system("cls");
			break;
		case '2':
			system("cls");

			break;
		case '3':
			system("cls");
			my_register(usm, rom, data, Res);
			system("cls");
			break;
		case '0':
			select = 0;
			Administrator = -1;
			break;
		case '5':
			system("cls");
			logout();
			m_log(usm, rom, data, Res);
			select = 0;
			break;
		default:
			system("cls");
		}

	}




}

void my_register(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{
	if (usm->user[Admlocation].history_sz == -1)
	{
		printf("您未曾订购过房间！\n");
		system("pause");
		return;
	}


	printf(divider);
	printf("最近一次订房信息\n");
	printf("%-8s\t%-8s\t%-8s\n", "订购类型", "预定时间", "消费金额");
	printf("%-8s\t%-8s\t%-8d\n", usm->user[Admlocation].history[usm->user[Admlocation].history_sz].type,
		usm->user[Admlocation].history[usm->user[Admlocation].history_sz].reserve_time,
		usm->user[Admlocation].history[usm->user[Admlocation].history_sz].price);
	printf(divider);
	printf("历史订房信息\n");
	printf(divider);
	for (int i = 0;i < usm->user[Admlocation].history_sz;i++)
	{
		printf("%-8s\t%-8s\t%-8s\n", "订购类型", "预定时间", "消费金额");
		printf("%-8s\t%-8s\t%-8d\n", usm->user[Admlocation].history[i].type,
			usm->user[Admlocation].history[i].reserve_time,
			usm->user[Admlocation].history[i].price);
	}
	system("pause");
}



void menu_main_unadm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{
	printf("1.申请订房\n");
	printf("2.申请退房\n");
	printf("3.我的订房\n");
	printf("5.退出登录\n");
	printf("0.退出程序\n");

}






//主界面的菜单
void menu_main(user_manage* usm)
{
	printf("客房管理系统 --排版待定 目前供添加功能 测试功能\n");
	printf("欢迎-- %s\t\t\t当前时间%s\n", usm->user[Admlocation].name, __TIME__);

	printf("-------------------------------------------\n");
	printf("1.用户管理\n");
	printf("2.客房管理\n");
	printf("3.订房信息\n");

	printf("5.退出登录\n");


	printf("0.退出程序\n");

}



static void menu_person_Adm()
{
	printf(divider);
	printf("1.查询用户信息\n");
	printf("0.返回\n");

}

 void oper_person_Adm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	char select = -1;

	do
	{
		printf(divider);
		menu_person(usm,rom,data,Res);
		menu_person_Adm();
		printf("请选择操作 :>\n");
		select = _getch();
		start(usm, rom, data, Res);
		switch (select)
		{
		case '1':
			system("cls");
			getUserInfo(usm, rom, data, Res);
			system("cls");
			break;
		case '0':
			select = 0;
			system("cls");
			break;
		default:
			system("cls");
		}

	} while (select);


}


 static int isgetUser(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res,const int i,const char* tmp)
 {
	 return (strcmp((const char*)usm->user[i].name, tmp) == 0) +
		 (strcmp((const char*)usm->user[i].sex, tmp) == 0) +
		 (strcmp((const char*)usm->user[i].idnum, tmp) == 0) +
		 (strcmp((const char*)usm->user[i].phone, tmp) == 0) +
		 (strcmp((const char*)usm->user[i].vip, tmp) == 0) ||
		 (usm->user[i].index == atoi(tmp));
 }


 void getUserInfo(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
 {
	 printf(divider);
	 menu_person(usm, rom, data, Res);
	 printf(divider);
	 printf("请输入查询信息(索引，名称，性别，身份证号，电话号，会员状态都可以输入\n");
	 printf(" :>");


	 char tmp[TMP] = { 0 };
	 scanf("%s", tmp);
	 if (tmp[0] == '~')
		 return;

	 int find = 0;

	
	 for (int i = 0;i <= usm->sz;i++)
	 {
		 if (isgetUser(usm, rom, data, Res, (const int)i, (const char*)tmp))
		 {
			 if (!find)
			 {
				 printf(divider);
				 printf(sm "查询结果如下" sm"\n");
				 printf("%-4s\t%-8s\t%-4s\t%-18s\t%-12s\t%-6s\n", "索引", "昵称", "性别", "身份证号", "电话号码", "会员");
				 find++;

			 }
			 printf("%-4d\t%-8s\t%-4s\t%-18s\t%-12s\t%-6s\n", usm->user[i].index,
				 usm->user[i].name,
				 usm->user[i].sex,
				 usm->user[i].idnum,
				 usm->user[i].phone,
				 usm->user[i].vip);
		 }
	 }
	 if (!find)
	 {
		 printf(divider);
		 printf("没有查到指定人的信息！\n");
	 }

	 system("pause");
 }






//用户管理界面		//排版待定 先暂时能看就行
void menu_person(user_manage* usm,room_manage* rom,acc_data* data,Reserve_manage* Res)
{
	printf("%-4s\t%-8s\t%-4s\t%-18s\t%-12s\t%-6s\n", "索引", "昵称", "性别", "身份证号", "电话号码", "会员");
	for (int i = 0; i <= usm->sz;i++)
	{
		printf("%-4d\t%-8s\t%-4s\t%-18s\t%-12s\t%-6s\n",usm->user[i].index,
														usm->user[i].name,
														usm->user[i].sex,
														usm->user[i].idnum,
														usm->user[i].phone,
														usm->user[i].vip);
	}
}


static void menu_room_Adm()
{
	printf(divider);
	printf("1.登记客房信息\n");
	printf("0.返回\n");


}


void opra_room_Adm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	char select = -1;

	do
	{
		menu_room(usm, rom, data, Res);
		menu_room_Adm();
		printf("请选择操作 :>\n");
		select = _getch();
		start(usm, rom, data, Res);
		switch (select)
		{
		case '1':
			system("cls");
			register_room(rom);
			Exit(usm, rom, data, Res);
			system("cls");
			break;
		case '0':
			select = 0;
			system("cls");
			break;
		default:
			system("cls");
		}


	} while (select);






}



//客房管理界面		//排版待定 先暂时能看就行
void menu_room(user_manage* usm,room_manage* rom,acc_data* data,Reserve_manage* Res)
{
	printf("%-4s\t%-8s\t%-12s\t%-12s\t%-12s\t%-8s\n", "索引","房号", "房间类型", "房间位置", "当前状态", "价格");
	for (int i = 0; i <= rom->sz;i++)
	{
		printf("%-4d\t%-8s\t%-12s\t%-12s\t%-12s\t%-8d\n", rom->room[i].index,
													  	  rom->room[i].id,
														  rom->room[i].type,
														  rom->room[i].loaction,
														  rom->room[i].state,
														  rom->room[i].price);												
	}

}


static void menu_Reserve_Adm()
{
	printf(divider);
	printf("1.查询订房信息\n");
	printf("0.退出\n");
}

void opra_Reserve_Adm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	char select = -1;

	do
	{
		menu_Reserve(usm, rom, data, Res);
		menu_Reserve_Adm();
		printf("请选择操作 :>\n");
		select = _getch();
		start(usm, rom, data, Res);
		switch (select)
		{
		case '1':
			printf("没做\n");
			system("pause");
			system("cls");
			break;
		case '0':
			select = 0;
			system("cls");
			break;
		default:
			system("cls");
		}


	} while (select);





}


void menu_Reserve(user_manage* usm,room_manage* rom,acc_data* data,Reserve_manage* Res)
{
	printf("%-4s\t%-8s\t%-4s\t%-8s\t%-8s\t%-8s\t%-8s\t%-8s\t%-20s\n", "索引", "用户昵称", "会员", "手机号码", "支付金额","订房类型", "支付日期", "支付时间", "备注");
	for (int i = 0;i <= Res->sz;i++)
	{
		printf("%-4d\t%-8s\t%-4s\t%-8s\t%-8d\t%-8s\t%-8s\t%-8s\t%-20s\n", Res->Reserve[i].index,
																			Res->Reserve[i].name,
																			Res->Reserve[i].vip,
																			Res->Reserve[i].phone,
																			Res->Reserve[i].price,
																			Res->Reserve[i].type,
																			Res->Reserve[i].reserve_time_date,
																			Res->Reserve[i].reserve_time_day,
																			Res->Reserve[i].remark);
	}


}



//创建一个user_manage 对象
user_manage* CreateUserManage()
{
	user_manage* usm = (user_manage*)malloc(sizeof(user_manage));  //创建一个user_manage指针对象
	if (NULL == usm)	//考虑堆空间不够的情况
	{
		perror("CreateUserManage ");		//打印错误信息
		exit(-10086);	//同时这里就以-10086的返回值 表示开辟内存失败的一个额外信号吧
	}
	usm->sz = -1;   //用-1表示当前是没有用户登记的记录的 因为数组下标从0开始
	usm->user = (Person*)calloc(MINIMUM, sizeof(Person));  //使用calloc 因为会默认初始化为0 处理字符数组很方便
	usm->maxsz = MINIMUM;		//调整数组大小 因为下标从0开始 所以减1
	for (int i = 0;i < MINIMUM;i++)
	{
		usm->user[i].history = (history*)calloc(MINIMUM, sizeof(history));
		if (NULL == usm->user[i].history)
		{
			printf("内存炸了,联系管理员！\n");
			system("pause");
			return NULL;
		}
		usm->user[i].history_sz = -1;
		usm->user[i].history_maxsz = MINIMUM;
	}



	return usm;
}

//开辟user_manage对象的内部数组内存
int UsmAlloc(user_manage* usm)
{
	Person* tmp = (Person*)realloc((void*)usm->user,(usm->maxsz += ADDCOUNT)*sizeof(Person));  //调整usm的大小
	if (NULL == tmp)	//判定空间是否足够
	{
		perror("UsmAlloc ");	//打印错误信息
		return -1;
	}
	usm->user = tmp;		//realloc可能会返回一个新的位置

	for (int i = usm->sz + 1;i < usm->maxsz;i++)
	{
		usm->user[i].history = (history*)calloc(MINIMUM, sizeof(history));
		usm->user[i].history_sz = -1;
		usm->user[i].history_maxsz = MINIMUM;
	}

	return 0;
}



//登记用户信息
void register_person(user_manage* usm)
{

	if (usm->sz + 1 == usm->maxsz)	//判定是否需要开辟新的内存空间 还是因为下标0开始 所以左侧加1
	{
		int find = UsmAlloc(usm);
		if (-1 == find)
			return;
	}
	int tmp = usm->sz + 1; //先创建一个让sz加一的变量 等输入能正常结束后 再增加usm的sz
	usm->user[tmp].index = usm->sz + 1;  //原则上希望索引从0开始 而现在sz为-1 表示当前内容为空
	printf("请输入如下信息:>\n");
	printf("昵称 :>");
	scanf("%s", usm->user[tmp].name);	//输入昵称 这里直接写数组名字也可以 也可以写&name

	printf("性别 :>");
	scanf("%s", usm->user[tmp].sex);	//注意用数组访问 现在的tmp的下标是一个最后端空着的位置

	printf("身份证号 :>");
	scanf("%s", usm->user[tmp].idnum);

	printf("电话号码 :>");
	scanf("%s", usm->user[tmp].phone);


	usm->user[tmp].vip[0] = '\0';	//会员先空着
	printf("      !\n");	//待定

	usm->sz++;   //自增sz

}



//创建一个room_manage 对象
room_manage* CreateRoomManage()
{
	room_manage* rom = (room_manage*)malloc(sizeof(room_manage));  //备注请看上面
	if (NULL == rom)	//考虑堆空间不够的情况
	{
		perror("CreateRoomManage ");		//打印错误信息
		exit(-10086);	//同时这里就以-10086的返回值 表示开辟内存失败的一个额外信号吧
	}
	rom->sz = -1;
	rom->room = (Room*)calloc(MINIMUM, sizeof(Room));
	rom->maxsz = MINIMUM;		//调整数组大小
	return rom;
}




int RomAlloc(room_manage* rom)
{
	Room* tmp = (Room*)realloc((void*)rom->room, (rom->maxsz += ADDCOUNT)*sizeof(Room));
	if (NULL == tmp)	//判定空间是否足够
	{
		perror("RomAlloc ");	//打印错误信息
		return -1;
	}
	rom->room = tmp;		//因为realloc可能会返回一个新的位置
	return 0;
}



//登记房子信息
void register_room(room_manage* rom)
{
	printf("输入~返回上一级\n");
	if (rom->sz + 1 == rom->maxsz)
	{
		int find = RomAlloc(rom);
		if (find == -1)
			return;
	}
	int tmp = rom->sz + 1;
	rom->room[tmp].index = rom->sz + 1;
	printf("请输入以下信息\n");
	printf("房号 :>");
	scanf("%s", rom->room[tmp].id);
	if (rom->room[tmp].id[0] == '~')
		return;
	printf("房间类型 :>");
	scanf("%s", rom->room[tmp].type);
	if (rom->room[tmp].type[0] == '~')
		return;
	printf("房间位置 :>");
	scanf("%s", rom->room[tmp].loaction);
	if (rom->room[tmp].loaction[0] == '~')
		return;
	printf("当前状态 :>");
	scanf("%s", rom->room[tmp].state);
	if (rom->room[tmp].state[0] == '~')
		return;
	printf("价格 :>");
	scanf("%d", &rom->room[tmp].price);
	if (rom->room[tmp].price == '~')
		return;
	rom->room[tmp].state_ = 0;
	printf("登记已完成!\n");
	rom->sz++;
	system("pause");
}




//创建一个Reserve_manage 对象
Reserve_manage* CreateReserve()
{
	Reserve_manage* Res = (Reserve_manage*)malloc(MINIMUM * sizeof(Reserve_manage));
	if (NULL == Res)
	{
		perror("CreateReserve ");
		exit(-10086);
	}
	Res->Reserve = (Reserve*)calloc(MINIMUM, sizeof(Reserve));
	Res->sz = -1;
	Res->maxsz = MINIMUM;	//调整数组大小
	return Res;
}


int Resalloc(Reserve_manage* Res)
{
	Reserve* tmp = (Reserve*)realloc((void*)Res->Reserve, (Res->maxsz += ADDCOUNT) * sizeof(Reserve));
	if (NULL == tmp)
	{
		perror("Resalloc ");
		return -1;
	}

	Res->Reserve = tmp;
	return 0;
}

void menu_register_res(user_manage* usm, room_manage* rom, Reserve_manage* Res)
{

	char(*type_)[TYPE] = (char(*)[TYPE])calloc(rom->sz+1, sizeof(char[TYPE]));
	int* price = (int*)calloc(rom->sz+1, sizeof(int));
	if (NULL == type_ || NULL == price)
	{
		printf("错误！\n");
		return;
	}
	int sz = -1;
	for (int i = 0;i <= rom->sz;i++)
	{
		int find = 1;
		for (int j = 0;j <= sz;j++)
		{
			if (strcmp(type_[j], rom->room[i].type) == 0)
			{
				find = 0;
			}
		}
		if (find && rom->room[i].state_ == 0)
		{
			strcpy(type_[++sz], rom->room[i].type);
			price[sz] = rom->room[i].price;
		}
	}
	for (int i = 0; i <= sz;i++)
	{
		if (!i)
		{
			printf(divider);
			printf("%-12s\t%-8s\n", "房间类型", "支付金额");
		}
		printf("%-12s\t%-8d\n", type_[i], price[i]);
	}
	printf(divider);

	if (sz == -1)
	{
		printf("抱歉，当前没有房间\n");
		printf(divider);
	}

	free(type_);
	free(price);
}

//登记预定房间信息
void register_res(user_manage* usm,room_manage* rom,Reserve_manage* Res)
{
	if (rom->sz == -1)
	{
		printf("当前暂无房间！\n");
		system("pause");
		return;
	}



	printf("输入~返回上一级\n");

	if (Res->sz + 1 == Res->maxsz)
	{
		int find = Resalloc(Res);
		if (-1 == find)
			return;
	}
	int tmp = Res->sz + 1;
	Res->Reserve[tmp].index = Res->sz + 1;


	char type[TYPE] = { 0 };
	char remark[REMARK] = { 0 };
	
	res:
	menu_register_res(usm, rom, Res);
	printf("请输入您想预定的房间类型 :>");
	scanf("%s", type);
	if (type[0] == '~')
		return;

	getchar();
	printf("留个备注喵 :>");
	char tmp__ = -1;
	if ((tmp = getchar()) == '\n')
	{
		;
	}
	else
	{
		remark[0] = tmp;
		scanf("%s", remark+1);
		getchar();
	}
	if (remark[0] == '~')
		return;


	if (FindSpareRoom((const char*)type, (const char*)remark, usm, rom, Res))
	{
		Res->sz++;
	}
	else
	{
		goto res;
	}
}



int FindSpareRoom(const char* type,const char* remark,user_manage* usm,room_manage* rom,Reserve_manage* Res)
{
	int find = 0;
	int tmp = Res->sz + 1;
	Room* tmp_room = (Room*)calloc(rom->sz + 1, sizeof(Room));
	if (NULL == tmp_room)
	{
		printf("无法寻找空余房间,请联系管理员处理！\n");
		system("pause");
		return 0;
	}
	int sz = -1;

	for (int i = 0;i <= rom->sz;i++)
	{
		if (strcmp(type, rom->room[i].type) == 0 && rom->room[i].state_ == 0)
		{
			tmp_room[++sz] = rom->room[i];
			find = 1;
		}
	}
	int location = 0;
	char select = -1;

	system("cls");

	printf(divider);



	if (!find)
	{
		printf("抱歉,当前没有此类型房间可供订入\n");
	}
	else
	{
		printf("为您匹配了一个房间(按←→切换,Enter确定订入,输入~表示我不订了)\n");
		{
			while (select)
			{
				printf("当前共有%d个房间可订入 目前为%d/%d个房间\n", sz+1, location+1, sz+1);
				printf("%-4s\t%-8s\t%-12s\t%-12s\t%-12s\t%-8s\n", "索引", "房号", "房间类型", "房间位置", "当前状态", "价格");
				printf("%-4d\t%-8s\t%-12s\t%-12s\t%-12s\t%-8d\n", tmp_room[location].index,
					tmp_room[location].id,
					tmp_room[location].type,
					tmp_room[location].loaction,
					tmp_room[location].state,
					tmp_room[location].price);



				select = _getch();
				if (select == 77)
				{
					location++;
					if (location > sz)
					{
						location = 0;
					}
				}
				else if (select == 75)
				{
					location--;
					if (location < 0)
					{
						location = sz;
					}
				}
				else if (select == '\r' || select == '\n')
				{
					strcpy(Res->Reserve[tmp].name, (const char*)usm->user[Admlocation].name);
					strcpy(Res->Reserve[tmp].vip, (const char*)usm->user[Admlocation].vip);
					Res->Reserve[tmp].price = tmp_room[location].price;
					strcpy(Res->Reserve[tmp].reserve_time_date, __DATE__);
					strcpy(Res->Reserve[tmp].reserve_time_day, __TIME__);
					strcpy(Res->Reserve[tmp].remark, remark);
					strcpy(Res->Reserve[tmp].phone, (const char*)usm->user[Admlocation].phone);
					rom->room[tmp_room[location].index].state_ = 1;
					strcpy(Res->Reserve[tmp].type, type);

					select = 0;
					

					if(usm->user[Admlocation].history_sz + 1 == usm->user[Admlocation].history_maxsz)
					{
						allochistory(usm);
					}
					++usm->user[Admlocation].history_sz;
					strcpy(usm->user[Admlocation].history[usm->user[Admlocation].history_sz].type, type);
					strcpy(usm->user[Admlocation].history[usm->user[Admlocation].history_sz].reserve_time, __TIME__);
					usm->user[Admlocation].history[usm->user[Admlocation].history_sz].price = tmp_room[location].price;


					printf("订房成功！\n");
					find = 1;
					system("pause");
				}
				else if(select == '~')
				{
					printf("感谢访问\n");
					select = 0;
					find = 0;
					system("pause");
				}


				system("cls");

			}
		}

	}


	free(tmp_room);
	system("cls");

	return find;
}




int allochistory(user_manage* usm)
{
	history* tmp = (history*)realloc(usm->user[Admlocation].history, (usm->user[Admlocation].history_maxsz += ADDCOUNT) * sizeof(history));
	if (NULL == tmp)
	{
		perror("allochistory :");
		return -1;
	}
	usm->user[Admlocation].history = tmp;
	
	return 0;
}




void start(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	FILE* Fusmc = fopen("./file/USMconfig.dat", "r");
	FILE* Fusm = fopen("./file/USMusers.dat", "r");

	FILE* Fromc = fopen("./file/Fromc.dat", "r");
	FILE* From = fopen("./file/From.dat", "r");

	FILE* Fdata = fopen("./file/Fdata.dat", "r");
	FILE* Faccount = fopen("./file/Faccount.dat", "r");

	FILE* Fresm = fopen("./file/Fresm.dat", "r");
	FILE* Fres = fopen("./file/Fres.dat", "r");

	FILE* Fhis = fopen("./file/Fhis.dat", "r");



	if (NULL != Fusmc && NULL != Fusm && NULL != Fdata && NULL != Faccount && NULL != Fresm && NULL != Fres && NULL != From && NULL != Fromc && NULL != Fhis)
	{
		fread((void*)&usm->sz, sizeof(int), (size_t)1, Fusmc);
		fread((void*)&usm->maxsz, sizeof(int), (size_t)1, Fusmc);


		fread((void*)&rom->sz, sizeof(int), (size_t)1, Fromc);
		fread((void*)&rom->maxsz, sizeof(int), (size_t)1, Fromc);

		fread((void*)&data->sz, sizeof(int), (size_t)1, Fdata);
		fread((void*)&data->maxsz, sizeof(int), 1, Fdata);

		fread((void*)&Res->sz, sizeof(int), (size_t)1, Fresm);
		fread((void*)&Res->maxsz, sizeof(int), (size_t)1, Fresm);


		Person* tmp = (Person*)realloc(usm->user, (usm->maxsz) * sizeof(Person));

		Room* tmprom = (Room*)realloc(rom->room, (rom->maxsz) * sizeof(Room));

		account* tmpacc = (account*)realloc(data->account, (data->maxsz) * sizeof(account));

		Reserve* tmpRes = (Reserve*)realloc(Res->Reserve, (Res->maxsz) * sizeof(Reserve));

	
		if (NULL == usm->user || NULL == data->account || NULL == tmpRes || NULL == tmprom)
		{
			perror("File ");
			exit(-10086);
		}




		usm->user = tmp;
		fread((void*)usm->user, sizeof(Person), (size_t)usm->sz + 1, Fusm);
		fclose(Fusmc);
		fclose(Fusm);

		rom->room = tmprom;
		fread((void*)rom->room, sizeof(Room), (size_t)rom->sz + 1, From);
		fclose(Fromc);
		fclose(From);

		data->account = tmpacc;
		fread((void*)data->account, sizeof(account), (size_t)data->sz + 1, Faccount);
		fclose(Fdata);
		fclose(Faccount);

		Res->Reserve = tmpRes;
		fread((void*)Res->Reserve, sizeof(Reserve), (size_t)Res->sz + 1, Fres);
		fclose(Fresm);
		fclose(Fres);

		for (int i = 0;i <= usm->sz && usm->user[i].history_sz != -1;i++)
		{
			usm->user[i].history = (history*)realloc(usm->user[i].history, (usm->user[i].history_sz + 1) * sizeof(history));
			fread((void*)usm->user[i].history, sizeof(history), (size_t)(usm->user[i].history_sz + 1), Fhis);
		}

		fclose(Fhis);

	}


	Fusmc = Fusm = NULL;
	Fdata = Faccount = NULL;
	Fresm = Fres = NULL;
	Fromc = From = NULL;
	Fhis = NULL;

}


void Exit(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	FILE* Fusmc = fopen("./file/USMconfig.dat", "w");
	FILE* Fusm = fopen("./file/USMusers.dat", "w");
	fwrite((const void*)&usm->sz, sizeof(int), (size_t)1, Fusmc);
	fwrite((const void*)&usm->maxsz, sizeof(int), (size_t)1, Fusmc);
	fwrite((const void*)usm->user, sizeof(Person), (size_t)usm->sz + 1, Fusm);



	FILE* Fromc = fopen("./file/Fromc.dat", "w");
	FILE* From = fopen("./file/From.dat", "w");
	fwrite((const void*)&rom->sz, sizeof(int), (size_t)1, Fromc);
	fwrite((const void*)&rom->maxsz, sizeof(int), (size_t)1, Fromc);
	fwrite((const void*)rom->room, sizeof(Room), (size_t)rom->sz + 1, From);


	FILE* Fdata = fopen("./file/Fdata.dat", "w");
	FILE* Faccount = fopen("./file/Faccount.dat", "w");
	fwrite((const void*)&data->sz, sizeof(int), (size_t)1, Fdata);
	fwrite((const void*)&data->maxsz, sizeof(int), (size_t)1, Fdata);
	fwrite((const void*)data->account, sizeof(account), (size_t)data->sz + 1, Faccount);



	FILE* Fresm = fopen("./file/Fresm.dat", "w");
	FILE* Fres = fopen("./file/Fres.dat", "w");
	fwrite((const void*)&Res->sz, sizeof(int), (size_t)1, Fresm);
	fwrite((const void*)&Res->maxsz, sizeof(int), (size_t)1, Fresm);
	fwrite((const void*)Res->Reserve, sizeof(Reserve), (size_t)Res->sz + 1, Fres);


	FILE* Fhis = fopen("./file/Fhis.dat", "w");
	for (int i = 0;i <= usm->sz;i++)
	{
		fwrite((const void*)usm->user[i].history, sizeof(history), (size_t)(usm->user[i].history_sz + 1), Fhis);
	}



	fclose(Fusmc);
	fclose(Fusm);

	fclose(Fromc);
	fclose(From);

	fclose(Fdata);
	fclose(Faccount);

	fclose(Fresm);
	fclose(Fres);


	fclose(Fhis);


	Fusmc = Fusm = NULL;
	Fromc = From = NULL;
	Fdata = Faccount = NULL;
	Fresm = Fres = NULL;
	Fhis = NULL;

}
