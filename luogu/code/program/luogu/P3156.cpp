


#include<iostream>

constexpr int size = 2 * 1e6 + 10;

int a[size];

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= n;++i)
        scanf("%d",a + i);
    while(m--)
    {
        int v;
        scanf("%d",&v);
        printf("%d\n",a[v]);
    }


    return 0;
}
