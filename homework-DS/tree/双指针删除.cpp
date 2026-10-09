


#include<stdio.h>


#define SIZE 1000000
#define and &&
typedef struct list list;
struct list
{
    int a[SIZE];
    int n;
};

list L = { 1,1,2,2,3,4,
           5,6,7,7,8,9,
           10,10,11,12 ,
        .n = 16 };

int is_del(const int* i,list* A)
{
    return i != A->a and *i == *(i - 1);
}

int is_del2(int i,list* A,int x,int y)
{
    return i >= x and i <= y;
}

void del(list* A)
{
    int* l = A->a,*r = l,*end = A->a + A->n;
    while(r != end)
    {
        if(is_del(r,A))
        {
            ++r;
        }
        else
        {
            *l++ = *r++;
        }
    }
    A->n = l - A->a;
}

int main()
{
    del(&L);
    for(int i = 0; i != L.n; ++i)
    {
        printf("%d ",L.a[i]);
    }

    return 0;
}