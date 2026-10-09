

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums)
    {
        std::ranges::sort(nums,[](int x,int y) -> bool {
            if(!x or !y) {
                return x;
            }
            int nx{},ny{};
            std::array<int,32> ax,ay;
            while(x) {
                ax[nx++] = x % 10;
                x /= 10;
            }
            while(y) {
                ay[ny++] = y % 10;
                y /= 10;
            }
            for(int i{},ix{ nx - 1 },iy{ ny - 1 },cei{ std::lcm(nx,ny) }; i != cei; ++i,ix = (ix - 1 + nx) % nx,iy = (iy - 1 + ny) % ny) {
                if(ax[ix] != ay[iy]) {
                    return ax[ix] > ay[iy];
                }
            }
            return true;
        });
        std::string ret;
        for(int v : nums) {
            ret += std::to_string(v);
        }
        return ret[0] == '0' ? "0" : ret;
    }
};