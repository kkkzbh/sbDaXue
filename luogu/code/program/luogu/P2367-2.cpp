

#include<iostream>
#include<array>

constexpr int N{ 5000000 + 2 };

std::array<int,N> a;
std::array<int,N> diff;


int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n,p;
    std::cin >> n >> p;
    for(int i{ 1 }; i <= n; ++i)
        std::cin >> a[i];
    while(p--)
    {
        int x,y,z;
        std::cin >> x >> y >> z;
        diff[x] += z;
        diff[y + 1] -= z;
    }
    int ans{ 2147483647 };
    for(int i{ 1 }; i <= n; ++i)
    {
        diff[i] += diff[i - 1];
        a[i] += diff[i];
        ans = std::min(ans,a[i]);
    }
    std::cout << ans;

    return 0;
}