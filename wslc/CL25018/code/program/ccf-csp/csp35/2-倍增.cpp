

#include<bits/stdc++.h>

using namespace std::string_literals;

auto main() -> int
{
    auto s = ""s;
    std::getline(std::cin,s);
    if(s.back() == '\r') {
        s.pop_back();
    }
    s.pop_back(),s.erase(s.begin());
    int n;
    std::cin >> n;
    auto constexpr step = 30;
    auto st = std::vector(128,std::vector(step,'\0'));
    for(auto i = 0; i != 128; ++i) {
        st[i][0] = char(i);
    }
    for(auto i = 0; i != n; ++i) {
        char c,x,y;
        std::cin >> c,std::cin.get(x),std::cin.get(y),std::cin >> c;
        st[x][0] = y;
    }
    for(auto p = 1; p != step; ++p) {
        for(auto i = 0; i != 128; ++i) {
            st[i][p] = st[st[i][p - 1]][p - 1];
        }
    }
    int m;
    std::cin >> m;
    for(auto i = 0; i != m; ++i) {
        int k;
        std::cin >> k;
        auto str = s;
        for(auto& c : str) {
            for(auto p = step; bool(p--);) {
                if(bool(k >> p & 1)) {
                    c = st[c][p];
                }
            }
        }
        std::cout << '#' << str << "#\n";
    }

}