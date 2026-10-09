


#include<iostream>
#include<string>
#include<cmath>

std::string solve(int n)
{
    if(n == 1)
    {
        return "";
    }
    if(n == 0)
    {
        return "(0)";
    }
    constexpr int size = 31 + 10;
    int m = 1 << 30;
    int v = 30;
    int num[size],top = 0;
    while(m)
    {
        if(n & m)
        {
            num[top++] = v;
        }
        --v;
        m >>= 1;
    }
    std::string s;
    s += "(";
    for(int i = 0; i != top;++i)
    {
        s += "2";
        s += solve(num[i]);
        if(i != top - 1) s += '+';
        //s += "+"[i == top - 1];

    }
    s += ")";
    return s;
}

int main()
{
    int n;
    std::cin >> n;
    std::string s = solve(n);
    int sz = s.size() - 1;
    for(int i = 1; i != sz;++i)
    {
        std::cout << s[i];
    }

    return 0;
}
