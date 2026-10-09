

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<int> maxSumOfThreeSubarrays(vector<int>& a, int k)
    {
        std::vector<int> sums(a.size() - k + 1);
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
        std::vector<int> prefix(sums.size());   // prefix[i] represents the max sum of subarray in index 0 ~ i.
        for(int i : std::views::iota(1,static_cast<int>(prefix.size())))
        {
            prefix[i] = std::max(prefix[i - 1],i,[&sums](const int x,const int y){ return sums[x] < sums[y]; });
        }
        std::vector<int> suffix(sums.size());  // suffix[i] represents the max sum of subarray in index i ~ size - 1
        suffix.back() = sums.size() - 1;
        for(int i : std::views::iota(0,static_cast<int>(suffix.size() - 1)) | std::views::reverse)
        {
            suffix[i] = std::max(i,suffix[i + 1],[&sums](const int x,const int y){ return sums[x] < sums[y]; });
        }
        std::vector<int> ret;
        sum = std::numeric_limits<int>::min();
        for(int i : std::views::iota(k,static_cast<int>(sums.size()) - k))
        {
            int val{ sums[i] + sums[prefix[i - k]] + sums[suffix[i + k]] };
            if(val > sum)
            {
                sum = val;
                ret = { prefix[i - k],i,suffix[i + k] };
            }
        }
        return ret;
    }
};

int main()
{
    std::vector par{ 7,13,20,19,19,2,10,1,1,19 };
    Solution{}.maxSumOfThreeSubarrays(par,3);

    return 0;
}