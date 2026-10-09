

#include<iostream>
#include<vector>
#include<array>
#include<utility>

constexpr int size = 1e5 + 2;

std::array<std::vector<std::pair<int,int>>,size> a{};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    int n,q;
    std::cin >> n >> q;
    int c,i,j,val;
    while(q--)
    {
        if(std::cin >> c >> i >> j; c == 1)
        {
            std::cin >> val;
            auto it = a[i].begin(),ed = a[i].end();
            for(;it != ed;++it)
                if(it->first == j)
                {
                    it->second = val;
                    break;
                }
            if(it == ed)
                a[i].emplace_back(j,val);
        }
        else
        {
            for(auto&& it : a[i])
            {
                if(it.first == j)
                {
                    std::cout << it.second << '\n';
                    break;
                }
            }
        }
    }

    return 0;
}
