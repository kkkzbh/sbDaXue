

#ifdef P1085

#include<cstdio>

int main()
{
    int v1,v2;
    int unhappyday = 0;
    int time = 0;
    for(int i = 1;i<=7;++i)
    {
        scanf("%d%d",&v1,&v2);
        if(v1 + v2 > 8 && v1 + v2 > time)
        {
            unhappyday = i;
            time = v1 + v2;
        }
    }
    printf("%d",unhappyday);

    return 0;
}



#endif





