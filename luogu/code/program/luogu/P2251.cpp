


#include<iostream>
#include<utility>
#include<deque>

int n,m;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m;
    std::deque<std::pair<int,int>> que;
    for(int i{ 1 },val; i <= n; ++i)
    {
        std::cin >> val;
        while(!que.empty() and val <= que.back().first)
            que.pop_back();
        if(!que.empty() and i - m == que.front().second)
            que.pop_front();
        que.emplace_back(val,i);
        if(i >= m)
            std::cout << que.front().first << '\n';
    }


    return 0;
}