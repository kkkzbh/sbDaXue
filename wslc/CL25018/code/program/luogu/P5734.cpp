

#ifdef P5734

#include<iostream>
#include<string>

int substr(const std::string& s,const std::string& sub)
{
    int size = s.size();
    int subsize = sub.size();
    for(int i = 0;i<size;++i)
    {
        int it = 0;
        while(s[i + it] == sub[it])
        {
            if(it + 1 == subsize) return i;
            ++it;
        }
    }
    return -1;
}

int main()
{
    int q;
    std::string s;
    std::cin >> q >> s;
    int a,b;
    int select = 0;
    for(int i = 1;i<=q;++i)
    {
        std::cin >> select;
        std::string tmp;
        switch(select)
        {
            case 1:
            {

                std::cin >> tmp;
                s += tmp;
                std::cout << s << '\n';
                break;
            }
            case 2:
            {
                std::cin >> a >> b;
                for (int i = a; i < a + b; ++i)
                {
                    tmp += s[i];
                }
                s = tmp;
                std::cout << s.c_str() << '\n';
                break;
            }
            case 3:
            {
                std::cin >> a >> tmp;
                std::string str;
                for (int i = a; i < s.size(); ++i)
                {
                    str += s[i];
                }
                s.resize(a);
                s += tmp;
                s += str;
                std::cout << s.c_str() << '\n';
                break;
            }
            case 4:
            {
                std::cin >> tmp;
                std::cout << substr(s, tmp) << '\n';
                break;
            }
        }
    }

    return 0;
}

#endif
