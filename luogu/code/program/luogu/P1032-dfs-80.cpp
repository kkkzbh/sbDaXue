



#include<iostream>
#include<array>
#include<string>

constexpr int size{6 + 3};
std::string s1,s2;
std::array<std::array<std::string,2>,size> cv;
int top{1};
int cnt;
int ans{1 << 30};

void dfs(int i)
{
    if(s1 == s2)
    {
        ans = std::min(ans,cnt);
        return;
    }

    if(i > 10) return;
    for(int _{1}; _ != top;++_)
    {
        decltype(s1.size()) x{};
        while((x = s1.find(cv[_][0]),x) != std::string::npos)
        {
            s1.replace(x,cv[_][0].size(),cv[_][1]);
            ++cnt;
            dfs(i + 1);
            s1.replace(x,cv[_][1].size(),cv[_][0]);
            --cnt;
            ++x;
        }
    }
}

int main()
{
    std::cin >> s1 >> s2;
    while(std::cin >> cv[top][0] >> cv[top][1]) ++top;
    dfs(1);
    if(ans != 1 << 30) std::cout << ans;
    else std::cout << "NO ANSWER!";

    return 0;
}