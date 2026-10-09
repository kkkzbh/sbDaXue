#pragma once

void Sort(void* dst, size_t block, size_t sz, int (*f)(void* e1, void* e2));
static void Swap(void* e1, void* e2,size_t block);
int INT(void* e1, void* e2);


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
		if(min != i)
		Swap((char*)dst + (i * block), (char*)dst + (min * block),block);
	}
}

static void Swap(void* e1, void* e2,size_t block)
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