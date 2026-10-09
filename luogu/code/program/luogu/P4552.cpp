

#include<iostream>
#include<array>
#include<algorithm>
#include<iterator>
#include<numeric>
#include<cmath>

constexpr int N{ 100000 + 2 };

std::array<int,N> a;
std::array<int,N> diff;
int n;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>(std::cin),n,a.begin() + 1);
    std::adjacent_difference(a.begin() + 1,a.begin() + 1 + n,diff.begin() + 1);
    long long postv{},inpostv{};
    std::for_each(diff.begin() + 2,diff.begin() + 1 + n,
                  [&](int i) -> void
                  {
                      if(i > 0)
                      {
                          postv += i;
                      }
                      else if(i < 0)
                      {
                          inpostv -= i;
                      }
                  });
    std::cout << std::max(postv,inpostv) << '\n' << std::abs(postv - inpostv) + 1; //不可双贪心求独立双优

    return 0;
}