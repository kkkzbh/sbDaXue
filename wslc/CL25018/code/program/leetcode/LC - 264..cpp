


#include<bits/stdc++.h>

auto init = []{ std::ios::sync_with_stdio(false),std::cin.tie(nullptr); return char{}; }();

struct Solution
{

    using int64 = long long;

    int nthUglyNumber(int n)
    {
        std::priority_queue<int64,std::vector<int64>,std::greater<>> que;
        std::unordered_set<int64> set;
        que.push(1);
        set.insert(1);
        int64 ret;
        for(int i{ 1 }; i <= n; ++i)
        {
            ret = que.top();
            que.pop();
            int64 val;
            val = ret * 2; if(set.find(val) == set.end()){ que.push(val); set.insert(val); }
            val = ret * 3; if(set.find(val) == set.end()){ que.push(val); set.insert(val); }
            val = ret * 5; if(set.find(val) == set.end()){ que.push(val); set.insert(val); }
        }
        return ret;
    }
};