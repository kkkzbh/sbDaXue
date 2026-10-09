

#ifdef P2367

#include<iostream>
#define min(A,B) ((A) > (B) ? (B) : (A))

constexpr int size = 5*1e6 + 10;

int n,p;
int g[size];
int prefix[size];
int d[size];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> p;
    for(int i = 1;i<=n;++i)
    {
        std::cin >> g[i];
    }
    for(int i = 1;i<=n;++i)
    {
        d[i] = g[i] - g[i-1];
    }
    int x,y,z;
    for(int i = 1;i<=p;++i)
    {
        std::cin >> x >> y >> z;
        d[x] += z;
        d[y+1] -= z;
    }
    int m = 1000000;
    for(int i = 1;i<=n;++i)
    {
        prefix[i] = prefix[i-1] + d[i];
        m = min(prefix[i],m);
    }

    std::cout << m;

    return 0;
}


#endif









