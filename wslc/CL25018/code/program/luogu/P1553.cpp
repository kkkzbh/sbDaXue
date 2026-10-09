

#ifdef P1553

#include<iostream>
#include<string>
#include<cctype>

int main()
{
    std::string s;
    std::cin >> s;
    std::string a;
    std::string b;
    char c = 0;
    int size = s.size();
    for(int i = 0;i<size;++i)
    {
        if(!isdigit(s[i]))
        {
            c = s[i];
            b = s.substr(i+1,size-i-1);
            break;
        }
        a += s[i];
    }
    int i;
    int end;
    for (end = a.size() - 1;a[end] == '0' && end >= 0;--end);
    if(end == -1) std::cout << 0;
    else
        for(i = end;i >= 0;--i)
        {
            std::cout << a[i];
        }
    if(c)
    {
        std::cout << c;
        if (c == '.')
        {
            for (i = 0; b[i] == '0' && i < b.size(); ++i);
            if (i == b.size()) std::cout << 0;
            else
                for (end = b.size() - 1; end >= i; --end)
                {
                    std::cout << b[end];
                }
        } else if (c == '/')
        {
            for (end = b.size() - 1;b[end] == '0' && end >= 0;--end);
            for(i = end;i >= 0;--i)
            {
                std::cout << b[i];
            }
        }
    }
    return 0;
}

#endif
