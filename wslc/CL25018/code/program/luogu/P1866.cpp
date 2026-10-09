

#include<iostream>
#include<array>
#include<algorithm>

constexpr std::size_t mod{ 1000000000 + 7 };
constexpr int N{ 50 + 2 };
constexpr int M_size{ 1000 + 2 };

std::array<int,M_size> a;

int main()
{
    std::size_t ans{ 1 };
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
        std::cin >> a[i];
    std::sort(a.begin() + 1,a.begin() + 1 + n);
    for(int i{ 1 }; i <= n; ++i)
    {
        if(a[i] - i + 1 < 1)
        {
            ans = 0;
            break;
        }
        ans *= (a[i] - i + 1);
        ans %= mod;
    }
    std::cout << ans;

    return 0;
}