
#include"f_dec.h"


void Sort(void* dst, size_t block, size_t sz, int (*f)(void* e1, void* e2))
{
	for (int i = 0;i < sz - 1;i++)
	{
		int min = i;
		for (int j = i + 1;j < sz;j++)
		{
			if (f((char*)dst + (j * block), (char*)dst + (min * block)) < 0)
			{
				min = j;
			}
		}
		if (min != i)
			Swap((char*)dst + (i * block), (char*)dst + (min * block), block);
	}
}

static void Swap(void* e1, void* e2, size_t block)
{
	char* tmp1 = (char*)e1;
	char* tmp2 = (char*)e2;
	for (int i = 0;i < block;i++)
	{
		*tmp1 = *tmp1 ^ *tmp2;	//使用^要注意 不要^自己 否则交换失效
		*tmp2 = *tmp1 ^ *tmp2;
		*tmp1 = *tmp1 ^ *tmp2;
		tmp1++;
		tmp2++;
	}
}

int INT(void* e1, void* e2)
{
	return *(int*)e1 - *(int*)e2;
}

int Person_index(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return x1->index - x2->index;
}

int Person_name(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->name, x2->name);
}

int Person_sex(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->sex, x2->sex);
}

int Person_age(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->age, x2->age);
}

int Person_idnum(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->idnum, x2->idnum);
}

int Person_phone(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->phone, x2->phone);
}

int Person_vip(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->vip, x2->vip);
}

int Person_ymd(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->ymd, x2->ymd);
}

int Room_index(void* e1, void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return x1->index - x2->index;
}

int Room_id(void* e1, void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return cmp(x1->id, x2->id);
}

int Room_type(void* e1,void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return cmp(x1->type, x2->type);
}

int Room_loaction(void* e1, void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return cmp(x1->loaction, x2->loaction);
}

int Room_state(void* e1, void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return cmp(x1->state, x2->state);
}

int Room_price(void* e1, void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return x1->price - x2->price;
}

int Room_ymd(void* e1, void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return cmp(x1->ymd, x2->ymd);
}

int Room_hms(void* e1, void* e2)
{
	Room* x1 = (Room*)e1;
	Room* x2 = (Room*)e2;
	return cmp(x1->hms, x2->hms);
}


int Res_index(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return x1->index - x2->index;
}

int Res_name(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->name, x2->name);
}

int Res_vip(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->vip,x2->vip);
}

int Res_price(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return x1->price - x2->price;
}

int Res_sex(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->sex, x2->sex);
}

int Res_age(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->age, x2->age);
}

int Res_ymd(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->reserve_time_date, x2->reserve_time_date);
}

int Res_hms(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->reserve_time_day, x2->reserve_time_day);
}

int Res_type(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->type, x2->type);
}

int Res_wday(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->wday, x2->wday);
}


int Res_mon(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->mon, x2->mon);
}

int Res_year(void* e1, void* e2)
{
	Reserve* x1 = (Reserve*)e1;
	Reserve* x2 = (Reserve*)e2;
	return cmp(x1->year, x2->year);
}

void menu_Sort_Res(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	printf(WHITE_TEXT "               *************************************************\n");
	printf("               **               欢迎来到排序系统              **\n");
	printf("               **          --------------------------         **\n");
	printf("               **          >>>>您希望按如何排序？<<<<         **\n");
	printf("               **                                             **\n");
	printf("               **                 1.按索引                    **\n");
	printf("               **                 2.按名称                    **\n");
	printf("               **                 3.按会员                    **\n");
	printf("               **                 4.按支付金额                **\n");
	printf("               **                 5.按性别                    **\n");
	printf("               **                 6.按年龄                    **\n");
	printf("               **                 7.按日期                    **\n");
	printf("               **                 8.按类型                    **\n");
	printf("               **                 9.按星期                    **\n");
	printf("               **                 10.按月份                   **\n");
	printf("               **                 11.按年份                   **\n");
	printf("               **                                             **\n");
	printf("               **             //按`返回上一级~//              **\n");
	printf("               *************************************************\n");


	char select = -1;
	while (select)
	{
		select = _getch();
		switch (select)
		{
		case '1':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_index);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '2':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_name);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '3':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_vip);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '4':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_price);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '5':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_sex);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '6':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_age);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '7':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_ymd);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '8':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_type);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '9':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_wday);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '10':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_mon);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '11':
			Sort(Res->Reserve, sizeof(Reserve), Res->sz + 1, Res_year);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case RETURN:
			select = 0;
			break;
		default:
			break;
		}
	}
	system("cls");
}


void menu_Sort_Room(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	printf(WHITE_TEXT "               *************************************************\n");
	printf("               **               欢迎来到排序系统              **\n");
	printf("               **          --------------------------         **\n");
	printf("               **          >>>>您希望按如何排序？<<<<         **\n");
	printf("               **                                             **\n");
	printf("               **                 1.按索引                    **\n");
	printf("               **                 2.按房号                    **\n");
	printf("               **                 3.按类型                    **\n");
	printf("               **                 4.按位置                    **\n");
	printf("               **                 5.按状态                    **\n");
	printf("               **                 6.按价格                    **\n");
	printf("               **                 7.按日期                    **\n");
	printf("               **                                             **\n");
	printf("               **             //按`返回上一级~//              **\n");
	printf("               *************************************************\n");

	char select = -1;
	while (select)
	{
		select = _getch();
		switch (select)
		{
		case '1':
			Sort(rom->room, sizeof(Room), rom->sz + 1, Room_index);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '2':
			Sort(rom->room, sizeof(Room), rom->sz + 1, Room_id);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '3':
			Sort(rom->room, sizeof(Room), rom->sz + 1, Room_type);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '4':
			Sort(rom->room, sizeof(Room), rom->sz + 1, Room_loaction);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '5':
			Sort(rom->room, sizeof(Room), rom->sz + 1, Room_state);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '6':
			Sort(rom->room, sizeof(Room), rom->sz + 1, Room_price);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '7':
			Sort(rom->room, sizeof(Room), rom->sz + 1, Room_ymd);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case RETURN:
			select = 0;
			break;
		default:
			break;
		}
	}
	system("cls");
}

void menu_Sort_Person(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res)
{

	printf(WHITE_TEXT "               *************************************************\n");
	printf("               **               欢迎来到排序系统              **\n");
	printf("               **          --------------------------         **\n");
	printf("               **          >>>>您希望按如何排序？<<<<         **\n");
	printf("               **                                             **\n");
	printf("               **                 1.按索引                    **\n");
	printf("               **                 2.按名称                    **\n");
	printf("               **                 3.按性别                    **\n");
	printf("               **                 4.按年龄                    **\n");
	printf("               **                 5.按身份证号                **\n");
	printf("               **                 6.按电话号码                **\n");
	printf("               **                 7.按会员状态                **\n");
	printf("               **                 8.按日期                    **\n");
	printf("               **                                             **\n");
	printf("               **             //按`返回上一级~//              **\n");
	printf("               *************************************************\n");



	char select = -1;
	while (select)
	{
		select = _getch();
		switch (select)
		{
		case '1':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_index);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '2':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_name);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '3':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_sex);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '4':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_age);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '5':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_idnum);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '6':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_phone);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '7':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_vip);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case '8':
			Sort(usm->user, sizeof(Person), usm->sz + 1, Person_ymd);
			printf(GREEN_TEXT"              >>>>>>>>>>>>排序成功！<<<<<<<<<<\n");
			select = 0;
			system("pause");
			break;
		case RETURN:
			select = 0;
			break;
		default:
			break;
		}
	}
	system("cls");
}













