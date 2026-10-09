

#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 n,s;
using node = std::pair<int,int>;
std::vector<std::pair<int,int>> a; // w cnt


int main()
{
    ios::sync_with_stdio(false),std::cin.tie(nullptr);
    cin >> n >> s;
    a.assign(n,{});
    for(auto& p : a) {
        auto& w = std::get<0>(p);
        auto& cnt = std::get<1>(p);
        std::cin >> w >> cnt;
    }
    std::sort(a.begin(),a.end(),[&](node const& lp,node const& rp) {
         return lp.second < rp.second;
    });
    auto sum = 0ll;
    for(auto& p : a) {
        sum += p.first;
    }
    auto k = 0;
    auto ans = 0LL;
    for(auto i = 0; ; ) {
        if(s < sum) {
            ans += s;
            ++k;
        } else {
            ans += (a[i].second - k) * 1LL * a[i].first;
            if(++i == n) {
                goto aans;
            }
            continue;
        }
        auto& p = a[i];
        auto w = p.first;
        auto cnt = p.second;
        while(cnt - k == 0) {
            sum -= w;
            if(++i == n) {
                goto aans;
            }
            cnt = a[i].second;
            w = a[i].first;
        }
    }
    aans:
    std::cout << ans;

}