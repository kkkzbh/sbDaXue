
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

int Person_Index(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return x1->index - x2->index;
}

int Person_Name(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->name, x2->name);
}

int Person_Sex(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->sex, x2->sex);
}

int Person_Age(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->age, x2->age);
}

int Person_Idnum(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->idnum, x2->idnum);
}

int Person_Phone(void* e1, void* e2)
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

int Person_Ymd(void* e1, void* e2)
{
	Person* x1 = (Person*)e1;
	Person* x2 = (Person*)e2;
	return cmp(x1->ymd, x2->ymd);
}