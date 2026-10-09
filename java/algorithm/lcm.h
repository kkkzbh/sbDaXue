#pragma once
#include"gcd.h"

inline int lcm(int a,int b)
{
    return a*b/gcd(a,b);
}

