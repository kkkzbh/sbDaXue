
#include<bits/stdc++.h>

class Solution {
public:

    constexpr static int MOD{ 1000000000 + 7 };
    using int64 = long long;

    int sumSubarrayMins(std::vector<int>& a)
    {
        std::stack<int> stk;
        stk.push(-1);
        a.push_back(-1);    // 因为每个元素弹出时才会结算，所以最后这个哨兵会使得所有栈的元素得以弹出
        int64 ans{};
        for(int i{},cei = a.size(); i != cei; ++i)
        {
            while(stk.size() > 1 and a[i] <= a[stk.top()])
            {
                int val{ stk.top() };
                stk.pop();
                ans += static_cast<int64>(a[val]) * (val - stk.top()) * (i - val);
                ans %= MOD;
            }
            stk.push(i);
        }
        return ans;
    }
};