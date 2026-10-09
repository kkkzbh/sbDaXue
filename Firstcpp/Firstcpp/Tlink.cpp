

#include "link.h"


static void menu()
{
	printf("1.Push\t\t\t2.Print\n");
	printf("3.Swap\t\t\t4.Print2\n");

}

Pnote t_link()
{
	Pnote List = CreateTlink();


	int n = 0;
	Elment x = 0;
	Push(9, List);
	Push(7, List);
	Push(5, List);
	Push(3, List);
	Push(1, List);

	do
	{
		menu();
		printf("请选择:>");
		cin >> n;
		switch (n)
		{
		case PUSH:
			printf("请输入插入元素:>");
			cin >> x;
			Push(x, List);
			break;
		case PRINT:
			Print(List);
			break;
		case SWAP:
			printf("请输入要交换的位置:>");
			cin >> n;
			Swap(n, List);
			break;
		case PRINT2:
			Print2(List);
			break;
		}

	} while (n);


	return List;
}


Pnote CreateTlink()
{
	Pnote head = (Pnote)malloc(sizeof(Tnote));
	if (nullptr == head)
	{
		perror("Create Tlink");
		return nullptr;
	}
	head->Note = 0;
	head->Next = nullptr;
	head->Last = nullptr;
	return head;
}


Pnote Push(Elment n,Pnote List)
{
	Pnote tmp = List->Next;
	List->Next = (Pnote)malloc(sizeof(Tnote));
	if (nullptr == List->Next)
	{
		perror("Push");
		return nullptr;
	}
	List->Next->Note = n;
	List->Next->Next = tmp;
	List->Next->Last = nullptr;
	if (nullptr != tmp)
	tmp->Last = List->Next;
	List->Note++;
	return List->Next;
}

void Print(Pnote List)
{
	printf("----------------------------------------------------\n");
	while ((List = List->Next) != nullptr)
	{
		cout << List->Note <<"      ";
	}
	cout << endl;
	printf("----------------------------------------------------\n");
}

void Swap(unsigned location,Pnote List)
{
	for (unsigned i = 0;i < location - 1;i++)
	{
		List = List->Next;
	}
	Pnote Ntmp1 = List->Next;
	List->Next = List->Next->Next;
	List->Next->Last = List;
	Pnote Ntmp2 = List->Next->Next;
	List->Next->Next = Ntmp1;
	Ntmp1->Next = Ntmp2;
	Ntmp1->Last = List->Next;
	Ntmp2->Last = Ntmp1;
}

void Swap_(unsigned location, Pnote List)
{
	for (unsigned i = 0;i < location - 1;i++)
	{
		List = List->Next;
	}
	Pnote P = List->Next;
	Pnote AP = P->Next;
	List->Next = AP;
	P->Next = AP->Next;
	AP->Next = P;
	AP->Last = List;
	P->Last = AP;
	if (P->Next != nullptr)
	{
		P->Next->Last = P;
	}
}

void Print2(Pnote List)
{
	printf("----------------------------------------------------\n");
	while ((List = List->Next) != nullptr)
	{
		printf("%-4d", List->Note);
	}
	printf("\n----------------------------------------------------\n");
}