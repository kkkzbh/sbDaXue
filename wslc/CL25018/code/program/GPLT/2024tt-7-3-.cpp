

#include<iostream>
#include<string>
#include<cctype>

int main()
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    int n;
    std::cin >> n;
    std::cin.ignore();
    while(n--)
    {
        std::string s,ans,tmp;
        std::getline(std::cin,tmp);
        std::cout << tmp << '\n';
        for(auto&& i : tmp) if(i != 'I') i = tolower(i);
        s.push_back(' ');
        s.append(tmp);
        s.append(15,' ');
        ans.push_back(' ');
        size_t i{ 1 };
        while(i <= tmp.size() && s[i] == ' ') ++i;
        while(i <= tmp.size())
        {
            if(s[i] == ' ')
            {
                size_t pos = i;
                while(pos <= tmp.size() && s[++pos] == ' ');
                if(pos <= tmp.size() && isalnum(s[pos]))
                {
                    ans.push_back(' ');
                }
                i = pos;
            }
            else if(s[i] == 'I' && !isalpha(s[i - 1]) && !isalpha(s[i + 1]))
            {
                ans += "You";
                ++i;
            }
            else if(s.substr(i,2) == "me" && !isalpha(s[i - 1]) && !isalpha(s[i + 2]))
            {
                ans += "You";
                i += 2;
            }
            else
            {
                if(s[i] == '?')
                {
                    ans.push_back('!');
                    ++i;
                }
                else if(s[i] == 'I')
                {
                    ans.push_back(s[i++]);
                }
                else
                {
                    ans.push_back(static_cast<char>(tolower(s[i++])));
                }
            }
        }
        ans.push_back(' ');
        for(size_t index{ 1 }; index < ans.size() - 1; ++index)
        {
            index = ans.find("can you",index);
            if(index == std::string::npos) break;
            if(!isalnum(ans[index - 1]) && !isalnum(ans[index + 7]))
            {
                ans.replace(index,7,"I can");
            }
        }
        for(size_t index{ 1 }; index < ans.size() - 1; ++index)
        {
            index = ans.find("could you",index);
            if(index == std::string::npos) break;
            if(!isalnum(ans[index - 1]) && !isalnum(ans[index + 9]))
            {
                ans.replace(index,9,"I could");
            }
        }
        std::cout << "AI: ";
        for(size_t index{ 1 }; index < ans.size() - 1; ++index)
        {
            if(ans[index] == 'Y')
            {
                std::cout << 'y';
            }
            else
            {
                std::cout << ans[index];
            }
        }
        std::cout << '\n';
    }

    return 0;
}