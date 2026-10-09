

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
    int k;
    std::cin >> k;
    let a = std::vector(k,0);
    for(let &v in a) {
        std::cin >> v;
    }
    let mique = __gnu_pbds::priority_queue<int,std::greater<>>{ a.begin(),a.end() };

    let merge = [](int x,int y) {
        return x + y - 1;
    };

    let min = 0;
    while(mique.size() != 1) {
        let x1 = mique.top();
        mique.pop();
        let x2 = mique.top();
        mique.pop();
        let r = merge(x1,x2);
        min += r;
        mique.push(r + 1);
    }

    let maque = __gnu_pbds::priority_queue<int>{ a.begin(),a.end() };

    let max = 0;
    while(maque.size() != 1) {
        let x1 = maque.top();
        maque.pop();
        let x2 = maque.top();
        maque.pop();
        let r = merge(x1,x2);
        max += r;
        maque.push(r + 1);
    }

    std::print("{} {}",max,min);

}