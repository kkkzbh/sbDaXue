

#ifdef P1478

#include<iostream>
#include<array>
#include<algorithm>
constexpr int size = 5000 + 10;

struct apple
{
    int heigh;
    int consume;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n,s;
    std::cin >> n >> s;
    std::array<apple,size> G = {0};
    int a,b;
    std::cin >> a >> b;
    int v = a + b;
    for(int i = 1; i <=n ;++i)
    {
        std::cin >> G[i].heigh >> G[i].consume;
    }
    std::sort(G.begin() + 1,G.begin() + 1 + n,[](const apple& a1,const apple& a2) -> bool
    {
        return a1.consume < a2.consume;
    });
    int count = 0;
    for(int i = 1;s && i <= n;++i)
    {
        if(G[i].heigh <= v && s >= G[i].consume)
        {
            ++count;
            s -= G[i].consume;
        }
    }
    std::cout << count;

    return 0;
}

#endif
