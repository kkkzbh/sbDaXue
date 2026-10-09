


#if 0

本题的一个剪枝方法为 使用一个表记录已产生的数据 来 剪枝
其实不难想到 平时的搜索都是对于整数的搜索 此时都会有一个vis类的数组用于剪枝
那么字符串也一样

#endif

#include<iostream>
#include<string>
#include<unordered_set>
#include<array>
#include<queue>
#include<utility>

constexpr int size = 10;

std::string s1,s2;
std::array<std::array<std::string,2>,size> cv;
std::size_t sz = 1;
std::size_t ans;
std::unordered_set<std::string> set(100);

bool bfs()
{
    std::queue<const std::string*> que;
    que.push(&s1);
    const std::string* last = que.front();
    const std::string* now = que.back();
    bool flag = false;
    while(!que.empty())
    {
        const std::string& str = *que.front();
        if(str == s2){ flag = true; break; }
        if(ans > 10) break;
        for(int i = 1; i != sz;++i)
        {
            std::size_t index = 0;
            while((index = str.find(cv[i][0],index)) != std::string::npos)
            {
                std::string tmp(str);
                tmp.replace(index,cv[i][0].size(),cv[i][1]);
                if(set.find(tmp) == set.end())
                {
                    auto p = set.insert(std::move(tmp));
                    que.push(&*p.first);
                    now = que.back();
                }
                ++index;
            }
        }
        if(&str == last)
        {
            last = now;
            ++ans;
        }
        que.pop();
    }
    return flag;
}

int main()
{
    std::cin >> s1 >> s2;
    std::string __tmp1,__tmp2;
    while(std::cin >> __tmp1 >> __tmp2) cv[sz][0] = __tmp1,cv[sz][1] = __tmp2,++sz;
    if(bfs()) std::cout << ans;
    else std::cout << "NO ANSWER!";


    return 0;
}