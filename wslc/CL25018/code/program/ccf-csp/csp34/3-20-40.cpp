

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

auto main() -> int
{
    using namespace std::string_literals;
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto cnt = std::vector(n,0);
    auto a = std::vector(n,std::vector<std::string>{});
    auto table = std::set<std::string>{};
    auto ans = std::vector<std::string>{};
    for(auto i = 0; i != n; ++i) {
        auto s = ""s;
        std::cin >> s >> cnt[i];
        for(auto c : s) {
            auto [it,ok] = table.emplace(1,c);
            a[i].emplace_back(1,c);
        }
    }
    for(auto const& c : table) {
        ans.emplace_back(c);
    }
    using key_t = std::pair<std::string,std::string>;
    auto que = std::invoke([]() {
        using node = std::pair<long long,key_t>;
        auto cmp = [](node const& x,node const& y) {
            auto const& [c1,ss1] = x;
            auto const& [c2,ss2] = y;
            if(c1 != c2) {
                return c1 < c2;
            }
            auto const& [sx1,sy1] = ss1;
            auto const& [sx2,sy2] = ss2;
            auto len1 = int(sx1.size() + sy1.size()),len2 = int(sx2.size() + sy2.size());
            if(len1 != len2) {
                return len1 > len2;
            }
            if(sx1.size() != sx2.size()) {
                return sx1.size() > sx2.size();
            }
            auto ret = sx1.compare(sx2);
            if(ret != 0) {
                return ret > 0;
            }
            return sy1 > sy2;
        };
        using namespace __gnu_pbds;
        using que_t = priority_queue<node,decltype(cmp)>;
        return que_t{ cmp };
    });
    auto map = std::map<key_t,decltype(que)::point_iterator>{};
    auto light = 0;
    for(auto k = 0; k != n; ++k) {
        auto const& s = a[k];
        for(auto i = 0; i + 1 < int(s.size()); ++i) {
            auto key = std::make_pair(s[i],s[i + 1]);
            auto find = map.find(key);
            if(find == map.end()) {
                auto it = que.push({ cnt[k],std::move(key) });
                auto const& [_,k] = *it;
                map.emplace(k,it);
                continue;
            }
            auto it = std::get<1>(*find);
            auto const& [v,_] = *it;
            que.modify(it,{ v + cnt[k],std::move(key) });
        }
    }
    while(table.size() != m and light != n) {
        auto [v,str] = que.top();
        auto const& [s1,s2] = str;
        auto [it,ok] = table.insert(s1 + s2);
        ans.emplace_back(*it);
        light = 0;
        for(auto k = 0; k != n; ++k) {
            auto& s = a[k];
            auto tmp = std::decay_t<decltype(s)>{};
            auto i = 0;
            auto erase = [&](int i) {
                auto key = std::make_pair(s[i],s[i + 1]);
                auto find = map.find(key);
                if(find == map.end()) {
                    return;
                }
                auto const& [str,it] = *find;
                #ifdef DEBUG
                assert(it != decltype(it){});
                #endif
                que.erase(it);
                map.erase(find);
            };
            auto insert = [&](int i) {
                auto key = std::make_pair(s[i],s[i + 1]);
                if(map.count(key)) {
                    #ifdef DEBUG
                    assert(map.find(key) != map.end());
                    #endif
                    auto it = std::get<1>(*map.find(key));
                    auto& [ct,str] = *it;
                    que.modify(it,{ ct + cnt[k],std::move(key) });
                    return;
                }
                #ifdef DEBUG
                assert(map.find(key) == map.end());
                #endif
                auto it = que.push({ cnt[k],std::move(key) });
                map.emplace(std::get<1>(*it),it);
            };
            while(i + 1 < int(s.size())) {
                if(s[i] == s1 and s[i + 1] == s2) {
                    erase(i);
                    if(i) {
                        erase(i - 1);
                    }
                    if(i + 2 < int(s.size())) {
                        erase(i + 1);
                    }
                    s[i] += s[i + 1];
                    if(i) {
                        insert(i - 1);
                    }
                    s[i + 1] = std::move(s[i]);
                    if(i + 2 < int(s.size())) {
                        insert(i + 1);
                    }
                    tmp.push_back(std::move(s[i + 1]));
                    i += 2;
                    continue;
                }
                tmp.push_back(s[i]);
                ++i;
            }
            if(i != int(s.size())) {
                tmp.push_back(std::move(s.back()));
            }
            s = std::move(tmp);
            light += s.size() == 1;
        }
    }

    for(auto const& s : ans) {
        std::cout << s << '\n';
    }


    return 0;
}