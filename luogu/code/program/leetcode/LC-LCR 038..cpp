

#include<bits/stdc++.h>

class Solution
{
public:

    constexpr static int N{ 100 + 2 };

    std::vector<int> dailyTemperatures(std::vector<int>& v)
    {
        std::stack<int> stk;
        std::vector<int> ans(v.size(),0);

        for(int i = v.size() - 1; i >= 0; --i)
        {
            while(!stk.empty() and v[i] >= v[stk.top()])
            {
                int val{ stk.top() };
                stk.pop();
                ans[val] = stk.empty() ? 0 : stk.top();
            }
            stk.push(i);
        }
        while(!stk.empty())
        {
            int val{ stk.top() };
            stk.pop();
            ans[val] = stk.empty() ? 0 : stk.top();
        }
        for(int i{},cei = v.size(); i != cei; ++i)
        {
            if(ans[i])
            {
                ans[i] -= i;
            }
        }
        return ans;
    }
};