

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<deque>
#include<queue>
#include<cassert>
#include<stack>
#include<optional>
#include<array>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<set>

#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define let auto

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif



template<typename T = int>
struct fenwick
{
    template<std::integral I>
    explicit fenwick(I n) noexcept : a(std::vector<T>(n)) {}

    [[nodiscard]]
    fun size() const noexcept -> int
    { return a.size(); }

    fun add(int i,T v) noexcept
    {
        for(++i; i <= a.size(); i += i & -i)
        {
            a[i - 1] += v;
        }
    }

    [[nodiscard]]
    fun sum(int i) const noexcept -> T
    {
        T ret{};
        for(++i; i; i -= i & -i)
        {
            ret += a[i - 1];
        }
        return ret;
    }

    [[nodiscard]]
    fun sum(int l,int r) const noexcept -> T
    {
        return sum(r) - sum(l - 1);
    }

    fun operator()(int i) const noexcept -> T
    {
        return sum(i);
    }

    fun operator()(int l,int r) const noexcept -> T
    {
        return sum(l,r);
    }

    fun clear() noexcept
    {
        std::ranges::fill(a,T{});
    }

    [[nodiscard]]
    fun select(T k) const noexcept -> int = delete;

    std::vector<T> a;
};

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

class Solution {
public:
    int minMovesToMakePalindrome(std::string& s)
    {
        std::ranges::for_each(s,[](char& c){ c -= 'a'; });
        int n = s.size();
        std::vector<int> to(n);
        std::vector<std::deque<int>> list(26);
        fenwick fw{ n };
        for(int i : std::views::iota(0,n)) {
            fw.add(i,1);
        }
        for(int i{}; i != n; ++i) {
            list[s[i]].push_back(i);
        }
        std::vector<bool> vis(n);
        for(int i : std::views::iota(0,n)) {
            if(vis[i]) {
                continue;
            }
            if (list[s[i]].size() != 1) [[likely]] {
                int l{ list[s[i]].front() }, r{ list[s[i]].back() };
                to[l] = fw(l - 1);
                to[r] = n - to[l] - 1;
                fw.add(r, -1);
                list[s[i]].pop_front();
                list[s[i]].pop_back();
                vis[l] = vis[r] = true;
            } else {
                fw.add(i,-1);
                to[i] = n / 2;
                vis[i] = true;
            }
        }
        int ans{};
        fw.clear(); // 我们真正的枚举 只枚举左半部分应该在的左下标处， 用fenwick的累加和统计距离计算index
        for(int val : to | std::views::reverse) {
            ans += fw(val);
            fw.add(val,1);
        }
        return ans;
    }
};
