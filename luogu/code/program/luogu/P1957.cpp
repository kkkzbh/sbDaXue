

#ifdef P1957

#include<iostream>
#include<string>
#include<cctype>
char op[3] = {'+','-','*'};

int atoi(std::string& s)
{
    int x = 0;
    for(auto & it : s)
    {
        x *= 10;
        x += it - '0';
    }
    return x;
}

inline int cacu(int x,int y,char op)
{
    if('+' == op) return x + y;
    else if('-' == op) return x - y;
    else return x * y;
}

int length(int x,int y,int z,char c)
{
    int len = 0;
    if(!x) ++len;
    while(x)
    {
        x /= 10;
        ++len;
    }
    if(!y) ++len;
    while(y)
    {
        y /= 10;
        ++len;
    }
    if(z < 0 || !z) ++len;
    while(z)
    {
        z /= 10;
        ++len;
    }
    return len + 2;
}

int main()
{
    int n;
    std::cin >> n;
    char c;
    std::string left;
    int l,r;
    for(int i = 1;i<=n;++i)
    {
        std::cin >> left;
        if(isalpha(left[0]))
        {
            c = left[0];
            std::cin >> l;
        }
        else
        {
            l = atoi(left);
        }
        std::cin >> r;
        std::cout << l << op[c - 'a'] << r << '=' << cacu(l,r,op[c-'a']) << '\n';
        std::cout << length(l,r,cacu(l,r,op[c - 'a']),c) << '\n';
    }

    return 0;
}

#endif
