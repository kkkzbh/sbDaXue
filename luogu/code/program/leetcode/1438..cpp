

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    void push(int it,std::deque<int>& que,std::vector<int>& a,auto cmp)
    {
        while(!que.empty() and (cmp(a[it],a[que.back()]) or a[que.back()] == a[it])) // less 是
        {
            que.pop_back();
        }
        que.push_back(it);
    }

    void pop(int it,std::deque<int>& que,std::vector<int>& a)
    {
        if(it == que.front())
        {
            que.pop_front();
        }
    }

    int longestSubarray(vector<int>& a, int limit)
    {
        std::deque<int> smq,bgq;
        int ret{};
        for(int l{},r{}; r != a.size(); ++r)
        {
            push(r,smq,a,std::less<>{});
            push(r,bgq,a,std::greater<>{});
            int x{ bgq.empty() ? 0 : a[bgq.front()] };
            int y{ smq.empty() ? 0 : a[smq.front()] };
            while(x - y > limit)
            {
                pop(l,smq,a);
                pop(l,bgq,a);
                ++l;
                x = bgq.empty() ? 0 : a[bgq.front()];
                y = smq.empty() ? 0 : a[smq.front()];
            }
            ret = std::max(ret,r - l + 1);
        }
        return ret;
    }
};