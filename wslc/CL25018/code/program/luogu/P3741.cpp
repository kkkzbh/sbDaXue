

#ifdef P3741

#include<iostream>
#include<string>


int main()
{
    int n;
    std::string s;
    std::cin >> n >> s;
    s = ' ' + s + ' ';
    int count = 0;
    int pos = -1;
    while((pos = s.find("VK",pos + 1)) != std::string::npos)
    {
        ++count;
    }
    for(int i = 1;i<=n;++i)
    {
        if(s[i] == 'V')
        {
            if(s[i-1] == 'V' && s[i+1] != 'K')
            {
                ++count;
                break;
            }
        }
        else
        {
            if(s[i-1] != 'V' && s[i+1] == 'K')
            {
                ++count;
                break;
            }
        }
    }
    std::cout << count;

    return 0;
}

#endif
