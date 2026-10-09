


//一个二叉搜索树 右侧放比根节点大于等于的数 第一行输入一个N 表示序列有N个数(N <= 100,数字 <= 2000)
//给定一个序列 打印层序遍历

//Sample Input
// 10
// 1 2 3 4 5 6 7 8 9 0

//Sample Output
//6 3 8 1 5 7 9 0 2 4


#ifdef __DEBUG__011
//*****************************text     one *****************************//
//对于给定的一序列 可以唯一确定一个完全二叉树
//如果想要把该完全二叉树调成完全二叉搜索树  应该如何处理?
//对于这一种搜索树而言 左边的都比根节点小 右边的都大于等于根节点
//那么根节点的值 只可能是 对序列从小到大排序后 第n个序列点的值 其中n为左子树的节点个数-1,这是不难理解的,左子树值都比根小,而右的都大于等于
//首先直接对序列排序 则可以按序唯一确定一个完全二叉树
//那么此时通过这个二叉树的大小 可以计算出 左子树的个数 那么就可以确定根的值在该序列的第几个点了
//得到根后 如果递归的处理(就是以根节点的值拆分左右两个序列)左子树和右子树 则左子树和右子树的序列同样也都是有序的
//对于左子树而言 如果有序列 则根就有值 那么首先该左序列所有的值都是左子树的可能取值
//那么就是同理，如何把该序列调成一个二叉搜索树 根本还是在于根的值则取决于左子树的左子树个数，然后去定根的值在该左序列的第几个数
//右子树同理 然后递归的处理问题  如果递归到某子树 是没有序列的 则结束递归

//本题首先把序列存到数组中 然后排序
//在调整过程中 这个数组的值不能改变，始终保留信息
//可以如下理解每个栈帧
//对于某个栈帧而言 对应了一个序列 和 根节点的位置
//这个序列的所有值 都是该序列树的结点全部可能取值  那么根结点的值 就是序列第n(左子树的个数) + 1 个值
//同时因为刚好是排好序的  那么该栈帧的左子树拿到的以n+1为分界点的左序列 都是该左子树的全部可能取值 然后同理递归
//右子树同理
//如果到达某个栈帧发现没有序列 则该栈帧存储的根节点的位置没有取值 如果序列只有1个数 显然根节点就是这个数

#include<cstdio>
#include<cmath>

#define MAX 105
#define LEFT(X) (2*(X) + 1)
#define RIGHT(X) (2 * (X) + 2)


void swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap(int& a,int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void insert_sort(int* a,int* b)
{
    if(a == b) return;
    int* it;
    int tmp;
    for(int* end = a+1;end != b;++end)
    {
        for(it = end,tmp = *end;it != a && tmp < *(it-1);--it)
        {
            *it = *(it - 1);
        }
        *it = tmp;
    }
}

int mediea3(int* a,int* b)
{
    int* mid = a +  (b-a)/2;
    if(*a > *mid) swap(a,mid);
    if(*a > *(b - 1)) swap(a,b-1);
    if(*mid > *(b-1)) swap(mid,b-1);
    if(b-2 != a) swap(mid,b-2);
    return *(b-2);
}

void quick_sort(int* a,int* b)
{
    static const int cutoff = (b-a)/4;
    if(b-a > cutoff)
    {
        int privot = mediea3(a,b);
        int* ita = a;
        int* itb = b-2;
        while(ita < itb)
        {
            while(*++ita < privot);
            while(*--itb > privot);
            if(ita >= itb) break;
            swap(ita,itb);
        }
        swap(ita,b-2);
        quick_sort(a,ita);
        quick_sort(ita + 1,b);
    }
    else
    {
        insert_sort(a,b);
    }
}

int pow2(int n)
{
    int i = 1;
    while(n--) i *= 2;
    return i;
}

int getLeftCount(int n)
{
    int H = static_cast<int>(log2(n + 1));
    int p = pow2(H);
    int X = n - p + 1 < p/2 ? n - p + 1 : p/2;
    return X + pow2(H-1) - 1;
}

int opt[MAX]{};

void solve(int* a,int* b,int root)
{
    if(a >= b) return;
    int n = getLeftCount(b - a);
    opt[root] = a[n];
    solve(a,a+n,LEFT(root));
    solve(a+n+1,b,RIGHT(root));
}

int main()
{
    int n;
    freopen("../data.dat","r",stdin);
    scanf("%d",&n);
    int a[MAX]{};
    for(int i = 0;i<n;++i)
    {
        scanf("%d",a+i);
    }
    quick_sort(a,a+n);
    solve(a,a+n,0);
    printf("%d",opt[0]);
    for(int i = 1;i<n;++i)
    {
        printf(" %d",opt[i]);
    }
    return 0;
}

#endif
