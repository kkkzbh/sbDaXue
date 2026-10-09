

#include<bits/stdc++.h>
using namespace std;

constexpr static int N{ 20000 + 2 };

struct node
{
    auto friend operator<=>(const node& n1,const node& n2)
    {
        if(n1.val == n2.val)
        {
            return n2.vec <=> n1.vec;
        }
        return n1.val <=> n2.val;
    }

    auto friend operator==(const node& n1,const node& n2)
    {
        return n1.val == n2.val and n1.vec == n2.vec;
    }

    auto friend operator+(const node& n1,const node& n2)
    {
        std::vector<int> a{ n1.vec };
        std::ranges::copy(n2.vec,std::back_inserter(a));
        return node{ a,n1.val + n2.val };
    }

    auto operator+=(const node& n)
    {
        std::ranges::copy(n.vec,std::back_inserter(vec));
        val += n.val;
        return *this;
    }

    std::vector<int> vec;
    int val;
};

std::array<std::array<node,3 + 1>,N> dp;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& a, int k)
    {
        std::vector<int> sums( a.size() - k + 1);
        int sum{};
        for(int i : std::views::iota(0,k))
        {
            sum += a[i];
        }
        sums[0] = sum;
        for(int l{ 1 },r{ k }; r != a.size(); ++l,++r)
        {
            sum -= a[l - 1];
            sum += a[r];
            sums[l] = sum;
        }

        for(auto& v : dp)
        {
            std::ranges::fill_n(v.begin(),3 + 1,node{});
        }

        // dp[n][m] = max ->  dp[n - 1][m] | dp[n - k][m - 1] + { std::vector{ n - 1 },sums[n - 1] }
        // m == 0 -> dp = 0
        // n ----   m.max = n / k;

        for(int i : std::views::iota(1,static_cast<int>(sums.size()) + 1)) // j == 1
        {
            dp[i][1] = std::max(dp[i - 1][1],node{ std::vector{ i - 1 },sums[i - 1] });
        }

        for(int i : std::views::iota(2,static_cast<int>(sums.size()) + 1))
        {
            for(int j : std::views::iota(2,std::min(1 + (i - 1) / k + 1,3 + 1)))
            {
                dp[i][j] = std::max(dp[i - 1][j],dp[i - k][j - 1] + node{ std::vector{ i - 1 },sums[i - 1] });
            }
        }
        return dp[sums.size()][3].vec;
    }
};

int main()
{
    std::vector par{ 4,3,2,1 };
    Solution{}.maxSumOfThreeSubarrays(par,1);

    return 0;
}