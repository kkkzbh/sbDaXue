

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define fun auto
#define let auto
#define in :

using namespace std;

struct section
{
    fun friend operator<(section const& section1,section const& section2) {
        let const& [l1,r1] = section1;
        let const& [l2,r2] = section2;
        let len1 = r1 - l1 + 1;
        let len2 = r2 - l2 + 1;
        if(len1 == len2) {
            return l1 < l2;
        }
        return len1 < len2;
    }
    int l,r;
};

using node = std::array<int,2>;

#define U(X) using __gnu_pbds::X;
U(tree) U(null_type) U(rb_tree_tag) U(null_node_update)

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& a) {
        let n = int(a.size());
        let _c = [&](node const& n1,node const& n2) {
            let const& [h1,i1] = n1;
            let const& [h2,i2] = n2;
            if(a[h1][i1] == a[h2][i2]) {
                return h1 < h2;
            }
            return a[h1][i1] < a[h2][i2];
        };
        let list = tree<node,null_type,decltype(_c),rb_tree_tag,null_node_update>{ _c };
        let r = section{ -100000,100000 };
        let range = views::iota;
        for(let i in range(0,n)) {
            list.insert(node{ i,0 });
        }
        let proj = [&](node const& n) {
            let const& [h,i] = n;
            return a[h][i];
        };
        #define mi (proj(*list.begin()))
        #define ma (proj(*list.rbegin()))
        return [&] {
            while(true) {
                r = std::min(r,section{ mi,ma });
                let const [h,i] = *list.begin();
                list.erase(list.begin());
                if(i + 1 == a[h].size()) {
                    return std::vector{ r.l,r.r };
                }
                list.insert(node{ h,i + 1 });
            }
        }();
    }
};
