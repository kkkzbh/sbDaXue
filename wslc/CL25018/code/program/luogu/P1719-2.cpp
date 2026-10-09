

#include<iostream>
#include<array>

constexpr int N{ 120 + 2};

std::array<std::array<int,N>,N> a;
std::array<std::array<int,N>,N> prefix;
std::array<int,N> m;
int n;

void build(int a,int b)
{
    for(int i{ 1 }; i <= n; ++i)
        m[i] = prefix[i][b] - prefix[i][a - 1];
}

int solve()
{
    int val{};
    int ans{};
    for(int i{ 1 }; i <= n; ++i)
    {
        val = std::max(0,m[i] + val);
        ans = std::max(val,ans);
    }
    return ans;
}

int main()
{
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
        for(int j{ 1 }; j <= n; ++j)
            std::cin >> a[i][j];
    for(int j{ 1 }; j <= n; ++j)
        for(int i{ 1 }; i <= n; ++i)
            prefix[j][i] = prefix[j][i - 1] + a[i][j];

    int ans{};
    for(int i{ 1 }; i <= n; ++i)
        for(int j{ i }; j <= n; ++j)
        {
            build(i,j);
            ans = std::max(ans,solve());
        }
    std::cout << ans;

    return 0;
}