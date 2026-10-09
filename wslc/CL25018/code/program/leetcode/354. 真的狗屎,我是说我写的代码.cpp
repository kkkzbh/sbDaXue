

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& a)
    {
        std::ranges::sort(a,[](const auto& v1,const auto& v2)
        {
            return v1 < v2;
        });
        std::vector<std::vector<std::vector<int>>> ends;
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            auto it{ std::lower_bound(ends.begin(),ends.end(),a[i],[](const auto& v1,const auto& v2)
            {
                return std::ranges::any_of(v1,[&v2](const auto& v)
                {
                    return v[0] < v2[0] and v[1] < v2[1];
                });
            }) };
            if(it == ends.end())
            {
                ends.emplace_back();
                ends.back().push_back(a[i]);
            }
            else
            {
                bool ${};
                for(int j : std::views::iota(0,static_cast<int>(it->size())))
                {
                    if(a[i][0] < (*it)[j][0] and a[i][1] < (*it)[j][1])
                    {
                        (*it)[j] = a[i];
                        $ = true;
                    }
                    else if(a[i][0] == (*it)[0][0] or a[i][1] == (*it)[0][1])
                    {
                        (*it)[j][0] = std::min((*it)[j][0],a[i][0]);
                        (*it)[j][1] = std::min((*it)[j][1],a[i][1]);
                        $ = true;
                        break;
                    }
                }
                if(!$)
                {
                    it->push_back(a[i]);
                }
                else
                {
                    auto r{ std::ranges::unique(*it) };
                    it->erase(std::ranges::begin(r),std::ranges::end(r));
                }
            }
        }
        return ends.size();
    }
};

int main()
{
    std::vector<std::vector<int>> vec{
            { 2,100 },{ 3,200 },{ 4,300 },{ 5,500 },{ 5,400 },{ 5,250 },{ 6,370 },{ 6,360 },{ 7,380 }
    };
    Solution{}.maxEnvelopes(vec);
    return 0;
}