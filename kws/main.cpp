

#include <bits/stdc++.h>

int main()
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,0);
    for (auto& v : a) {
        std::cin >> v;
    }
    for (auto v : a) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}