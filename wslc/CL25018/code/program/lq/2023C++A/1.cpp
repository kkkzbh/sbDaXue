

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto a = std::string{},b = a;
    std::cin >> a >> b;
    std::reverse(a.begin(),a.end()),std::reverse(b.begin(),b.end());
    if(a.back() == '-') {
        a.pop_back();
    }
    if(b.back() == '-') {
        b.pop_back();
    }
    for(auto& c : a) {
        c ^= 48;
    }
    for(auto& c : b) {
        c ^= 48;
    }
    auto pow2 = [](auto& s) {
        auto s2 = std::string(2 * s.size() + 1,0);
        for(auto i = 0; i != s.size(); ++i) {
            for(auto j = 0; j != s.size(); ++j) {
                s2[i + j] += s[i] * s[j];
                s2[i + j + 1] += s2[i + j] / 10;
                s2[i + j] %= 10;
            }
        }
        return s2;
    };

    auto a2 = pow2(a),b2 = pow2(b);

    auto k = [&]() {
        if(a2.size() != b2.size()) {
            return a2.size() < b2.size();
        }
        for(auto i = a2.size(); i--;) {
            if(a2[i] != b2[i]) {
                return a2[i] < b2[i];
            }
        }
        return false;
    }();
    if(k) {
        std::swap(a2,b2);
    }
    for(auto i = 0; i != b2.size(); ++i) {
        a2[i] -= b2[i];
        if(a2[i] < 0) {
            --a2[i + 1];
            a2[i] += 10;
        }
    }
    while(not a2.empty() and not a2.back()) {
        a2.pop_back();
    }
    if(a2.empty()) {
        std::cout << '0';
        return 0;
    }
    std::reverse(a2.begin(),a2.end());
    if(k) {
        std::cout << '-';
    }
    for(auto& c : a2) {
        c ^= 48;
    }
    std::cout << a2;

}