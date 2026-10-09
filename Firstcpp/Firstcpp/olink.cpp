


#include"link.h"


static void menu()
{
	printf("**************************\n");
	printf("******  1. EnLink    *****\n");
	printf("******  2. InLink    *****\n");
	printf("******  3. PrintLink *****\n");
	printf("******  4. Insert    *****\n");
	printf("******  5. Remove    *****\n");
	printf("**************************\n");
	printf("6.Exchange		");


	printf("\n");
}

pNote o_Link()
{
	oLink List = CreateLink();
	int n = 0;
	Elmtype tmp = 0;
	do
	{
		menu();
		scanf("%d", &n);
		switch (n)
		{
		case ENLINK:
			printf("输入要在末端链接的数据:>");
			std::cin >> tmp;
			EnLink(tmp, List);
			printf("链接成功！\n");
			break;
		case INLINK:
			printf("输入要在首端链接的数据:>");
			std::cin >> tmp;
			InLink(tmp, List);
			printf("链接成功！\n");
			break;
		case PRINTLINK:
			PrintLink(List);
			printf("\n");
			break;
		case INSERT:
			printf("输入链接数据和插入位置");
			std::cin >> tmp >> n;
			Insert(tmp, n, List);
			break;
		case REMOVE:
			RemoveLink(List);
			printf("已置空\n");
			break;
		case EXCHANGE:
			printf("请输入位置:>");
			cin >> n;
			Exchange((unsigned)n, List);
			printf("交换成功！\n");
			break;
		}
	} while (n);
	return List;
}


oLink CreateLink()
{
	oLink head = (oLink)malloc(sizeof(Note));
	if (head == NULL)
	{
		perror("Creatmalloc");
		return NULL;
	}
	head->Next = NULL;
	head->Note = 0;
	return head;
}

int isEmpty(oLink List)
{
	return List->Next == NULL;
}

pNote EnLink(Elmtype X,oLink List)
{
	pNote tmp = List;
	while (List->Next != NULL)
	{
		List = List->Next;
	}
	List->Next = (pNote)malloc(sizeof(Note));
	if (List->Next == NULL)
	{
		perror("EnLink");
		return NULL;
	}
	List->Next->Note = X;
	List->Next->Next = NULL;
	tmp->Note++;
	return List->Next;
}

pNote InLink(Elmtype X, oLink List)
{
	pNote tmp = List->Next;
	List->Next = (pNote)malloc(sizeof(Note));
	if (List->Next == NULL)
	{
		perror("Inlink");
		return NULL;
	}
	List->Next->Next = tmp;
	List->Next->Note = X;
	List->Note++;
	return List->Next;
}

void PrintLink(oLink List)
{
	pNote tmp = List;
	printf("----------------------------------------------------\n");
	while ((tmp = (tmp->Next)) != NULL)
	{
		printf("%-4d", tmp->Note);
	}
	printf("\n----------------------------------------------------\n");
}


pNote Insert(Elmtype X,int location,oLink List)
{
	if (location > List->Note)
	{
		printf("The location over the link length!\n");
		return NULL;
	}
	pNote tmp = (pNote)malloc(sizeof(Note));
	if (NULL == tmp)
	{
		perror("Insert");
		return NULL;
	}
	List->Note++;
	for (int i = 0; i < location-1; i++)
	{
		List = List->Next;
	}

	tmp->Note = X;
	tmp->Next = List->Next;
	List->Next = tmp;
	return tmp;
}


void RemoveLink(oLink List)
{
	while (List->Next != NULL)
	{
		pNote tmp = List->Next->Next;
		free(List->Next);
		List->Next = tmp;
	}
}

//如果对List->Next 赋值 也就破坏了链表 使用访问链表时 一定要用List
void PrintLost(oLink List1, oLink List2)
{
	Elmtype arr[TEST] = { 0 };
	int location = 0;
	int count = -1;
	while (List2->Next != NULL)
	{
		arr[++count] = List2->Next->Note;
		List2->Next = List2->Next->Next;
	}
	
	for (int i = 1,is = 0;i <= arr[count];i++)
	{
		if (i == arr[is])
		{
			printf("%-4d", List1->Next->Note);
			is++;
		}
		List1->Next = List1->Next->Next;
	}
}

void PrintLost_(oLink List1,oLink List2)
{
	int count = 1;
	List1 = List1->Next;
	List2 = List2->Next;
	while (List1 != nullptr && List2 != nullptr)
	{
		if (List2->Note == count++)
		{
			printf("%-4d", List1->Note);
			List2 = List2->Next;
		}
		List1 = List1->Next;
	}
}



//使用位置指针访问链表 有时是一个很好用的举措 至于开辟了空间 随便了
//为了一点点空间 非常不值得
//一个建议的方法是 要操纵几个链表元素 就使用几个位置指针(可以在此基础上尽可能少)
void Exchange(unsigned location,oLink List)
{
	if (location >= (unsigned)(List->Note))
	{
		printf("Location must less than length\n");
		return;
	}
	for (unsigned i = 0;i < location-1;i++)
	{
		List = List->Next;
	}		
	//注意函数的值传递，所以不要直接更改List的值，只能前调一位指针更改它的Next
	pNote tmp = List->Next;	//交换1与2(location为1的位置)	//->0->1->2->3 保存 ->1
	List->Next = List->Next->Next;	//->0->2   0指向2
	pNote tmp2 = List->Next->Next;   //->0->2->3 保存->3
	List->Next->Next = tmp;			//利用保存的->1  让2->1  此时0->2->1->2->1........
	tmp->Next = tmp2;			//利用保存的->3 让1->3 此时0->2->1->3  交换成功
}//这里tmp名字起的不太好 最好起一个有象征的名字

void Exchange_(unsigned location, oLink List)
{
	if (location >= (unsigned)(List->Note))
	{
		printf("Location must less than length\n");
		return;
	}
	for (unsigned i = 0;i < location - 1;i++)
	{
		List = List->Next;
	}
	pNote P = List->Next;
	pNote AP = P->Next;
	List->Next = AP;
	P->Next = AP->Next;
	AP->Next = P;
}




//删除某位置的元素（参数为该位置上一位置的元素 单链表）
static void Del(pNote ptr)
{
	pNote tmp = ptr->Next->Next;
	free(ptr->Next);
	ptr->Next = tmp;
}

oLink Intersection(oLink List1,oLink List2)
{
	oLink tmp = List1;
	Elmtype a[100] = { 0 };
	while ((List2 = List2->Next) != NULL)
		a[List2->Note]++;
	while (List1->Next != nullptr)
	{
		if (!a[List1->Next->Note])
			Del(List1);
		else 
			List1 = List1->Next;
	}
	return tmp;
}

oLink Intersection_(oLink List1, oLink List2)
{
	oLink tmp = CreateLink();
	List1 = List1->Next;
	List2 = List2->Next;
	while (NULL != List1 && NULL != List2)
	{
		if (List1->Note == List2->Note)
		{
			EnLink(List1->Note, tmp);
			List1 = List1->Next;
			List2 = List2->Next;
		}
		else if (List1->Note > List2->Note)
		{
			List2 = List2->Next;
		}
		else
		{
			List1 = List1->Next;
		}
	}
	//for (;List1;List1->Next);
	//for (;List2;List2->Next);
	return tmp;
}

pNote Insert_(Elmtype x, pNote p)
{
	pNote px = (pNote)malloc(sizeof(Note));
	if (nullptr == px)
	{
		perror("Insert_\n");
		return nullptr;
	}
	px->Note = x;
	pNote tmp = p->Next;
	p->Next = px;
	px->Next = tmp;
	return px;
}