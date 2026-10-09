

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

using uint64 = unsigned long long;

constexpr static int N{ 40 + 2 };
constexpr static int N2{ 100000 + 2 };
constexpr static int N3{ 10000 + 2 };

struct node
{
    fun friend operator==(const node& n1,const node& n2) -> bool
    {
        return n1.i == n2.i and n1.k == n2.k and n1.val == n2.val;
    }
    int i,k,val;
};

namespace std
{
    template<>
    struct hash<node>
    {
        fun operator()(const node& n) const -> uint64
        {
            return (n.i * 3) + (n.val << 1) + n.k;
        }
    };
}

std::string s;
int n;
//std::array<std::array<std::array<int,N3>,N2>,N> dp;
std::unordered_map<node,int> dp;

fun dfs(int i,int k,int val) -> int
{
    if(i == s.size())
    {
        return val == k ? 0 : -1;
    }
    if((val * 10 + s[i] ^ 48) > k)
    {
        return -1;
    }
    auto it{ dp.find({ i,k,val }) };
    if(it != dp.end())
    {
        return it->second;
    }
    return dp[{ i,k,val }] = std::min
            (
                    [=]
                    {
                        int ret{ dfs(i + 1,k - (val * 10 + s[i] ^ 48),0) };
                        return ret == -1 ? std::numeric_limits<int>::max() : ret + 1;
                    }(),
                    [=]
                    {
                        int ret{ dfs(i + 1, k, val * 10 + s[i] ^ 48) };
                        return ret == -1 ? std::numeric_limits<int>::max() : ret;
                    }()
            );
}

fun solve()
{
    std::cin >> s >> n;
    int ret{ dfs(0,n,0) };
    print("{}",ret == std::numeric_limits<int>::max() ? -1 : ret);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}