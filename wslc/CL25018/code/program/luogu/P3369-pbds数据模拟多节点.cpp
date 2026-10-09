

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

namespace gnu
{
    using namespace __gnu_pbds;
    using namespace __gnu_cxx;
}

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    let set = gnu::tree<int64,gnu::null_type,std::less<>,gnu::rb_tree_tag,gnu::tree_order_statistics_node_update>{};
    let multi = [](int64 v){ return v << 17; };
    let restore = [](int64 v) { return v >> 17; };

    for(let i in iota(0,n)) {
        int opt,x;
        std::cin >> opt >> x;
        switch(opt) // NOLINT
        {
            case 1:
            {
                set.insert(multi(x) + i);
            }
                break;
            case 2:
            {
                set.erase(set.lower_bound(multi(x)));
            }
                break;
            case 3:
            {
                std::cout << set.order_of_key(multi(x)) + 1 << '\n';
            }
                break;
            case 4:
            {
                std::cout << restore(*set.find_by_order(x - 1)) << '\n';
            }
                break;
            case 5:
            {
                std::cout << restore(*--set.lower_bound(multi(x))) << '\n';
            }
                break;
            case 6:
            {
                std::cout << restore(*set.upper_bound(multi(x) + n - 1)) << '\n';
            }
                break;
        }
    }



    return 0;
}


