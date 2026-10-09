

#include<bits/extc++.h>

using namespace std::views;

auto main() -> int
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,std::vector(n,0));
    std::ranges::for_each(a | join,[](auto& v){ std::cin >> v; });

    auto s = std::vector(n,false);
    auto ans {
            std::invoke([&](this auto&& self,int i) -> int {
                if(i == n) {
                    return 0;
                }
                return std::ranges::min(iota(0,n) |
                                        filter([&](auto j){ return not s[j]; }) |
                                        transform([&](auto j){
                                            s[j] = true;
                                            auto val = a[i][j] + self(i + 1);
                                            s[j] = false;
                                            return val;
                                        }));
            },0)
    };
    std::println("{}",ans);

}