


#include<iostream>
#include<array>
#include<algorithm>

constexpr int N{ 120 + 2 };

std::array<std::array<int,N>,N> a;
std::array<std::array<int,N>,N> prefix;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
        for(int j{ 1 }; j <= n; ++j)
        {
            std::cin >> a[i][j];
            prefix[i][j] = prefix[i][j - 1] + prefix[i - 1][j] - prefix[i - 1][j - 1] + a[i][j];
        }
    int ans{};
    for(int i{ 1 }; i <= n; ++i)
        for(int j{ 1 }; j <= n; ++j)
            for(int m{ i }; m <= n; ++m)
                for(int k{ j }; k <= n; ++k)
                    ans = std::max(ans,prefix[m][k] - prefix[m][j - 1] - prefix[i - 1][k] + prefix[i - 1][j - 1]);
    std::cout << ans;

    return 0;
}