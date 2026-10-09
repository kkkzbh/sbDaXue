

#include<bits/stdc++.h>

auto init{ []
           {
                std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
                return char{};
           }()};

struct Solution
{
    int largestRectangleArea(std::vector<int>& a)
    {
        std::stack<int> stk;
        stk.push(-1);
        a.push_back(-1);
        int ans{};
        for(int i{},cei = a.size(); i != cei; ++i)
        {
            while(stk.size() > 1 and a[i] < a[stk.top()])
            {
                int val{ stk.top() };
                stk.pop();
                ans = std::max(ans,a[val] * (i - stk.top() - 1));
            }
            if(stk.size() == 1 or a[i] != a[stk.top()])
            {
                stk.push(i);
            }
            else
            {
                stk.pop();
                stk.push(i);
            }
        }
        return ans;
    }
};