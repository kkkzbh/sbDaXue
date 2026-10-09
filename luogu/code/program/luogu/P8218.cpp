
#ifdef P8218

#include<iostream>

constexpr int size = 1e5 + 10;

int a[size],prefix[size];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for(int i = 1;i <= n;++i)
    {
        std::cin >> a[i];
    }
    for(int i = 1;i <= n; ++i)
    {
        prefix[i] = prefix[i-1] + a[i];
    }
    int m;
    std::cin >> m;
    int l,r;
    for(int i = 1;i <= m;++i)
    {
        std::cin >> l >> r;
        std::cout << prefix[r] - prefix[l-1] << '\n';
    }



    return 0;
}



#endif









