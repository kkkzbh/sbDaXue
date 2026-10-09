

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

constexpr static int N{ 1000 + 2 };

struct node
{
    int t,c;
};

int t,n;
std::vector<node> a;
std::array<int,N> dp;

fun scan()
{
    int h1,m1,h2,m2;
    scanf("%d:%d",&h1,&m1);
    scanf("%d:%d",&h2,&m2);
    t = (h2 * 60) + m2 - (h1 * 60) - m1;
    scanf("%d",&n);
    for(int i : std::views::iota(0,n))
    {
        int vt,vc,vp;
        scanf("%d %d %d",&vt,&vc,&vp);
        int cnt{ vp ? vp : t / vt };
        for(int k{ 1 }; k <= cnt; k <<= 1)
        {
            a.emplace_back(k * vt,k * vc);
            cnt -= k;
        }
        if(cnt)
        {
            a.emplace_back(cnt * vt,cnt * vc);
        }
    }
}

fun solve()
{
    for(const auto [vt,vc] : a)
    {
        for(int j : std::views::iota(std::min(vt,t + 1),t + 1) | std::views::reverse)
        {
            dp[j] = std::max(dp[j],vc + dp[j - vt]);
        }
    }
    print("{}",dp[t]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(scan);
    std::invoke(solve);

    return 0;
}