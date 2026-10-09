

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    void push(int it,std::deque<int>& que,std::vector<int>& a)
    {
        while(!que.empty() and a[que.back()] <= a[it])
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

    vector<int> maxSlidingWindow(vector<int>& a, int k)
    {
        std::deque<int> que;
        int l{},r{};
        while(r != a.size() and r - l != k)
        {
            push(r++,que,a);
        }
        std::vector<int> ret;
        ret.push_back(a[que.front()]);
        while(r != a.size())
        {
            pop(l++,que,a);
            push(r++,que,a);
            ret.push_back(a[que.front()]);
        }
        return ret;
    }
};