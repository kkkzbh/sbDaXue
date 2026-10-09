

#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>
#include<bitset>
#include<numeric>
#include<numeric>

#define fun auto
#define let auto
#define in :

using namespace std::views;
using namespace std::literals::string_literals;

fun main() -> int
{
    let s = ""s;
    std::cin >> s;
    let n = int(s.size());
    let p = std::vector(n,std::vector(n,0.));
    std::ranges::for_each(p | join,[](auto& val){ std::cin >> val; });


    return 0;
};