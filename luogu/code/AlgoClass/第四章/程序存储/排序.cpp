

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<array>
#include<print>
#include<ext/pb_ds/priority_queue.hpp>

#define fun auto
#define let auto
#define in :

using namespace std::views;

fun main() -> int
{
    int n,l;
    std::cin >> n >> l;
    let a = std::vector(n,0);
    for(let &v in a) {
        std::cin >> v;
    }
    std::ranges::sort(a);
    let ans = 0;
    for(let const& v in a) {
        if(l >= v) {
            l -= v;
            ++ans;
        } else {
            break;
        }
    }

    std::print("{}",ans);

}