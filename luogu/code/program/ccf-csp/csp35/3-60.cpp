

#include<bits/stdc++.h>

struct pad 
{
    pad() = default;
    pad(int x1,int x2,int x3,int x4) : NN{ x1 },MM{ x2 },nn{ x3 },mm{ x4 } {}
    int NN,MM,nn,mm;
    std::vector<std::string> a;
};

using namespace std::string_literals;

auto main() -> int 
{
    int n;
    std::cin >> n;
    auto text = std::vector(n,""s);
    std::cin.ignore();
    for(auto& s : text) {
        std::getline(std::cin,s);   
    }
    auto ts = ""s;
    auto d = std::vector<std::string>{};
    while(std::getline(std::cin,ts)) {
        if(ts.front() != '@') {
            continue;
        } else {
            break;
        }
    }
   
    auto check_first = [&](auto const& s) {
        int NN,MM,nn,mm;
        auto ret = sscanf(s.data(),"@@ -%d,%d +%d,%d @@",&NN,&MM,&nn,&mm);
        return std::make_tuple(ret == 4,NN,MM,nn,mm);
    };
    
    auto die = [&]() {
        std::cout << "Patch is damaged.";
        std::exit(0);
    };
    
    if(ts.front() != '@') {
        die();
    }
    
    
    auto p = std::vector<pad>{};
    
    {
        auto [flag,a,b,c,d] = check_first(ts);
        if(not flag) {
            die();
        }
        p.emplace_back(a,b,c,d);
    }
    
    while(std::getline(std::cin,ts)) {
        if(ts.front() == '#') {
            continue;
        }
        if(ts.front() == '@') {
            auto [flag,a,b,c,d] = check_first(ts);
            auto& [NN,MM,nn,mm,_] = p.back();
            if(not flag or a < NN + MM) {
                die();
            }
            p.emplace_back(a,b,c,d);
            continue;
        }
        if(ts.front() != '-' and ts.front() != '+' and ts.front() != ' ') {
            die();
        }
        auto& [_1,_2,_3,_4,data] = p.back();
        data.push_back(std::move(ts));
    }
    
    auto pn = int(p.size());
    auto xp = std::vector(pn,std::vector<std::string>{}),yp = xp;
    for(auto i = 0; i != pn; ++i) {
        auto const& [NN,MM,nn,mm,data] = p[i];
        for(auto const& str : data) {
            if(str.front() == ' ') {
                xp[i].emplace_back(str,1),yp[i].emplace_back(str,1);
            } else if(str.front() == '-') {
                xp[i].emplace_back(str,1);
            } else {
                yp[i].emplace_back(str,1);
            }
        }
        auto const& xs = xp[i];
        auto const& ys = yp[i];
        if(int(xs.size()) != MM or int(ys.size()) != mm) {
            die();
        }
    }
    
    auto same = [&](int start,int pi) {
        auto const& [NN,MM,nn,mm,_] = p[pi];
        auto const& xs = xp[pi];
        
        if(start < 0 or start + MM > int(text.size())) {
            return false;
        }
        
        return std::equal(text.begin() + start,text.begin() + start + MM,xs.begin());
    };
    
    auto kit = 0;
    
    auto exchange = [&](int start,int pi) {
        auto const& [NN,MM,bb,mm,_] = p[pi];
        auto const& ys = yp[pi];
        for(auto i = kit; i != start; ++i) {
            std::cout << text[i] << '\n';
        }
        for(auto const& s : ys) {
            std::cout << s << '\n';
        }
        kit = start + MM;
    };
    
    for(auto i = 0; i != pn; ++i) {
        auto& [NN,MM,nn,mm,data] = p[i];
        auto buc = std::vector<decltype(MM)>{};
        for(auto delta = -MM + 1; delta < MM and (i == 0 or NN + delta >= p[i - 1].NN + p[i - 1].MM); ++delta) {
            if(same(NN + delta - 1,i)) {
                buc.push_back(delta);
            }
        }
//        if(buc.empty()) {
//            die();
//        }
        auto min = std::numeric_limits<decltype(buc)::value_type>::max();
        for(auto val : buc) {
            min = std::min(min,std::abs(val));
        }
        auto buc2 = decltype(buc){};
        for(auto val : buc) {
            if(std::abs(val) == min) {
                buc2.push_back(val);
            }
        }
        auto delta = buc.empty() ? 0 : buc2.front();
        exchange(NN + delta - 1,i);
        for(auto j = i; j != pn; ++j) {
            p[j].NN += delta;
        }
    }


    for(auto i = kit; i != int(text.size()); ++i) {
        std::cout << text[i] << '\n';
    }
    
    
    return 0;
}