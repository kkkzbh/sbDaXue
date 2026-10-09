

#include<iostream>


int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n;
    std::cin >> n;
    int ans{};
    for(int i{ 1 }; i <= n; ++i)
    {
        int x;
        std::cin >> x;
        ans ^= x;
    }
    std::cout << ans;

    return 0;
}