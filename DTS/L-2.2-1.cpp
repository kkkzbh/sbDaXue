

#include<stdio.h>
#include<stdlib.h>

typedef struct Node *PtrToNode;
struct Node {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;
/* Nodes are sorted in decreasing order of exponents.*/

int main()
{


    return 0;
}

typedef struct Node node;
Node* New(int Cof,int Exp)
{
    node* it = (node*)malloc(sizeof(node));
    it->Coefficient = Cof;
    it->Exponent = Exp;
    it->Next = NULL;
    return it;
}

Polynomial Add( Polynomial a, Polynomial b )
{
    typedef struct Node node;
    node* ita = a;
    node* itb = b;
    node* head = (node*)malloc(sizeof(node));
    node* it = head;
    while(ita && itb)
    {
        if(ita->Exponent > itb->Exponent)
        {
            it->Next = New(ita->Coefficient,ita->Exponent);
            it = it->Next;
            ita = ita->Next;
        }
        else if(ita->Exponent < itb->Exponent)
        {
            it->Next = New(itb->Coefficient,itb->Exponent);
            it = it->Next;
            itb = itb->Next;
        }
        else
        {
            if(ita->Coefficient + itb->Coefficient)
            {
                it->Next = New(ita->Coefficient + itb->Coefficient,ita->Exponent);
                it = it->Next;
            }
            ita = ita->Next;
            itb = itb->Next;
        }
    }
    while(ita)
    {
        it->Next = New(ita->Coefficient,ita->Exponent);
        it = it->Next;
        ita = ita->Next;
    }
    while(itb)
    {
        it->Next = New(itb->Coefficient,itb->Exponent);
        it = it->Next;
        itb = itb->Next;
    }
    return head;
}