


#ifdef P1208

#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 2 * 1e6 + 10;

struct milk
{
    int price;
    int count;
};

std::array<milk,size> G;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    for(int i = 1; i <=m ;++i)
    {
        std::cin >> G[i].price >> G[i].count;
    }
    std::sort(G.begin() + 1,G.begin() + 1 + m,[](const milk& m1,const milk& m2) -> bool
    {
       return m1.price < m2.price;
    });
    int p = 0;
    for(int i = 1; n && i <= m;++i)
    {
        if(n >= G[i].count)
        {
            n -= G[i].count;
            p += G[i].price * G[i].count;
        }
        else
        {
            p += G[i].price * n;
            n = 0;
        }
    }
    std::cout << p;

    return 0;
}

#endif
