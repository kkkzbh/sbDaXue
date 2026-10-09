

#ifdef P1867

#include<cstdio>
#define MAXHP 10.0

int main()
{
    double hp = MAXHP;
    int i;
    scanf("%d",&i);
    int exp = 0;
    double dhp;
    int dexp;
    while(i--)
    {
        scanf("%lf%d",&dhp,&dexp);
        hp -= dhp;
        if(hp <= 0) break;
        else if(hp > 10.0) hp = 10.0;
        exp += dexp;
    }
    i = 1;
    int lv = 0;
    while(exp >= i)
    {
        exp -= i;
        ++lv;
        i *= 2;
    }
    printf("%d %d",lv,exp);

    return 0;
}

#endif