

#ifdef P1046

#include<cstdio>

int main()
{
    int dis[10]{};
    for(int i = 0;i<10;++i)
    {
        scanf("%d",&dis[i]);
    }
    int h;
    scanf("%d",&h);
    h += 30;
    int count = 0;
    for(int i = 0;i<10;++i)
    {
        if(h >= dis[i]) ++count;
    }
    printf("%d",count);

    return 0;
}


#endif