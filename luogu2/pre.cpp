

#include<iostream>
#include<chrono>
#include<fstream>
#include<functional>

namespace
{
    [[maybe_unused]]
    struct timer
    {
        timer() = default;

        ~timer()
        {
            auto const end{std::chrono::high_resolution_clock::now()};
            auto const duration{std::chrono::duration_cast<std::chrono::microseconds>(end - start)};
            //std::cout << "\n\n" << duration.count() << "μs";
            char tim[30];
            snprintf(tim,sizeof(tim),"\n\n%lldμs",duration.count());
            fputs(tim,stdout);
        }

        decltype(std::chrono::high_resolution_clock::now()) start{std::chrono::high_resolution_clock::now()};
    }_;

    [[maybe_unused]]
    auto static fio = [] // NOLINT
    {
        std::freopen("../in.in","r",stdin);
        std::freopen("../out.out","w",stdout);
        return char{};
    }();

}