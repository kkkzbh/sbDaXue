

#include <bits/stdc++.h>

using i64 = long long;

template<typename T>
auto constexpr MAX = std::numeric_limits<T>::max();

using namespace std::literals;

auto constexpr MOD = 998244353;

auto solve() -> void
{
    int n;
    i64 m;
    std::cin >> n >> m;
    auto a = ""s;
    std::cin >> a;
    auto ans = 1ll;
    auto pow = [](i64 v,auto p) -> i64 {
        auto ret = 1ll;
        while(p) {
            if(p & 1) {
                ret *= v;
                ret %= MOD;
            }
            v *= v;
            v  %= MOD;
            p >>= 1;
        }
        return ret;
    };
    auto inv2 = pow(2,MOD - 2);
    auto ca = std::count(a.begin(),a.end(),'A');
    auto cb = std::count(a.begin(),a.end(),'B');
    auto cc = std::count(a.begin(),a.end(),'C');
    auto cd = ca;
    m = std::min(2ll * ca + cb,m);
    auto k = ca + cd + cb;
    auto bd = std::max(m + 1ll,2 * n + 2ll) + 1;
    auto fac = std::vector(bd,0ll);
    fac[0] = 1;
    for(auto i = 1; i != bd; ++i) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    auto inv = fac;
    inv[bd - 1] = pow(fac[bd - 1],MOD - 2);
    for(auto i = bd - 1; i--; ) {
        inv[i] = (i + 1) * inv[i + 1] % MOD;
    }

    for(auto i = 0; i <= m; ++i) {
        ans += fac[k] * inv[i] % MOD * inv[k - i] % MOD;
    }

    auto pccb = std::vector(m + 1,0ll);
    pccb[0] = 1;
    for(auto i = 1; i <= std::min(m,i64(cb)); ++i) {
        pccb[i] =  (pccb[i - 1] + (fac[cb] * inv[i] % MOD * inv[cb - i] % MOD)) % MOD;
    }

    auto C = [&](auto n,auto m) -> i64 {
        return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
    };

    for(auto sa = 0; ;++sa) {
        if(sa * 2 > m) {
            break;
        }
        auto y = m - 2 * sa;
        y = std::min(y,i64(cb));
        if(y > cb) {
            // continue;
        }
        ans -= C(ca,sa) * pccb[y] % MOD;
        ans += MOD;
        ans %= MOD;
    }

    std::cout << ans << '\n';

}

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int tt = 1;
    // std::cin >> tt;
    while(tt--) {
        solve();
    }


}