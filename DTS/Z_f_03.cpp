

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ) /* 先序遍历，由裁判实现，细节不表 */
{
    if(BT)
    {
        printf(" %d",BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
void InorderTraversal( BinTree BT )  /* 中序遍历，由裁判实现，细节不表 */
{
    if(BT)
    {
        InorderTraversal(BT->Left);
        printf(" %d",BT->Data);
        InorderTraversal(BT->Right);
    }
}

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */

BinTree Insert( BinTree BST, ElementType X )
{
    typedef struct TNode Node;
    if(!BST)
    {
        BST = (Node*)malloc(sizeof(Node));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
        return BST;
    }
    Node* it = BST;
    int find = 0;
    while(!find)
    {
        if(it->Data == X) find = 1;
        else if(X > it->Data)
        {
            if(it->Right) it = it->Right;
            else
            {
                it->Right = (Node*)malloc(sizeof(Node));
                it->Right->Data = X;
                it->Right->Left = NULL;
                it->Right->Right = NULL;
                find = 1;
            }
        }
        else
        {
            if(it->Left) it = it->Left;
            else
            {
                it->Left = (Node*)malloc(sizeof(Node));
                it->Left->Data = X;
                it->Left->Left = NULL;
                it->Left->Right = NULL;
                find = 1;
            }
        }
    }
    return BST;
}

BinTree Delete( BinTree BST, ElementType X )
{
    typedef struct TNode Node;
    Node** lastv = &BST;
    Node* it = BST;
    while(it && it->Data != X)
    {
        if(X > it->Data)
        {
            lastv = &it->Right;
            it = it->Right;
        }
        else
        {
            lastv = &it->Left;
            it = it->Left;
        }
    }
    if(!it)
    {
        printf("Not Found\n");
        return BST;
    }
    if(it->Left && it->Right)
    {
        Node* tmp = it->Right;
        lastv = &it->Right;
        while(tmp->Left)
        {
            lastv = &tmp->Left;
            tmp = tmp->Left;
        }
        it->Data = tmp->Data;
        *lastv = tmp->Right;
        free(tmp);
    }
    else if(it->Left)
    {
        *lastv = it->Left;
        free(it);
    }
    else
    {
        *lastv = it->Right;
        free(it);
    }
    return BST;
}

Position Find( BinTree BST, ElementType X )
{
    typedef struct TNode Node;
    Node* it = BST;
    while(it && it->Data != X)
    {
        if(X > it->Data) it = it->Right;
        else it = it->Left;
    }
    return it;
}

Position FindMin( BinTree BST )
{
    typedef struct TNode Node;
    if(!BST) return NULL;
    Node* it = BST;
    while(it->Left) it = it->Left;
    return it;
}

Position FindMax( BinTree BST )
{
    typedef struct TNode Node;
    if(!BST) return NULL;
    Node* it = BST;
    while(it->Right) it = it->Right;
    return it;
}