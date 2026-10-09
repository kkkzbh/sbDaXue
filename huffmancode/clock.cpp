



#include "clock.h"



auto now()
{
    return std::chrono::high_resolution_clock::now();
}

auto ptime(decltype(std::chrono::high_resolution_clock::now()) start,decltype(std::chrono::high_resolution_clock::now()) end) -> void
{
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << duration.count() << " ms\n";
}
