

#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>
#include<bitset>
#include<numeric>
#include<numeric>
#include<array>
#include<ext/algorithm>

#define fun auto
#define let auto
#define in :

using namespace std::views;
using namespace std::literals::string_literals;


fun main() -> int
{
    let a = std::array<int,3>{};
    std::ranges::for_each(a,[](auto& val){ std::cin >> val; });
    std::cout << __gnu_cxx::__median(a[0],a[1],a[2]) + 2 << '\n';


    return 0;
};