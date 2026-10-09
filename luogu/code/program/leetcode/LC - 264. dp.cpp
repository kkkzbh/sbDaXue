
#include<bits/stdc++.h>

struct Solution
{

    int nthUglyNumber(int n)
    {
        std::vector<int> a(n + 2);
        a[1] = 1;
        for(int i{ 2 },i2{ 1 },i3{ 1 },i5{ 1 }; i <= n; ++i)
        {
            int v1{ a[i2] * 2 };
            int v2{ a[i3] * 3 };
            int v3{ a[i5] * 5 };
            int mv{ std::min({ v1,v2,v3 }) };
            if(mv == v1) ++i2;
            if(mv == v2) ++i3;
            if(mv == v3) ++i5;
            a[i] = mv;
        }
        return a[n];
    }
};