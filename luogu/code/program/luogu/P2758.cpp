

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>

#define fun auto
template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    if constexpr(sizeof...(Args))
    {
        std::cout << std::vformat(fmts.get(), std::make_format_args(std::forward<Args>(args)...));
    }
    else
    {
        std::cout << fmts.get();
    }
}

constexpr static int N{ 2000 + 2 };
constexpr static int INF{ 0x3f3f3f3f };

std::string s1,s2;
std::array<std::array<int,N>,N> dp;

fun solve()
{
    std::cin >> s1 >> s2;

    //dp[i][j] min ->
    // s1[i - 1] == s2[j - 1] -> dp[i - 1][j - 1]
    // 1. -> dp[i - 1][j] + 1
    // 2. -> dp[i][j - 1] + 1
    // 3. -> dp[i - 1][j - 1] + 1

    for(int i : std::views::iota(1,static_cast<int>(s2.size()) + 1)){ dp[0][i] = i; }
    for(int i : std::views::iota(1,static_cast<int>(s1.size()) + 1)){ dp[i][0] = i; }

    for(int i : std::views::iota(1,static_cast<int>(s1.size()) + 1))
    {
        for(int j : std::views::iota(1,static_cast<int>(s2.size()) + 1))
        {
            if(s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = std::min
                                   ({
                                            dp[i - 1][j],
                                            dp[i][j - 1],
                                            dp[i - 1][j - 1],
                                    }) + 1;
            }
        }
    }

    print("{}",dp[s1.size()][s2.size()]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}