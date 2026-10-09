

#ifdef P5019

#include<iostream>
#include<array>

constexpr int size = 1e5 + 10;

int solve(std::array<int,size>& G,int st,int ed)
{
    if(st == ed) return 0;
    int min = G[st];
    int mini = st;
    for(int i = st + 1; i != ed;++i)
    {
        if(G[i] < min)
        {
            min = G[i];
            mini = i;
        }
    }
    for(int i = st; i != ed;++i)
    {
        G[i] -= min;
    }
    return min + solve(G,st,mini) + solve(G,mini + 1,ed);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::array<int,size> G = {0};
    for(int i = 1; i <= n;++i)
    {
        std::cin >> G[i];
    }
    int ret = solve(G,1,n+1);
    std::cout << ret;

    return 0;
}

#endif
