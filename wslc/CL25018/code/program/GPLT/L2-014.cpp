

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

fun main() -> int
{
    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());

    let que = std::vector<std::vector<int>>{};

    let find = [&](int v) {
        return std::upper_bound(que.begin(),que.end(),v,[](int v,const auto& vec) {
            return v < vec.back();
        });
    };

    for(let v in a) {
        let it = find(v);
        if(it == que.end()) {
            que.push_back({ v });
        } else {
            it->push_back(v);
        }
    }

    std::cout << que.size() << '\n';

    return 0;
}