
#include <bits/stdc++.h>

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
            // std::cout << std::format("\n\n{}μs",duration.count());
             // std::println("\n\n{}μs",duration.count());
        }

        decltype(std::chrono::high_resolution_clock::now()) start{};
    }_;

    [[maybe_unused]]
    auto static fio = [] // NOLINT
    {
        std::freopen(DEFAULT_IO_FILE_DIR "in","r",stdin);
        std::freopen(DEFAULT_IO_FILE_DIR "out","w",stdout);
        return char{};
    }();

}
