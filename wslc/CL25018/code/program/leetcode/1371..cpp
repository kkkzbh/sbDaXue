

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

#define n static_cast<int>(s.size())

    char cv(const char c)
    {
        char ret{ 1 };
        switch (c)
        {
            case 'u':
                ret <<= 1;
            case 'o':
                ret <<= 1;
            case 'i':
                ret <<= 1;
            case 'e':
                ret <<= 1;
            case 'a':
                break;
            default:
                ret = -1;
        }
        return ret;
    }

    int findTheLongestSubstring(string& s)
    {
        std::array<int,0b100000> map{};
        map.fill(-2);
        map[0] = -1;
        char state{};
        int ret{};
        for(int i : std::views::iota(0,n))
        {
            char op{ cv(s[i]) };
            if(op != -1)
            {
                state ^= op;
            }
            if(map[state] != -2)
            {
                ret = std::max(ret,i - map[state]);
            }
            else
            {
                map[state] = i;
            }
        }
        return ret;
    }
};