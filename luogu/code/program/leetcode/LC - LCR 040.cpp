

#include<bits/stdc++.h>

auto init{ []
           {
               std::ios::sync_with_stdio(0),std::cin.tie(0);
               return char{};
           }()};

struct Solution
{
    int maximalRectangle(std::vector<std::string>& v)
    {
        std::vector<std::vector<int>> a;
        a.resize(v.size());
        for(auto& it : a)
        {
            it.reserve(v[0].size());
        }
        for(int i{},cei = v.size(); i != cei; ++i)
        {
            for(int j{},cei = v[0].size(); j != cei; ++j)
            {
                a[i].push_back(v[i][j] ^ 48);
            }
        }

        for(int i{ 1 },cei = a.size(); i < cei; ++i)
        {
            for(int j{},cei = a[0].size(); j != cei; ++j)
            {
                if(a[i][j])
                {
                    a[i][j] = a[i - 1][j] + 1;
                }
            }
        }
        for(const auto& it : a)
        {
            for(const auto val : it)
            {
                std::cout << val << ' ';
            }
            std::cout << '\n';
        }
        int ans{};
        for(int i = a.size() - 1; i >= 0; --i)
        {
            std::stack<int> stk;
            int val{};
            for(int j{},cei = a[i].size(); j != cei; ++j)
            {
                while(!stk.empty() and a[i][j] <= a[i][stk.top()])
                {
                    int vi{ stk.top() };
                    stk.pop();
                    val = std::max(val,a[i][vi] * (j - (stk.empty() ? -1 : stk.top()) - 1));
                }
                stk.push(j);
            }
            while(!stk.empty())
            {
                int vi{ stk.top() };
                stk.pop();
                val = std::max(val,a[i][vi] * (static_cast<int>(a[0].size()) - (stk.empty() ? -1 : stk.top()) - 1));
            }
            std::cout << val << '\n';
            ans = std::max(ans,val);
        }
        return ans;
    }
};