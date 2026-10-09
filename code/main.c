#include<stdio.h>
#include<stdlib.h>

int Add(int x ,int y);

int main()
{
    printf("Hello world\n");
    int n = 5;
    int a[n];
    a[0] = 1;
    printf("%d\n",a[0]);
    int x = Add(a[0],n);
    printf("%d\n",x);

    return 0;
}


