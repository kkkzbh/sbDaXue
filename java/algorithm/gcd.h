#pragma once

int gcd(int a,int b)
{
    if(a <= 0 || b <= 0)
        return -1;
    int max = a > b ? a : b;
    int min = a > b ? b : a;
    int tmp = 0;
    while(min)
    {
        tmp = max % min;
        max = min;
        min = tmp;
    }
    return max;
}