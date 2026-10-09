

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(m,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto s = std::vector(n,std::string{});
    for(auto& str : s) {
        std::cin >> str;
    }
    auto max = 0;
    auto scores = std::vector(n,0);
    auto k = 0;
    for(auto const& str : s) {
        for(auto i = 0; i != str.size(); ++i) {
            if(str[i] == 'o') {
                scores[k] += a[i];
            }
        }
        scores[k] += (k + 1);
        max = std::max(max,scores[k++]);
    }
    auto buc = std::vector<int>{};
    buc.reserve(m);
    k = 0;
    for(auto const& str : s) {
        for(auto i = 0; i != str.size(); ++i) {
            if(str[i] == 'x') {
                buc.emplace_back(a[i]);
            }
        }
        std::sort(buc.begin(),buc.end(),std::greater{});
        auto sum = scores[k++];
        auto tar = max;
        if(sum >= tar) {
            std::cout << "0\n";
            goto cc;
        }
        for(auto i = 0; i != buc.size(); ++i) {
            sum += buc[i];
            if(sum >= tar) {
                std::cout << i + 1 << '\n';
                goto cc;
            }
        }

        cc:
        buc.clear();
    }

}