

import std;
#ifndef ONLINE_JUDGE
#include <cassert>
#endif

using namespace std::views;
using namespace std::string_literals;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(m,std::vector<int>{});
    auto fm = std::vector(n,false);
    for(auto tmp = ""s; auto& vec : a) {
        int k;
        std::cin >> k;
        vec.resize(k);
        for(auto& val : vec) {
            std::cin >> tmp;
            auto female = tmp[0] == '-';
            std::sscanf(tmp.data() + female,"%d",&val);
            fm[val] = female;
        }
    }
    int A,B;
    {
        bool gA,gB;
        auto tmp = ""s;
        std::cin >> tmp;
        gA = tmp[0] == '-';
        std::sscanf(tmp.data() + gA,"%d",&A);
        fm[A] = gA;
        std::cin >> tmp;
        gB = tmp[0] == '-';
        std::sscanf(tmp.data() + gB,"%d",&B);
        fm[B] = gB;
    }

    auto d = std::vector(2,std::vector(n,0.));
    auto mi = std::map<int,int> {
        { A,0 },
        { B,1 }
    };
    for(auto vec : a) {
        auto iA = -1,iB = -1;
        auto nn = static_cast<int>(vec.size());
        for(auto [i,vp] : zip(iota(0,nn),vec)) {
            auto const& val = vp;
            if(A == val) {
                iA = i;
            } else if(B == val) {
                iB = i;
            }
        }
        auto w = 1. / nn;
        #define code(X) \
        if(i##X != -1) { \
           for(auto val : iota(0,nn) | filter([i##X](auto i) { \
               return i != i##X; \
           }) | transform([&vec](auto i) { \
               return vec[i]; \
           }) | filter([&](auto val) { \
               return fm[val] != fm[X]; \
           })) { \
               d[mi[X]][val] += w; \
           } \
        }
        code(A)
        code(B)
        #undef code
    }
    auto maxA = std::ranges::max(d[mi[A]]),maxB = std::ranges::max(d[mi[B]]);
    auto AA = fm[A] ? std::format("-{}",A) : std::format("{}",A);
    auto BB = fm[B] ? std::format("-{}",B) : std::format("{}",B);
    auto equal = [](auto lhs,auto rhs) noexcept {
        auto constexpr eps = 1e-6;
        return std::abs(lhs - rhs) < eps;
    };
    #ifndef ONLINE_JUDGE
    assert(equal(d[mi[A]][B],d[mi[B]][A]));
    #endif
    if(equal(d[mi[A]][B],maxA) and equal(d[mi[B]][A],maxB)) {
        std::println("{} {}",AA,BB);
        return 0;
    }
    #define code(X) \
    for(auto i : zip(iota(0,n),d[mi[X]]) | filter([&](auto const& p) noexcept { \
        return equal(std::get<1>(p),max##X);     \
    }) | keys) { \
       std::println("{} {}{}",X##X,fm[i] ? "-" : "",i);  \
    }
    code(A)
    code(B)
    #undef code
}
