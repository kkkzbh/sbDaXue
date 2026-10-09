

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
#include<unordered_map>

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

std::array<std::string,7 + 2> map{
        { "---","--x","-w-","-wx","r--","r-x","rw-","rwx" }
};

fun solve()
{
    std::string s,ans;
    std::cin >> s;
    for(const auto ch : s)
    {
        ans += map[ch ^ 48];
    }
    print("{}\n",ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--)
    {
        std::invoke(solve);
    }

    return 0;
}