

#include<bits/stdc++.h>
using namespace std;

// dp[n][k] = max -> dp[n - k][k - 1] + a[n] , dp[n - 1][k]

constexpr static int N{ 2 * 10000 + 2 };

std::array<std::array<std::pair<std::vector<int>,int>,3 + 1>,N> dp;

class Solution {
public:

    std::pair<std::vector<int>,int> dfs(int i,int k,int len,std::vector<int>& a)
    {
        if(!k)
        {
            return std::make_pair(std::vector<int>{},0);
        }
        if((k - 1) * len > i - 1)   //  内层剪枝
        {
            return std::make_pair(std::vector<int>{},-1);
        }
        if(dp[i][k].second != -1)
        {
            return dp[i][k];
        }
        std::vector<int> reta;
        int retv{};
        auto [v1,val1]{ dfs(i - 1,k,len,a) };
        auto [v2,val2]{ dfs(i - len,k - 1,len,a) };
        if(val2 != -1)
        {
            val2 += a[i - 1];
            v2.push_back(i - 1);
        }
        if(val1 < val2)
        {
            retv = val2;
            std::ranges::copy(v2,std::back_inserter(reta));
        }
        else if(val2 > val1)
        {
            retv = val1;
            std::ranges::copy(v1,std::back_inserter(reta));
        }
        else
        {
            retv = val1;
            reta = std::min(v1,v2);
        }
        return dp[i][k] = std::make_pair(reta,retv);
    }

    vector<int> maxSumOfThreeSubarrays(vector<int>& a, int k)
    {
        for(auto& v : dp)
        {
            v.fill(std::make_pair(std::vector<int>{},-1));
        }
        std::vector<int> b(a.size() - k + 1,0);
        int sum{};
        for(int i : std::views::iota(0,k))
        {
            sum += a[i];
        }
        b[0] = sum;
        for(int l{ 1 },r{ k }; r != a.size(); ++r)
        {
            sum -= a[l - 1];
            sum += a[r];
            b[l++] = sum;
        }
        return dfs(b.size(),3,k,b).first;
    }
};

int main()
{
    std::vector<int> a{ { 1,2,1,2,6,7,5,1 } };
    std::ranges::copy(Solution{}.maxSumOfThreeSubarrays(a,2),std::ostream_iterator<int>{ std::cout," " });
    return 0;
}