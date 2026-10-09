#pragma once

#include<cstdio>
#include<cctype>

constexpr std::size_t __BUFFER__SIZE = 200000;

//#define __BUFFER__SIZE (1 << 18) //1 << 15 = 32767

char __Buffer[__BUFFER__SIZE];
char* __Start = __Buffer,*__End = __Start;
inline char __Getchar()
{
    if(__Start == __End)
        __End = (__Start = __Buffer) + fread(__Buffer,1,__BUFFER__SIZE,stdin);
    return *__Start++;
}

inline bool read(int& v)
{
    int sign = 1,value = 0;
    bool flag{ false };
    char c = __Getchar();
    while(isspace(c)) c = __Getchar();
    if(c == '-') {sign = -1; c = __Getchar();}
    while(c >= '0' && c <= '9')
    {
        value = (value << 1) + (value << 3) + (c ^ 48);
        c = __Getchar();
        flag = true;
    }
    --__Start;
    v = sign * value;
    return flag;
}

inline bool read(char& c){ return __Getchar(); }


