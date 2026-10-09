

#ifdef P1597

#include<iostream>
#include<string>
#include<cctype>

int a,b,c;
int tmp;

int& varible(char chr)
{
    if(chr == 'a') return a;
    if(chr == 'b') return b;
    if(chr == 'c') return c;
    tmp = chr - '0';
    return tmp;
}

int main()
{
    char lv,rv;
    do
    {
        if(2 == scanf("%c:=%c",&lv,&rv))
        {
            varible(lv) = varible(rv);
        }
    }while(getchar() == ';');
    printf("%d %d %d",a,b,c);

    return 0;
}

#endif
