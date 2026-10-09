

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& a) {
        let n = int(a.size());
        let l = -1,r = l - 1;
        for(let max = -2147483647; let i in views::iota(0,n)) {
            if(a[i] < max) {
                r = i;
            }
            max = std::max(max,a[i]);
        }
        for(let min = 2147483647; let i in views::iota(0,n) | views::reverse) {
            if(a[i] > min) {
                l = i;
            }
            min = std::min(min,a[i]);
        }
        return r - l + 1;
    }
};