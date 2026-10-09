

#ifdef P1106

#include<iostream>
#include<string>
#include<algorithm>


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string s;
    std::cin >> s;
    int n;
    std::cin >> n;
    int st = 0;
    while(st < s.size() - 1 && s[st] == '0') ++st;
    for(int i = st + 1; n && i < s.size();)
    {
        if(s[i] < s[i - 1])
        {
            s.erase(i - 1,1);
            --n;
            --i;
        }
        else ++i;
    }
    s.resize(std::max(static_cast<int>(s.size() - n > 0 ? s.size() - n : 0),st));
    while(s[st] == '0') ++st;
    s.size() == st ? std::cout << 0 : std::cout << s.c_str() + st;

    return 0;
}

#endif