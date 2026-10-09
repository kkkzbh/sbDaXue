#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 2;
    int b = 1;
    while(b>0)
{
    a++;
    if(a%2==1 && a<=100)
    printf("%d\n",a);
}




    return 0;
}
