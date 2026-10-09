

#include<bits/stdc++.h>
using namespace std;

class NumArray {
public:

    vector<int> vec;

    NumArray(vector<int>& a)
    {
        vec.reserve(a.size() + 1);
        vec.push_back(0);
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            vec.push_back(vec.back() + a[i]);
        }
    }

    int sumRange(int left, int right)
    {
        return vec[right + 1] - vec[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */