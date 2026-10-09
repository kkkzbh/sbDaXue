
#ifdef P1035

#include<cstdio>

int main()
{
    int k;
    scanf("%d",&k);
    double sum = 0;
    int i;
    for(i = 1; sum <= k ;++i)
    {
        sum += 1.0/i;
    }
    printf("%d",i-1);
    return 0;
}


#endif