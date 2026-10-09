


#include<iostream>
#include<set>

std::set<int> set;

[[maybe_unused]]
auto M_ = []() -> auto
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    return 0;
}();

int main()
{
    int n;
    std::cin >> n;
    for(int i{},op,len; i != n;++i)
    {
        decltype(set.begin()) it;
        if(std::cin >> op >> len; op == 1)
        {
            if((it = set.find(len)) == set.end())
                set.insert(len);
            else
                std::cout << "Already Exist\n";
        }
        else
        {
            if((it = set.find(len)) != set.end())
            {
                std::cout << len << '\n';
                set.erase(it);
            }
            else if(set.empty())
                std::cout << "Empty\n";
            else
            {
                auto front = set.lower_bound(len);
                auto back = front;
                if(front != set.begin())
                    --front;
                if(back != set.end() && (*back - len) < (len - *front))
                {
                    front = back;
                }
                std::cout << *front << '\n';
                set.erase(front);
            }
        }
    }

    return 0;
}