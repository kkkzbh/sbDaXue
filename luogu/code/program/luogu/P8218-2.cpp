

#include<iostream>
#include<array>

constexpr int N{ 100000 + 2 };

std::array<int,N> a;
std::array<int,N> prefix;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
    {
        std::cin >> a[i];
        prefix[i] = prefix[i - 1] + a[i];
    }
    int m;
    std::cin >> m;
    for(int i{}; i != m; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        std::cout << prefix[y] - prefix[x - 1] << '\n';
    }


    return 0;
}