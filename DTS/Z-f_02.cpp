#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;

struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */

List Merge( List L1, List L2 )
{
    List L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    List it = L;
    List ita = L1->Next;
    List itb = L2->Next;
    L1->Next = L2->Next = NULL;
    while(ita && itb)
    {
        if(ita->Data < itb->Data)
        {
            List tmp = ita;
            ita = ita->Next;
            tmp->Next = it->Next;
            it->Next = tmp;
            it = tmp;
        }
        else
        {
            List tmp = itb;
            itb = itb->Next;
            tmp->Next = it->Next;
            it->Next = tmp;
            it = tmp;
        }
    }
    while(ita)
    {
        List tmp = ita;
        ita = ita->Next;
        tmp->Next = it->Next;
        it->Next = tmp;
        it = tmp;
    }
    while(itb)
    {
        List tmp = itb;
        itb = itb->Next;
        tmp->Next = it->Next;
        it->Next = tmp;
        it = tmp;
    }
    return L;
}