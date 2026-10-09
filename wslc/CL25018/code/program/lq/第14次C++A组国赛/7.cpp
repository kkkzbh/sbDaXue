

#include <bits/stdc++.h>

using i64 = long long;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector(n,std::vector(n,char{}));
    for(auto& vec : a) {
        for(auto& v : vec) {
            std::cin >> v;
        }
    }
    auto cntr = std::vector(n,0),cntc = cntr,ca = cntr,cb = cntr;
    auto rset = std::set<int>{},cset = rset;
    for(auto i = 0; i != n; ++i) {
        for(auto j = 0; j != n; ++j) {
            if(a[i][j] == 95) {
                continue;
            }
            if(a[i][j] == '0') {
                ++cntr[i];
            }
            ++ca[i];
        }
        for(auto j = 0; j != n; ++j) {
            if(a[j][i] == 95) {
                continue;
            }
            if(a[j][i] == 48) {
                ++cntc[i];
            }
            ++cb[i];
        }
    }
    auto buc = std::vector(n,0);
    for(auto i = 0; i != n; ++i) {
        buc[i] = i;
    }
    // std::sort(buc.begin(),buc.end(),[&,cmp_fn = std::greater{},proj = [&](int i){ return ca[i]; }](int x,int y) { return cmp_fn(proj(x),proj(y)); });
    auto next = [&](int i,int j) {
        return (++j == n) ? std::make_pair(i + 1,0) : std::make_pair(i,j);
    };
    auto dfs = [&](auto&& dfs,int i,int j) -> bool {
        if(i == n) {
            return true;
        }
        auto ii = buc[i];
        auto [ni,nj] = next(i,j);
        if(a[ii][j] == 95) {

            auto fa = ca[ii] + 1 == n,fb = cb[j] + 1 == n;
            auto k1 = 0,k2 = 0;
            if(fa) {
                for(auto k = 0; k != j; ++k) {
                    k1 <<= 1;
                    k1 |= (a[ii][k]) ^ 48;
                }
                k1 <<= 1;
                for(auto k = j + 1; k != n; ++k) {
                    k1 <<= 1;
                    k1 |= a[ii][k] ^ 48;
                }
            }
            if(fb) {
                for(auto k = 0; k != ii; ++k) {
                    k2 <<= 1;
                    k2 |= a[k][j] ^ 48;
                }
                k2 <<= 1;
                for(auto k = ii + 1; k != n; ++k) {
                    k2 <<= 1;
                    k2 |= a[k][j] ^ 48;
                }
            }

            if(cntr[ii] != n / 2 and cntc[j] != n / 2) {
                a[ii][j] = 48;
                ++cntr[ii];
                ++cntc[j];
                ++ca[ii],++cb[j];
                auto ok1 = true,ok2 = true;
                if(fa) {
                    auto [it1,ok11] = rset.emplace(k1);
                    ok1 = ok11;
                }
                if(fb) {
                    auto [it2,ok22] = cset.emplace(k2);
                    ok2 = ok22;
                }
                if(ok1 and ok2 and dfs(dfs,ni,nj)) {
                    return true;
                }
                if(fa and ok1) {
                    rset.erase(k1);
                }
                if(fb and ok2) {
                    cset.erase(k2);
                }
                --cntr[ii];
                --cntc[j];
                --ca[ii],--cb[j];
            }
            if(ca[ii] - cntr[ii] != n / 2 and cb[j] - cntc[j] != n / 2) {
                a[ii][j] = 49;
                auto ok1 = true,ok2 = true;
                ++ca[ii],++cb[j];
                if(fa) {
                    auto t1 = k1 | (1 << (n - j - 1));
                    auto [it1,ok11] = rset.emplace(t1);
                    ok1 = ok11;
                }
                if(fb) {
                    auto t2 = k2 | (1 << (n - ii - 1));
                    auto [it2,ok22] = cset.emplace(t2);
                    ok2 = ok22;
                }
                if(ok1 and ok2 and dfs(dfs,ni,nj)) {
                    return true;
                }
                if(fa and ok1) {
                    rset.erase(k1 | (1 << (n - j - 1)));
                }
                if(fb and ok2) {
                    cset.erase(k2 | (1 << (n - ii - 1)));
                }
                --ca[ii],--cb[j];
            }
            a[ii][j] = 95;
        } else {

            auto fa = ca[ii] == n,fb = cb[j] == n;
            auto k1 = 0,k2 = 0;
            if(fa) {
                for(auto k = 0; k != j; ++k) {
                    k1 <<= 1;
                    k1 |= (a[ii][k]) ^ 48;
                }
                k1 <<= 1;
                for(auto k = j + 1; k != n; ++k) {
                    k1 <<= 1;
                    k1 |= a[ii][k] ^ 48;
                }
            }
            if(fb) {
                for(auto k = 0; k != ii; ++k) {
                    k2 <<= 1;
                    k2 |= a[k][j] ^ 48;
                }
                k2 <<= 1;
                for(auto k = ii + 1; k != n; ++k) {
                    k2 <<= 1;
                    k2 |= a[k][j] ^ 48;
                }
            }

            auto bit = a[ii][j] ^ 48;
            auto ok1 = true,ok2 = true;
            if(fa) {
                auto [_,ok11] = rset.emplace(k1 | (bit << (n - j - 1)));
                ok1 = ok11;
            }
            if(fb) {
                auto [_,ok22] = cset.emplace(k2 | (bit << (n - ii - 1)));
                ok2 = ok22;
            }
            if(ok1 and ok2 and dfs(dfs,ni,nj)) {
                return true;
            }
            if(fa and ok1) {
                rset.erase(k1 | (bit << (n - j - 1)));
            }
            if(fb and ok2) {
                cset.erase(k2 | (bit << (n - ii - 1)));
            }
        }
        return false;
    };
    auto ok = dfs(dfs,0,0);
    assert(ok);
    for(auto& vec : a) {
        for(auto c : vec) {
            std::cout << c;
        }
        std::cout << '\n';
    }

}