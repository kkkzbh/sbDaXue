

#include<bits/stdc++.h>

struct Solution
{

    int longestValidParentheses(const std::string& s)
    {
        std::vector<int> a(s.size() + 2,0);
        for(int i{ 2 }; i <= s.size(); ++i) // < is more safe.
        {
            if(s[i - 1] != '(')
            {
                if(s[i - 2] == '(')
                {
                    a[i] = a[i - 2] + 2;
                }
                else
                {
                    a[i] += a[i - 1];
                    int it{ i - 1 - a[i - 1] };
                    for(;it >= 1 and s[it - 1] == ')'; it = it - 1 - a[it - 1])
                    {
                        a[i] += a[it - 1];
                    }
                    if(it >= 1) a[i] += a[it - 1] + 2;
                    else a[i] = 0;
                }
            }
        }
        return *std::max_element(a.begin() + 1,a.end() - 1);
    }
};