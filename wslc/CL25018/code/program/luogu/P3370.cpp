

#include<iostream>
#include<unordered_set>
#include<string>

int main()
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    std::string s;
    int n;
    std::cin >> n;
    std::unordered_set<std::string> set;
    while(n--)
    {
        std::cin >> s;
        set.insert(s);
    }
    std::cout << set.size();

    return 0;
}