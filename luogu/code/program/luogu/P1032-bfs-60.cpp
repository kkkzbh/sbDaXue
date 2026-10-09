



#include<iostream>
#include<array>
#include<string>
#include<queue>
#include<utility>

constexpr int size{6 + 3};
std::string s1,s2;
std::array<std::array<std::string,2>,size> cv;
int top{1};
int cnt;

void bfs()
{
    std::queue<std::string> que;
    que.push(s1);
    std::string* last = &que.front();
    std::string* now = last;
    while(!que.empty() && cnt <= 10)
    {
        std::string& str = que.front();
        if(str == s2) break;
        for(int i = 1; i != top;++i)
        {
            decltype(s1.size()) sz{};
            while((sz = str.find(cv[i][0],sz)) != std::string::npos)
            {
                std::string tmp = str;
                tmp.replace(sz,cv[i][0].size(),cv[i][1]);
                que.push(std::move(tmp));
                now = &que.back();
                ++sz;
            }
        }
        if(&str == last)
        {
            last = now;
            ++cnt;
        }
        que.pop();
    }
}

int main()
{
    std::cin >> s1 >> s2;
    while(std::cin >> cv[top][0] >> cv[top][1]) ++top;
    bfs();
    if(cnt <= 10) std::cout << cnt;
    else std::cout << "NO ANSWER";

    return 0;
}