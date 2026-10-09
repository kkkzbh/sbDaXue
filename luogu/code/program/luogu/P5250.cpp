


#include<iostream>
#include<set>

std::set<int> set;

[[maybe_unused]]
auto M_ = []() -> auto
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
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
                auto x = set.lower_bound(len);
                if(x == set.end())
                {
                    --x;
                    std::cout << *x << '\n';
                    set.erase(x);
                }
                else if(x != set.begin())
                {
                    auto y = x--;
                    if (len - *x <= *y - len)
                    {
                        std::cout << *x << '\n';
                        set.erase(x);
                    }
                    else
                    {
                        std::cout << *y << '\n';
                        set.erase(y);
                    }
                }
                else
                {
                    std::cout << *x << '\n';
                    set.erase(x);
                }
            }
        }
    }

    return 0;
}