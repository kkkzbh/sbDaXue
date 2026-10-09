

#include<iostream>
#include<print>
#include<vector>
#include<ranges>
#include<algorithm>
#include<functional>
#include<map>
#include<numeric>

using namespace std::views;

auto main() -> int
{
    auto scan = []<typename... Args>(Args&&... args) { (std::cin >> ... >> args); };
    int n,c;
    std::cin >> n >> c;
    auto a = std::vector(n,0);
    std::ranges::for_each(a,scan);

    auto prefix = [&,prefix_a = std::invoke([&] {
        auto vec = std::vector(n + 1,0);
        for(auto i : iota(0,n)) {
            vec[i + 1] = vec[i] + a[i - 1];
        }
        return vec;
    })](int l,int r) { return prefix_a[r] - prefix_a[l]; };

    auto ans = std::vector<int>{};
    bool flag;
    for(auto dep : iota(n,n + 1)) {
        flag = std::invoke(
                [&, path = std::vector<int>{}, dp = std::vector(n, std::map<int, bool>{})](this auto &&self, int i,int val) -> bool { // NOLINT
                    if(val == c) {
                        ans = std::move(path);
                        return dp[i][val] = true;
                    }
                    if(i == n or val > c or val + prefix(i,n) < c) {
                        return false;
                    }
                    if(dp[i][val]) {
                        return true;
                    }
                    if(int(path.size()) == dep) {
                        return false;
                    }
                    if(self(i + 1, val)) {
                        return dp[i][val] = true;
                    }
                    path.push_back(a[i]);
                    if(self(i + 1, val + a[i])) {
                        return dp[i][val] = true;
                    }
                    path.pop_back();
                    return false;
                }, 0, 0);
        if(flag) {
            break;
        }
    }

    if(not flag) {
        std::print("No solution!");
        return 0;
    }

    for(auto const& v : ans) {
        std::print("{} ",v);
    }
    std::println();
    std::print("{}",std::reduce(ans.begin(),ans.end()));

    return 0;
}