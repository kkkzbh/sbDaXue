

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

let constexpr error = "No Solution";

fun main() -> int
{
    int n,k;
    std::cin >> n >> k;
    let a = std::vector(k + 1,0);
    for(let &v in a) {
        std::cin >> v;
    }
    for(let const& v in a) {
        if(v > n) {
            std::cout << error;
            return 0;
        }
    }
    let y = n;
    if(y < a[0]) {
        std::cout << error;
        return 0;
    }
    y -= a[0];
    let count = 0;
    for(let i in iota(1,k + 1)) {
        if(y < a[i]) {
            ++count;
            y = n;
        }
        y -= a[i];
    }
    std::cout << count;

}