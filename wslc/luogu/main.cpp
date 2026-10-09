

#include <bits/stdc++.h>

struct disjoint_set
{
    auto static constexpr root = -1;

    explicit disjoint_set(int n) noexcept : a{ n,root },d{ n,0 } {}

    auto find(auto i) noexcept
    {
        if(a[i] == root) {
            return i;
        }
        auto r = a[i];
        (d[i] += d[r]) %= 3;
        return a[i] = find(i);
    }

    auto merge(auto x,auto y,auto r) noexcept
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            return static_cast<int>((d[x] - d[y] + 3) % 3 == r);
        }
        a[fx] = fy;
        d[fx] = (r + d[y] - d[x] + 3) % 3;
    }

    std::vector<int> a,d;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto ans = 0;
    auto set = disjoint_set{ n };
    for(auto i = 0; i != m; ++i) {
        int r,x,y;
        std::cin >> r >> x >> y;
        --r,--x,--y;
        if(x >= n or y >= n or x == y and r == 1) {
            ++ans;
            continue;
        }
        ans += set.merge(x,y,r);
    }
    std::cout << ans;

}