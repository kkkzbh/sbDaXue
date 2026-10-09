

#include<bits/stdc++.h>
using namespace std;

using int64 = long long;
using uint64 = unsigned long long;

struct bitree
{

    struct node
    {
        bool friend operator<(const node n1,const node n2)
        {
            return n1.len < n2.len;
        }
        int len;
        int cnt;
    };

    std::vector<node> a;

    explicit bitree(uint64 n) : a(std::vector<node>(n + 1)){}

    void update(int i,node val)
    {
        while(i < a.size())
        {
            if(val.len > a[i].len)
            {
                a[i] = val;
            }
            else if(val.len == a[i].len)
            {
                a[i].cnt += val.cnt;
            }
            i += i & -i;
        }
    }

    node query(int i)
    {
        node ret{};
        while(i)
        {
            if(a[i].len == ret.len)
            {
                ret.cnt += a[i].cnt;
            }
            else if(a[i].len > ret.len)
            {
                ret = a[i];
            }
            i -= i & -i;
        }
        return ret;
    }
};

class Solution {
public:
    int findNumberOfLIS(vector<int>& a)
    {
        std::vector<int> vec{ a };
        std::ranges::sort(vec);
        bitree b{ a.size() };
        for(int val : a)
        {
            auto it{ std::ranges::lower_bound(vec,val) };
            int index{ 1 + static_cast<int>(it - vec.begin()) };
            auto [len,cnt]{ b.query(index - 1) };
            b.update(index,{ len + 1,std::max(1,cnt) });
        }
        auto [len,cnt]{ b.query(a.size()) };

        return cnt;
    }
};
