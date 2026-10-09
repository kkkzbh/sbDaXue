

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<array>
#include<print>
#include<ext/pb_ds/priority_queue.hpp>
#include<numeric>

#define fun auto
#define let auto
#define in :

using namespace std::views;

fun main() -> int
{
    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    for(let &v in a) {
        std::cin >> v;
    }

    std::ranges::sort(a);
    let prefix = std::vector(n + 1,0);
    for(let i in iota(0,n)) {
        prefix[i + 1] = prefix[i] + a[i];
    }
    let sum = std::reduce(prefix.begin(),prefix.end());

    std::print("{:.2f}", 1. * sum / n);


}