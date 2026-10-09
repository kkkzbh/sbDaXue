

#include<bits/stdc++.h>

using namespace std::string_literals;

auto main() -> int 
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto s = ""s;
    std::getline(std::cin,s);
    s.pop_back(),s.erase(s.begin());
    int n;
    std::cin >> n;
    auto map = std::map<char,char>{};
    for(auto c : s) {
        map[c] = c;
    }
    for(auto i = 0; i != n; ++i) {
        char c,x,y;
        std::cin >> c;
        std::cin.get(x),std::cin.get(y);
        std::cin >> c;
        map[x] = y;
    }
    int m;
    std::cin >> m;
    auto f = [&](auto& str) {
        for(auto& c : str) {
            c = map[c];
        }
    };
    auto dp = std::vector{ s };
    for(f(s); s != dp.front(); f(s)) {
        dp.push_back(s);
    }
    auto mod = int(dp.size());
    for(auto i = 0; i != m; ++i) {
        int k;
        std::cin >> k;
        std::cout << '#' << dp[k % mod] << "#\n";
    }
    
        
    return 0;
}