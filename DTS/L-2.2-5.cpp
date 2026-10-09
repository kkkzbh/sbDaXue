


#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( GetOp() ) {
            case push:
                scanf("%d %d", &Sn, &X);
                if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
                break;
            case pop:
                scanf("%d", &Sn);
                X = Top_Pop(S, Sn);
                if ( X==ERROR ) printf("Stack %d is Empty!\n", Sn);
                break;
            case end:
                PrintStack(S, 1);
                PrintStack(S, 2);
                done = 1;
                break;
        }
    }
    return 0;
}

/* Your function will be put here */

typedef struct StackRecord stack;

Stack CreateStack( int MaxElements )
{
    stack* stk = (stack*)malloc(sizeof(stack));
    stk->Capacity = MaxElements;
    stk->Top1 = -1;
    stk->Top2 = MaxElements;
    stk->Array = (ElementType*)malloc(MaxElements * sizeof(ElementType));
    return stk;
}
int IsEmpty( Stack S, int Stacknum )
{
    if (Stacknum == 1)
    {
        if(S->Top1 == -1)
        {
            return 1;
        }
    }
    else
    {
        if(S->Top2 == S->Capacity)
        {
            return 1;
        }
    }
    return 0;
}
int IsFull( Stack S )
{
    if(S->Top1 + 1 == S->Top2) return 1;
    return 0;
}
int Push( ElementType X, Stack S, int Stacknum )
{
    if(IsFull(S))
    {
        return 0;
    }
    if(Stacknum == 1) S->Array[++S->Top1] = X;
    else S->Array[--S->Top2] = X;
    return 1;
}
ElementType Top_Pop( Stack S, int Stacknum )
{
    if(IsEmpty(S,Stacknum)) return ERROR;
    ElementType X;
    if(Stacknum == 1) X = S->Array[S->Top1--];
    else X = S->Array[S->Top2++];
    return X;
}