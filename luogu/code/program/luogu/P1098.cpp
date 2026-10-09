

#ifdef P1098

#include<iostream>
#include<string>
#include<cctype>
#include<algorithm>

void solve(std::string::size_type it,int p1,int p2,int p3,std::string& s)
{
    if(it == 0 || it == s.size() - 1) return;
    std::string tmp;
    if(isdigit(s[it - 1]) && isdigit(s[it + 1]))
    {
        if(s[it - 1] == s[it + 1]) return;
        else if(s[it - 1] + 1 == s[it + 1])
        {
            s.erase(it,1);
            return;
        }
        for(char c = static_cast<char>(s[it - 1] + 1);c < s[it + 1];++c)
        {
            for(int i = 1; i <= p2;++i)
            {
                tmp += p1 == 3 ? '*' : c;
            }
        }
        if(p3 == 2) std::reverse(tmp.begin(),tmp.end());
    }
    else if(islower(s[it - 1]) && islower(s[it + 1]))
    {
        if(s[it - 1] == s[it + 1]) return;
        else if(s[it - 1] + 1 == s[it + 1])
        {
            s.erase(it,1);
            return;
        }
        else
        {
            for (char c = static_cast<char>(s[it - 1] + 1); c < s[it + 1]; ++c)
            {
                for (int i = 1; i <= p2; ++i)
                {
                    tmp += p1 == 3 ? '*' : p1 == 2 ? static_cast<char>(toupper(c)) : c;
                }
            }
            if (p3 == 2) std::reverse(tmp.begin(), tmp.end());
        }
    }
    if(!tmp.empty())
    {
        s.replace(it,1,tmp);
    }
}

int main()
{
    int p1,p2,p3;
    std::cin >> p1 >> p2 >> p3;
    std::string s;
    std::cin >> s;
    decltype(s.size()) it = 0;
    while((it = s.find('-',it)) != std::string::npos)
    {
        solve(it++,p1,p2,p3,s);
    }
    std::cout << s;
    return 0;
}

#endif
