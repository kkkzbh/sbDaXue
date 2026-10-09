

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto g = std::vector(n,std::vector<int>{});
    auto id = std::vector(n,0LL);
    for(auto i = 0; i != m; ++i) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        g[x].emplace_back(y);
        ++id[y];
    }
    auto constexpr MOD = 998244353;
    // 除法取模
    // 几条路 总长度
    // 拓扑+dp  cnt[root] = \sum cnt[son]
    // len[root] = \sum (len[son] + cnt[son]?)
    // 5次方 不压缩重边 ?
    auto que = std::deque<int>{};
    for(auto i = 0; i != n; ++i) {
        if(id[i] != 0) {
            continue;
        }
        que.push_back(i);
    }
    auto cnt = std::vector(n,1LL);
    auto len = std::vector(n,0LL);
    auto vis = std::vector(n,false);
    auto tops = [&](auto&& dfs,int u) {
        if(vis[u]) {
            return;
        }
        vis[u] = true;
        for(auto v : g[u]) {
            dfs(dfs,v);
            (cnt[u] += cnt[v]) %= MOD;
            (len[u] += len[v] + cnt[v]) %= MOD;
        }
    };
    auto sumcnt = 0LL,sumlen = 0LL;
    for(auto v : que) {
        tops(tops,v);
    }
    for(auto i = 0; i != n; ++i) {
        (sumcnt += cnt[i]) %= MOD;
        (sumlen += len[i]) %= MOD;
    }
    auto pow = [](auto val,auto p) {
        auto ret = 1LL;
        for(; p; p >>= 1) {
            if(p & 1) {
                (ret *= val) %= MOD;
            }
            (val *= val) %= MOD;
        };
        return ret;
    };
    auto ans = sumlen * pow(sumcnt,MOD - 2) % MOD;
    std::cout << ans;

}