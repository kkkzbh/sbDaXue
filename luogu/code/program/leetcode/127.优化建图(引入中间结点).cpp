

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<deque>
#include<queue>
#include<cassert>
#include<stack>
#include<optional>
#include<array>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<set>
#include<fstream>

#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

struct Solution
{
    int ladderLength(string& s1, string& s2, vector<string>& a)
    {

        if(std::ranges::find(a,s2) == a.end()) {
            return 0;
        }

        let id = std::unordered_map<std::string,int>{};

        let graph = std::vector(a.size(),std::vector<int>{});

        let createV = [&](const std::string& s) {
            let [it,flag] = id.emplace(s,id.size());
            if(flag) {
                graph.emplace_back();
            }
        };

        let addE = [&](std::string& s) {
            createV(s);
            let i1 = id[s];
            for(let &c in s) {
                let tmp = c;
                c = '*';
                createV(s);

                let i2 = id[s];
                graph[i1].push_back(i2);
                graph[i2].push_back(i1);

                c = tmp;
            }
        };

        for(let &s in a) {
            addE(s);
        }
        if(!id.contains(s1)) {
            addE(s1);
        }

        let bfs = [&](int i,int tar) {

            let que = std::queue<int>{};
            let vis = std::vector(id.size(),false);
            que.push(i);
            vis[i] = true;

            let level = 1;
            while(!que.empty()) {
                for(let k in std::views::iota(0,int(que.size()))) {
                    let it = que.front();
                    que.pop();
                    if(it == tar) {
                        return level;
                    }
                    for(let v in graph[it] | std::views::filter([&](int i){ return !vis[i]; })) {
                        que.push(v);
                        vis[v] = true;
                    }
                }
                ++level;
            }

            return 0;
        };

        return (bfs(id[s1],id[s2]) + 1) / 2;

    }
};