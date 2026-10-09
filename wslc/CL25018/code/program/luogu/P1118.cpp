

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    int n,sum;
    std::cin >> n >> sum;
    if(n == 1) {
        if(sum == 1) {
            std::cout << 1;
        }
        return 0;
    }
    if(n == 2) {
        if(sum == 3) {
            std::cout << 1 << ' ' << 2;
        }
        return 0;
    }
    auto tg = std::vector(3,std::vector<int>{});
    tg.push_back({ 1,2,1 });
    for(auto i : iota(4,12 + 1)) {
        auto const& bk = tg.back();
        auto vec = std::vector<int>{};
        vec.push_back(bk.front());
        for(auto j : iota(1,int(bk.size()))) {
            vec.push_back(bk[j] + bk[j - 1]);
        }
        vec.push_back(bk.back());
        tg.push_back(std::move(vec));
    }
    auto perm = std::vector(n,0);
    std::iota(perm.begin(),perm.end(),1);
    auto flag = false;
    while(std::invoke([&] {
        auto s = 0;
        auto const& coef = tg[n];
        for(auto i : iota(0,n)) {
            s += coef[i] * perm[i];
            if(s > sum) {
                return true;
            }
        }
        return not ((flag = s == sum));
    }) and std::ranges::next_permutation(perm).found ){}

    if(not flag) {
        return 0;
    }

    std::ranges::for_each(std::as_const(perm),[](auto const& val){ std::cout << val << ' '; });

}